#pragma once
#include <stdint.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


#include "Common.h"



namespace yamanda
{
	namespace ymdfs
	{

		

		class File_Cache
		{
		public:
			File_Cache();
			virtual ~File_Cache();

			int64_t ReadFile(const std::string &filepath,char *buf,int64_t len,int64_t offset);


		private:
			common::Cache::Handler* FindFile(const std::string& file_path);

		private:
			common::Cache*			cache_;
			std::mutex				read_file_mutex_;
		};
	}
}


