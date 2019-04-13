#pragma once
#include <string>
#include <mutex>
#include <map>
#include <functional>
#include <algorithm>

#include "sofa/pbrpc/pbrpc.h"
#include "google/protobuf/service.h"


#include "chunkserver.h"

namespace yamanda
{

	namespace ymdfs
	{
		class RpcClient
		{
		public:
			RpcClient();
			virtual ~RpcClient();


			template <typename T>
			bool GetStub(const std::string server,T **stub);

			template <typename Stub,typename Request,typename Response,typename Callback>
			bool SendRequest(Stub *stub,void(Stub::*func)(
				google::protobuf::RpcController *,
				const Request *,Response *,Callback *),
				const Request *request,Response *response,
				int32_t rpc_timeout,int retry_times);


		private:
			::sofa::pbrpc::RpcClient *rpc_client_;
			typedef std::map<std::string, sofa::pbrpc::RpcChannel*> HostMap;
			HostMap *host_map_;
			std::mutex host_map_mutex_;
		};

	}
}