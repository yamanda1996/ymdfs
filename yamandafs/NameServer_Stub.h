#pragma once

namespace yamanda
{

	namespace ymdfs
	{

		typedef void *(*call_back)(void *);
		/*void *call_back(void *argc)
		{
			return NULL;
		}*/

		class NameServer_Stub
		{
		public:
			NameServer_Stub();
			~NameServer_Stub();

			
			void GetFileLocation(google::protobuf::RpcController *,
				const FileLocationRequest *, FileLocationResponse *, call_back)
			{
				return;
			}

		};
	}
}


