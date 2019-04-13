#pragma once
#include "sofa/pbrpc/pbrpc.h"

#include "ReadBlockRequest.h"
#include "ReadBlockResponse.h"
#include "Common.h"


namespace yamanda
{

	namespace ymdfs
	{

		

		class chunkserver
		{
		public:
			chunkserver();
			virtual ~chunkserver();

		protected:
			Common *common_;
		};







		class ChunkServer_Stub
		{
		public:
			ChunkServer_Stub();
			virtual ~ChunkServer_Stub();
			virtual void ReadBlock(::google::protobuf::RpcController *controller,
				const ReadBlockRequest *request, ReadBlockResponse * response,
				::google::protobuf::Closure *done) = 0;

		private:
			
		};

	}
}


