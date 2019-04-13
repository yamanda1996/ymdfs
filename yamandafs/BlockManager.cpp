#include "BlockManager.h"

namespace yamanda
{

	namespace ymdfs
	{

		extern Counter g_find_ops;

		BlockManager::BlockManager()
		{
		}


		BlockManager::~BlockManager()
		{
		}

		Data_Block *BlockManager::FindBlock(int64_t block_id)
		{
			g_find_ops.Inc();
			std::lock_guard<std::mutex> lock(block_map_mutex_);
			auto it = block_map_.find(block_id);
			if (block_map_.end() == it)
			{
				return NULL;		//Î´ÕÒµ½block
			}
			Data_Block * block = it->second;
			block->AddRef();
			return block;
		}

	}
}

