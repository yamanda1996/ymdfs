#pragma once
#include <stdint.h>
#include <map>
#include <mutex>

#include "data_block.h"
#include "Common.h"

namespace yamanda
{
	namespace ymdfs
	{

		class BlockManager
		{
		public:
			BlockManager();
			virtual ~BlockManager();
			Data_Block *FindBlock(int64_t block_id);



		private:


		private:
			std::map<int64_t, Data_Block *>		block_map_;
			std::mutex							block_map_mutex_;

		};

	}
}


