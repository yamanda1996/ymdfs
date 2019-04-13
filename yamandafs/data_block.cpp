#include "data_block.h"


namespace yamanda
{
	namespace ymdfs
	{
		BlockMeta::BlockMeta(std::string store_path, int64_t block_id):
			store_path_(store_path),block_id_(block_id)
		{
			
		}
		BlockMeta::~BlockMeta()
		{
			
		}


		int64_t BlockMeta::block_size() const
		{
			return block_size_;
		}

		void BlockMeta::set_block_size(int64_t size)
		{
			block_size_ = size;
		}

		std::string BlockMeta::store_path() const
		{
			return store_path_;
		}

		int64_t BlockMeta::block_id() const
		{
			return block_id_;
		}



		Data_Block::Data_Block(const BlockMeta &meta,Disk* disk):
			meta_(meta),deleted_(false),
			disk_file_size_(meta.block_size()),
			disk_(disk),blockbuf_(NULL)
		{
			common_ = new Common;
			disk_file_ = meta.store_path() + BuildFilePath(meta.block_id());
		}


		Data_Block::~Data_Block()
		{
			if (nullptr != common_)
			{
				delete common_;
				common_ = nullptr;
			}
		}

		int Data_Block::AddRef()
		{
			int res = common_->atomic_add(&refs_, 1);
			assert(res > 0);
			return res;
		}

		int64_t Data_Block::Read(char *buf, int64_t len, int64_t offset)
		{
			//读取块中内容时加锁，此处可以改进为共享锁以及互斥锁
			std::lock_guard<std::mutex> lock(mutex_);
			if (offset > meta_.block_size())
			{
				LOG(INFO, "Wrong offset %ld > %ld",
					offset,meta_.block_size());
				return WRONG_PARAM;
			}
			else if (deleted_)
			{
				return DEL_BLOCK;
			}
			//数据被保存在磁盘还有缓冲区中
			//从磁盘中读取数据
			int64_t read_len = 0;	//读取完毕数据长度
			while (offset + read_len < disk_file_size_)
			{
				int64_t pread_len = (len - read_len) > (disk_file_size_ - offset - read_len) ? 
					(disk_file_size_ - offset - read_len) : (len - read_len);
				mutex_.unlock();
				int64_t ret = file_cache_->ReadFile(disk_file_,buf + read_len,
					pread_len,offset + read_len);
				disk_->counters_.mem_read_ops.Inc();
				mutex_.lock();
				if (ret != pread_len)
				{
					LOG(WARNING, "Read file failed,pread_len: %ld,offset: %ld,ret: %ld %s",
						pread_len, offset + read_len, ret,strerror(errno));
					return READ_FILE_FAIL;
				}
				read_len += ret;
				if (read_len >= len)
				{
					return read_len;
				}
			}
			//从block_buf_list中读取数据
			int64_t mem_offset = offset + read_len - disk_file_size_;
			int32_t buf_id = mem_offset / FLAGS_write_buf_size;
			mem_offset %= FLAGS_write_buf_size;
			while (buf_id < block_buf_list_.size())
			{
				const char* block_buf = block_buf_list_.at(buf_id).first;
				int buf_len = block_buf_list_.at(buf_id).second;
				int mlen = (len - read_len) < (buf_len - mem_offset)?
					(len - read_len): (buf_len - mem_offset);
				memcpy(buf + read_len, block_buf + mem_offset, mlen);
				disk_->counters_.mem_read_ops.Inc();
				read_len += mlen;
				mem_offset = 0;
				buf_id++;
				if (read_len >= len)
				{
					return read_len;
				}
			}
			assert(mem_offset >= 0);
			if (mem_offset < bufdatalen_)
			{
				int mlen = (bufdatalen_ - mem_offset) < (len - read_len) ?
					(bufdatalen_ - mem_offset) : (len - read_len);
				memcpy(buf + read_len, blockbuf_ + mem_offset, mlen);
				disk_->counters_.mem_read_ops.Inc();
				read_len += mlen;
			}
			return read_len;
		}

		std::string Data_Block::BuildFilePath(int64_t block_id)
		{
			char file_path[16];
			//len = 2 + 3 + 10
			int len = snprintf(file_path, sizeof(file_path), "/%03ld/%010ld",
				block_id % 1000, block_id / 1000);
			assert(15 == len);
			return file_path;
		}

	}
}

