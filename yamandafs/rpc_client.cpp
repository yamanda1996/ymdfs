#include "rpc_client.h"


namespace yamanda
{
	namespace ymdfs
	{
		RpcClient::RpcClient()
		{
			
		}
		RpcClient::~RpcClient()
		{
			
		}


		template <typename T>
		bool RpcClient::GetStub<T>(const std::string server, T **stub)
		{
			bool ret = true;
			std::lock_guard<std::mutex> lock(host_map_mutex_);
			::sofa::pbrpc::RpcChannel *channel = NULL;
			HostMap::iterator it = host_map_.find(server);

			if (host_map_.end() != it)
			{
				channel = it->second;
			}
			else    //如果没有找到server对应的channel，则创建一个新的channel
			{
				::sofa::pbrpc::RpcChannelOptions channelOptions;
				channel = new ::sofa::pbrpc::RpcChannel(rpc_client_,server,channelOptions);
				host_map_[server] = channel;
			}

			*stub = new T(channel);
			return ret;
		}

		template <typename Stub, typename Request, typename Response, typename Callback>
		bool RpcClient::SendRequest(Stub *stub, void(Stub::*func)(
			google::protobuf::RpcController *,
			const Request *, Response *, Callback *),
			const Request *request, Response *response,
			int32_t rpc_timeout, int retry_times)
		{
			bool ret = true;
			::sofa::pbrpc::RpcController controller;
			controller.SetTimeout(1000);
			for (int32_t retry_time = 0;retry_time < retry_times;++retry_time)
			{
				(stub->*func)(&controller,request,response,NULL);

			}
		}
	}
}
