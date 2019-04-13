#include "FileImpl.h"



namespace yamanda
{

	namespace ymdfs
	{

		WriteBuffer::WriteBuffer(int32_t seq, int32_t buf_size, int64_t block_id, int64_t offset)
			:seq_id_(seq),buf_size_(buf_size),
			block_id_(block_id),offset_(offset),
			data_size_(0),is_last_(false),refs_(0)
		{
			
			buf_ = new char[buf_size];

		}

		WriteBuffer::~WriteBuffer()
		{
			if (NULL != buf_)
			{
				delete [] buf_;
				buf_ = NULL;
			}
		}

		int WriteBuffer::Available() const
		{
			return buf_size_ - data_size_;
		}

		int WriteBuffer::Append(const char *buf, int len)
		{
			assert(data_size_ + len <= buf_size_);
			memcpy(buf_ + data_size_, buf, len);
			data_size_ += len;
			return data_size_;

		}

		const char* WriteBuffer::Data() const
		{
			return buf_;
		}

		int WriteBuffer::Size() const
		{
			return data_size_;
		}


		int WriteBuffer::Sequence() const
		{
			return seq_id_;
		}

		void WriteBuffer::Clear()
		{
			data_size_ = 0;
		}


		void WriteBuffer::SetLast()
		{
			is_last_ = true;
		}
		bool WriteBuffer::IsLast() const
		{
			return is_last_;
		}


		int64_t WriteBuffer::offset() const
		{
			return offset_;
		}
		int64_t WriteBuffer::block_id() const
		{
			return block_id_;
		}

		void WriteBuffer::AddRefBy(int counter)
		{
			common_.atomic_add(&refs_, counter);
		}
		void WriteBuffer::AddRef()
		{
			common_.atomic_inc(&refs_);
		}
		void WriteBuffer::DecRef()
		{
			if ( 1 == (common_.atomic_add(&refs_,-1)))
			{
				//引用计数为0，删除该对象
				assert(0 == refs_);
				delete this;
			}
		}

		FileImpl::FileImpl(ymdfs_impl *ymdfs,std::string name):
			ymdfs_(ymdfs),last_chunkserver_index_(-1),name_(name)
		{
			
		}


		FileImpl::~FileImpl()
		{
		}


		int32_t FileImpl::Pread(char *buf, int32_t read_size, int64_t offset, bool reada = false)
		{
			if (read_size < 0 || buf == NULL || offset < 0)
			{
				LOG(WARNING, "Pread(%s,%ld,%d),bad parameters", name_.c_str(),offset,read_size);
				return BAD_PARAMETER;
			}
			{
				std::lock_guard<std::mutex> lock(mutex_);
				if (-1 == last_read_offset_ || 
					last_read_offset_ != offset)
				{
					sequential_ratio_ /= 2;
					LOG(DEBUG, "Pread(%s,%ld,%d) missing last read offset %ld",
						name_.c_str(), offset, last_read_offset_, last_read_offset_);
				}
				else
				{
					sequential_ratio_++;
				}
				last_read_offset_ = offset + read_size;
				if (reada_buf_ && reada_base_ <= offset &&
						reada_base_ + reada_buf_len_ >= offset + read_size)
				{
					memcpy(buf,reada_buf_ + (offset - reada_base_),read_size);
					return read_size;
				}
			}
			LocatedBlock lcblock;
			ChunkServer_Stub *chunkserver = NULL;
			std::string cs_addr;
			int64_t block_id;

			{
				std::lock_guard<std::mutex> lock(mutex_);
				if (located_blocks_.blocks_.empty())
				{
					return 0;
				}
				else if (0 == located_blocks_.blocks_[0].chains_size())
				{
					if (0 == located_blocks_.blocks_[0].block_size())
					{
						return 0;
					}
					else
					{
						LOG(WARN, "no located chunkserver of block #%ld",
							located_blocks_.blocks_[0].block_id());
						return TIMEOUT;
					}
				}
				lcblock.CopyFrom(located_blocks_.blocks_[0]);
				if (-1 == last_chunkserver_index_ || !chunkserver_stub_)
				{
					const std::string& local_host_name = ymdfs_->local_host_name_;
					for (int i = 0;i < lcblock.chains_size();++i)
					{
						//addr为定位的block所在的ChunkServerInfo的地址
						std::string addr = lcblock.chains(i).address();
						std::string cs_name = std::string(addr, 0, addr.find_last_of(":"));
						if (cs_name == local_host_name)
						{
							last_chunkserver_index_ = i;
							cs_addr = lcblock.chains(i).address();
							break;
						}
					}
					//如果该block所在的chunkserver不是本机，随机选择一个chunkserver
					if (-1 == last_chunkserver_index_)
					{
						int server_index = rand() % lcblock.chains_size();
						cs_addr = lcblock.chains(server_index).address();
						last_chunkserver_index_ = server_index;
					}
					ymdfs_->rpc_client_->GetStub(cs_addr, &chunkserver_stub_);
				}
				chunkserver = chunkserver_stub_;
				block_id = lcblock.block_id();
			}

			ReadBlockRequest request;
			ReadBlockResponse response;

			request.set_sequence_id(common_->get_micros_time());
			request.set_block_id(block_id);
			request.set_offset(offset);
			int32_t rlen = read_size;

			if (sequential_ratio_ > 2 &&
				reada &&
				read_size < FLAGS_sdk_file_reada_len)
			{
				rlen = (static_cast<int64_t>(FLAGS_sdk_file_reada_len)) < 
					(static_cast<int64_t>((sequential_ratio_) * read_size)) ? 
					(static_cast<int64_t>(FLAGS_sdk_file_reada_len)):
					(static_cast<int64_t>((sequential_ratio_)* read_size));
				LOG(DEBUG,"Pread(%s,%ld,%d) sequential_ratio_:%d,readahead to %d",
					name_.c_str(),offset,read_size,sequential_ratio_,rlen);
			}
			request.set_read_len(rlen);
			bool ret = false;

			for (int retry_time = 0;retry_time < lcblock.chains_size() * 2;retry_time++)
			{
				LOG(DEBUG,"start Pread %s",cs_addr.c_str());
				ymdfs_->rpc_client_->SendRequest(chunkserver, &ChunkServer_Stub::ReadBlock,
					&request, &response, 15, 3);

			}


		}
		int32_t FileImpl::Read(char *buf, int32_t read_size)
		{
			
		}
		int32_t FileImpl::Write(const char *buf, int32_t write_size)
		{
			
		}
		int32_t FileImpl::Seek(int64_t offset, int32_t whence)
		{
			
		}
		int32_t FileImpl::Flush()
		{
			
		}
		int32_t FileImpl::Sync()
		{
			
		}
		int32_t FileImpl::Close()
		{

		}

	}
}
