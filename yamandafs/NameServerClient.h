#pragma once
#include "google/protobuf/service.h"

namespace yamanda
{

	namespace ymdfs
	{
		class NameServer_Stub;
		class NameServerClient
		{
		public:
			NameServerClient();
			~NameServerClient();

			template <typename Request,typename Response,typename Callback>
			bool SendRequest(void (NameServer_Stub::*func)(google::protobuf::RpcController *,
				const Request *, Response *, Callback *),
				const Request *request, Response * response, int 32_t rpc_timeout, int retry_time = 1)
			{
				bool flag = false;

				return flag;
			}
		};

	}
}


