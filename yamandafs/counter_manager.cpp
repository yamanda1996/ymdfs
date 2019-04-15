#include "counter_manager.h"



namespace yamanda
{
	namespace ymdfs
	{

		
		common::Counter g_find_ops;			//查询操作计数
		common::Counter g_read_ops;			//全局读操作计数
		common::Counter g_read_bytes;		//全局读取字节数

		counter_manager::counter_manager()
		{
		}


		counter_manager::~counter_manager()
		{
		}
	}
}


