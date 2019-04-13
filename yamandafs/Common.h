#pragma once
#include <mutex>
#include <string>
#include <stdint.h>
#include <windows.h>
#include <map>
#include <atomic>



#define LOG printf
#define DEBUG 0
#define INFO "info"
#define WARN "warn"
#define WARNING "warning"
#define ERROR 3


//从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME (116444736000000000UL)

namespace yamanda
{

	namespace ymdfs
	{
		class Common
		{
		public:
			Common();
			~Common();

			volatile int atomic_add(volatile int *a,int b);
			volatile int atomic_inc(volatile int *a);

			std::string get_local_hostname();

			int64_t get_micros_time();

		private:
			std::mutex mutex_;
		};

		
		class Counter
		{
		public:
			Counter();
			virtual ~Counter();
			int64_t Inc();
			int64_t Dec();

		private:
			int64_t count_;
			std::mutex count_mutex_;

		};

	}
}

namespace common
{

#define BAD_PARAM 1
	//只能放这，要不互相包含，就找不到这个结构体了
	struct FileEntity
	{
		FILE* fp;
		std::string file_name;
	};
	
	class Slice
	{
	public:
		Slice(std::string str) :str_(str) {}
		std::string get_str()
		{
			return str_;
		}

		//为了使这个类型能够作为map的key值，必须重载<操作符
		bool operator<(const Slice& s2)
		{
			return str_ < s2.str_;
		}

	private:

	private:
		std::string				str_;

	};

	class Cache
	{
	class Handler;
	public:
		Cache() {}
		virtual ~Cache(){}
		Handler* Lookup(Slice& slice) 
		{
			std::lock_guard<std::mutex> lock(slice_handler_map_mutex_);
			auto handler = slice_handler_map_.find(&slice);
			if (slice_handler_map_.end() == handler)
			{
				LOG(INFO, "unfind filename : %s", slice.get_str());
				return NULL;
			}
			Handler* res = handler->second;
			return res;
		}


		Handler* Insert(Slice& slice,FileEntity* file,int count,
			void (*func)(void*))
		{
			Handler* handler = new Handler(file->fp,file->file_name,count);
			std::lock_guard<std::mutex> lock(slice_handler_map_mutex_);
			slice_handler_map_.insert(std::pair<Slice*, Handler*>(
				&slice,handler));
			func(file);			//FileEntry对象用完就不需要了，使用回调函数释放file内存
			return handler;
		}

		void* Value(Handler* handler)
		{
			return handler->get_file_p();
		}

		void Release(Handler *handler)
		{
			handler->Dec();
		}

	public:
		class Handler
		{
		public:
			Handler(FILE* file,std::string file_name,int count):
				file_(file),file_name_(file_name)
			{
				count_.store(count);
			}
			FILE* get_file_p()
			{
				return file_;
			}
			virtual ~Handler() {}
			//注意线程安全
			int Inc()
			{
				count_++;
				return count_.load();
			}
			int Dec()
			{
				count_--;
				return count_.load();
			}


		private:

		private:
			FILE*						file_;
			std::string					file_name_;
			volatile std::atomic<int>	count_{0};

		};

	private:


	private:
		std::map<Slice*, Handler*> slice_handler_map_;
		std::mutex slice_handler_map_mutex_;
	};

	
	class Counter
	{
	public:
		Counter()
		{
			counter_.store(0);
		}
		int Inc()
		{
			counter_++;
			return counter_;
		}

		int Dec()
		{
			counter_--;
			return counter_;
		}

	private:
		volatile std::atomic<int> counter_{ 0 };

	};

}


