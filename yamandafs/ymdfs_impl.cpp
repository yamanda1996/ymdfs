#include "ymdfs_impl.h"


namespace yamanda 
{

	namespace ymdfs
	{

		int32_t GetErrorCode(StatusCode stat)
		{
			if (stat < 100)
			{
				if (0 == stat)
				{
					return OK;
				}
				else
				{
					return UNKNOWN_ERROR;
				}
			}
			switch (stat / 100)
			{
			case 1:
				return BAD_PARAMETER;
			case 2:
				return PERMISSION_DENIED;
			default:
				return UNKNOWN_ERROR;
			}
		}

		ymdfs_impl::ymdfs_impl()
		{
			common_ = new Common;
			local_host_name_ = common_->get_local_hostname();
		}


		ymdfs_impl::~ymdfs_impl()
		{
		}


		int32_t ymdfs_impl::OpenFile(const char *path, int32_t flags, File **file,
			const ReadOption &options)
		{
			
		}


		int32_t ymdfs_impl::OpenFile(const char *path, int32_t flags, File **file,
			const WriteOption &options)
		{
			
		}


		int32_t ymdfs_impl::OpenFile(const char *path, int32_t flags, int32_t mode,
			File **file, const WriteOption &options)
		{
			*file = NULL;
			if (!(flags & O_WRONLY))
			{
				return BAD_PARAMETER;
			}
			WriteOption write_option = options;
			/*if (write_option.write_mode == kWriteDefault)
			{

			}*/
			FileLocationRequest request;
			FileLocationResponse response;

			request.set_filename(path);
			request.set_sequence_id(0);

			bool rpc_ret = nameserver_client_->SendRequest(&NameServer_Stub::GetFileLocation,
											&request, &response, 15, 1);
			if (!rpc_ret || response.status() != OK)
			{
				LOG(WARN,"Open file for write failed,%s,rpc_ret = %d,status = %s\n",
						path,rpc_ret,response.status().c_str());

				if (!rpc_ret)
				{
					return TIMEOUT;
				}
				else
				{
					return GetErrorCode(response.status());
				}
			}
			else
			{
				*file = new File_impl_wrapper(this, rpc_client_, path, flags, options);
			}



		}

		int32_t GetErrorCode()


		int32_t ymdfs_impl::DeleteFile(const char *path)
		{

		}
	}




}