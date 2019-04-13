#pragma once

#include "counter_manager.h"


namespace yamanda
{
	namespace ymdfs
	{

		class Data_Block;

		typedef DiskCounterManager::DiskCounters DCounters;
		typedef DiskCounterManager::DiskStat DStat;


		class Disk
		{
		public:
			Disk();
			~Disk();

		private:


		private:
			friend class Data_Block;
			DCounters			counters_;
		};
	}
}


