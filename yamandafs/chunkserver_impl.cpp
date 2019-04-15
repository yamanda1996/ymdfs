#include "chunkserver_impl.h"

#include "counter_manager.h"

namespace yamanda
{

	namespace ymdfs
	{
		extern common::Counter g_read_bytes;
		extern common::Counter g_read_ops;

		chunkserver_impl::chunkserver_impl()
		{
			block_manager_ = new BlockManager;
		}


		chunkserver_impl::~chunkserver_impl()
		{
		}

		void chunkserver_impl::ReadBlock(::google::protobuf::RpcController *controller,
			const ReadBlockRequest *request, ReadBlockResponse * response,
			::google::protobuf::Closure *done)
		{
			int64_t block_id = request->block_id();
			int64_t offset = request->offset();
			int32_t read_len = request->read_len();
			if (read_len <= 0 || read_len > (64 << 20) || offset < 0)
			{
				LOG(WARNING, "ReadBlock bad paramters %d,%ld",read_len,offset);
				response->set_status(kBadParameter);
				done->Run();
				return;
			}
			if (!response->has_sequence_id())
			{
				response->set_sequence_id(request->sequence_id());
				response->add_timestamp();
				std::function<void()> task = std::bind(&chunkserver_impl::ReadBlock,
					this, controller, request, response, done);
				thead_pool->AddTask(task);
				return;
			}
			StatusCode status = kOk;
			int64_t find_start = common_->get_micros_time();

			Data_Block *block = block_manager_->FindBlock(block_id);
			if (NULL == block)
			{
				status = kCsNotFound;
				LOG(WARNING, "ReadBlock not found: #%ld offset: %ld len: %d\n",
					block_id,offset,read_len);
			}
			else
			{
				int64_t read_start = common_->get_micros_time();
				char *buf = new char[read_len];
				int64_t len = block->Read(buf, read_len, offset);
				int64_t read_end = common_->get_micros_time();
				if (len >= 0)
				{
					response->mutable_databuf()->assign(buf, len);
					LOG(INFO, "ReadBlock #%ld offset: %ld len: %d return: %ld \
						use %ld %ld %ld %ld %ld",block_id,offset,read_len,len,
						(response->timestamp(0) - request->sequence_id()) / 1000,		//rpc time
						(find_start - response->timestamp(0)) / 1000,		//dispatch time
						(read_start - find_start) / 1000,		//find time
						(read_end - read_start) / 1000,			//read time
						(read_end - response->timestamp(0) / 1000));	//service time
					g_read_ops.Inc();
					g_read_bytes.Add(len);
				}
				else
				{
					status = kReadError;
					LOG(WARNING, "ReadBlock #%ld fail offset: %ld len: %ld",
						block_id, offset, read_len);
				}
				delete[] buf;
			}
			response->set_status(status);
			done->Run();
			if (block)
			{
				block->DecRef();
			}
		}
	}
}


