#include "chunkserver_impl.h"

namespace yamanda
{

	namespace ymdfs
	{
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
					LOG(INFO, "");				//4ÔÂ12ÈÕ  yamanda
					//fjdks 
				}
				
			}


		}
	}
}


