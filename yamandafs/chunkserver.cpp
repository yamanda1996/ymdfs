#include "chunkserver.h"

namespace yamanda
{
	namespace ymdfs
	{

		chunkserver::chunkserver()
		{
			common_ = new Common;
		}


		chunkserver::~chunkserver()
		{
			if (nullptr != common_)
			{
				delete common_;
				common_ = nullptr;
			}
		}

		ChunkServer_Stub::ChunkServer_Stub()
		{
			
		}
		ChunkServer_Stub::~ChunkServer_Stub()
		{
			
		}
	}
}


