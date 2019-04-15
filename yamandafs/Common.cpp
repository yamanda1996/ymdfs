#include "Common.h"

namespace yamanda
{

	namespace ymdfs
	{
		Common::Common()
		{
		}


		Common::~Common()
		{
		}

		std::string Common::get_local_hostname()
		{
			return std::string("localhost");
		}

		volatile int Common::atomic_add(volatile int *a, int b)
		{
			std::lock_guard<std::mutex> lock(mutex_);
			*a += b;
			return *a;
		}

		volatile int Common::atomic_inc(volatile int *a)
		{
			std::lock_guard<std::mutex> lock(mutex_);
			*a += 1;
			return *a;
		}

		int64_t Common::get_micros_time()
		{
			int64_t micro_time = 0;
			LARGE_INTEGER li;
			FILETIME ft;
			GetSystemTimeAsFileTime(&ft);
			li.LowPart = ft.dwLowDateTime;
			li.HighPart = ft.dwHighDateTime;
			micro_time = (li.QuadPart - EPOCHFILETIME) / 10;
			return micro_time;
		}

		//common::Counter::Counter():count_(0){}
		//common::Counter::~Counter(){}
		//int64_t common::Counter::Inc()
		//{
		//	//也可以使用原子操作
		//	std::lock_guard<std::mutex> lock(count_mutex_);
		//	count_++;
		//	return count_;
		//}
		//int64_t common::Counter::Dec()
		//{
		//	std::lock_guard<std::mutex> lock(count_mutex_);
		//	count_--;
		//	return count_;
		//}

	}
}



