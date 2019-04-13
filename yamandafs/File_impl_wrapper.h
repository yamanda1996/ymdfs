#pragma once
#include <memory>

#include "ymdfs.h"

namespace yamanda 
{
	namespace ymdfs
	{

		class ymdfs;
		class RpcClient;
		class FileImpl;


		class File_impl_wrapper : public File
		{
		public:
			File_impl_wrapper();
			File_impl_wrapper(ymdfs *ymdfs, RpcClient *client, const char *path,
				int32_t flags, WriteOption write_option);

			virtual ~File_impl_wrapper();

			int32_t Pread(char *buf, int32_t read_size, int64_t offset, bool reada = false);
			int32_t Read(char *buf, int32_t read_size);
			int32_t Write(const char *buf, int32_t write_size);
			int32_t Seek(int64_t offset, int32_t whence);
			int32_t Flush();
			int32_t Sync();
			int32_t Close();

		private:
			std::shared_ptr<FileImpl> impl_;
		};

	}
}


