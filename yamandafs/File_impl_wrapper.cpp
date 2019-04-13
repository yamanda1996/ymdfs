#include "File_impl_wrapper.h"

#include "rpc_client.h"
#include "FileImpl.h"

namespace yamanda
{
	namespace ymdfs
	{
		File_impl_wrapper::File_impl_wrapper()
		{
		}

		File_impl_wrapper::File_impl_wrapper(ymdfs *ymdfs, RpcClient *client, const char *path,
			int32_t flags, WriteOption write_option)
		{

		}



		File_impl_wrapper::~File_impl_wrapper()
		{
		}


		int32_t File_impl_wrapper::Pread(char *buf, int32_t read_size, int64_t offset, bool reada = false)
		{
			
			return 0;
		}
		int32_t File_impl_wrapper::Read(char *buf, int32_t read_size)
		{
			return 0;

		}
		int32_t File_impl_wrapper::Write(const char *buf, int32_t write_size)
		{
			return 0;

		}
		int32_t File_impl_wrapper::Seek(int64_t offset, int32_t whence)
		{
			return 0;

		}
		int32_t File_impl_wrapper::Flush()
		{
		
			return 0;

		}
		int32_t File_impl_wrapper::Sync()
		{
			return 0;

		}
		int32_t File_impl_wrapper::Close()
		{
			return 0;

		}

	}



}


