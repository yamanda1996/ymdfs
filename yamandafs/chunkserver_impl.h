#pragma once
#include <functional>

#include "chunkserver.h"
#include "thread_pool.h"
#include "BlockManager.h"
#include "data_block.h"
#include "ReadBlockRequest.h"

namespace yamanda
{
	namespace ymdfs
	{

		enum StatusCode
		{
			kOk						= 0,
			kCsNotFound				= 1,
			kReadError				= 2
		};
		class ReadBlockRequest;
		class chunkserver_impl:public chunkserver
		{
		public:
			chunkserver_impl();
			virtual ~chunkserver_impl();
			virtual void ReadBlock(::google::protobuf::RpcController *controller,
				const ReadBlockRequest *request, ReadBlockResponse * response,
				::google::protobuf::Closure *done);

		private:
			thread_pool<std::function<void()>> *thead_pool;
			BlockManager *block_manager_;
		};
	}
}


