#pragma once
#include <queue>
#include <mutex>

namespace yamanda
{
	namespace ymdfs
	{

		template <typename Task>
		class thread_pool
		{
		public:
			template <typename Task>
			thread_pool()
			{
			}
			template <typename Task>
			virtual ~thread_pool()
			{
			}
			template <typename Task>
			void AddTask(Task task)
			{
				std::lock_guard<std::mutex> lock(task_queue_mutex_);
				task_queue_->push(task);
			}

		private:
			std::mutex task_queue_mutex_;
			std::queue<Task> task_queue_;
		};

	}
}


