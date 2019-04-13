#include "file_cache.h"

namespace yamanda
{
	namespace ymdfs
	{
		


		static void DeleteEntry(void* value)
		{
			common::FileEntity* file = reinterpret_cast<common::FileEntity*>(value);
			if (NULL != file->fp)
			{
				fclose(file->fp);
			}
			LOG(INFO, "FileCache close file: %s", file->file_name.c_str());
			delete file;
		}


		File_Cache::File_Cache()
		{
		}


		File_Cache::~File_Cache()
		{
		}

		int64_t File_Cache::ReadFile(const std::string &filepath, char *buf, int64_t len, int64_t offset)
		{
			common::Cache::Handler* handler = FindFile(filepath);
			if (NULL == handler)
			{
				return -1;
			}
			FILE* fp = handler->get_file_p();
			int64_t ret = 0;
			//对应Linux中的pread函数
			{
				std::lock_guard<std::mutex> lock(read_file_mutex_);
				fseek(fp, offset, SEEK_CUR);
				ret = fread(buf, 1, len, fp);
			}
			cache_->Release(handler);
			return ret;
		}

		common::Cache::Handler* File_Cache::FindFile(const std::string& file_path)
		{
			common::Slice key(file_path);
			//先从缓存中查，如果没有说明这是第一次读取该文件
			common::Cache::Handler* handler = cache_->Lookup(key);
			if (NULL == handler)
			{
				FILE* fp = fopen(file_path.c_str(), "r");
				if (NULL == fp)
				{
					LOG(WARNING, "File not found: %s", file_path.c_str());
					return NULL;
				}
				common::FileEntity* file = new common::FileEntity;
				file->file_name = file_path;
				file->fp = fp;
				handler = cache_->Insert(key, file, 1, DeleteEntry);
			}
			return handler;
		}
	}
}


