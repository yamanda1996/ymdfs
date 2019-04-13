#pragma once
#include "Common.h"

namespace yamanda
{
	namespace ymdfs
	{
		class counter_manager
		{
		public:
			counter_manager();
			virtual~counter_manager();
		};


		class DiskCounterManager
		{
		public:
			struct DiskCounters
			{
				common::Counter mem_read_ops;
			};

			struct DiskStat 
			{
			};

		};
	}
}


