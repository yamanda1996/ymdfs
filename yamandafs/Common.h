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


//��1601��1��1��0:0:0:000��1970��1��1��0:0:0:000��ʱ��(��λ100ns)
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
	//ֻ�ܷ��⣬Ҫ��������������Ҳ�������ṹ����
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

		//Ϊ��ʹ��������ܹ���Ϊmap��keyֵ����������<������
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
			func(file);			//FileEntry��������Ͳ���Ҫ�ˣ�ʹ�ûص������ͷ�file�ڴ�
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
			//ע���̰߳�ȫ
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


