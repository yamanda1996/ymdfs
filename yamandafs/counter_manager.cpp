#include "counter_manager.h"



namespace yamanda
{
	namespace ymdfs
	{

		
		common::Counter g_find_ops;			//��ѯ��������
		common::Counter g_read_ops;			//ȫ�ֶ���������
		common::Counter g_read_bytes;		//ȫ�ֶ�ȡ�ֽ���

		counter_manager::counter_manager()
		{
		}


		counter_manager::~counter_manager()
		{
		}
	}
}


