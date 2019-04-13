#pragma once
#include <fcntl.h>
#include <string>

#include "ymdfs.h"
#include "NameServerClient.h"
#include "FileLocationRequest.h"
#include "FileLocationResponse.h"
#include "NameServer_Stub.h"
#include "File_impl_wrapper.h"
#include "rpc_client.h"
#include "Common.h"

namespace yamanda
{
	namespace ymdfs
	{
		class ymdfs_impl:public ymdfs
		{
		public:
			friend class FileImpl;

			ymdfs_impl();
			~ymdfs_impl();

			int32_t OpenFile(const char *path, int32_t flags, File **file,
				const ReadOption &options);
			int32_t OpenFile(const char *path, int32_t flags, File **file,
				const WriteOption &options);
			int32_t OpenFile(const char *path, int32_t flags, int32_t mode,
				File **file, const WriteOption &options);
			int32_t DeleteFile(const char *path);


		private:
			NameServerClient *nameserver_client_;
			RpcClient *rpc_client_;
			std::string local_host_name_;
			Common *common_;

		};

	}
}


