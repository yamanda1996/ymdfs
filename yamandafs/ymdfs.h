#pragma once
#include <stdint.h>


namespace yamanda 
{
	namespace ymdfs 
	{
		const int OK = 0;
		const int BAD_PARAMETER = -1;
		const int PERMISSION_DENIED = -2;
		const int NOT_ENOUGH_QUOTA = -3;
		const int NETWORK_UNAVAILABLE = -4;
		const int TIMEOUT = -5;
		const int NOT_ENOUGH_SPACE = -6;
		const int OVERLOAD = -7;
		const int META_NOT_AVAILABLE = -8;
		const int UNKNOWN_ERROR = -9;


		enum WriteMode
		{
			kWriteDefault,
			kWriteChains,
			kWriteFanout
		};

		struct ReadOption
		{
			int timeout;	//��msΪ��λ��<0��ʶtimeout��Ч��==0��ʾ���ȴ�
			ReadOption() :timeout(-1) {}
		};

		struct WriteOption
		{
			int flush_timeout;	//��msΪ��λ��<0��ʶtimeout��Ч��==0��ʾ���ȴ�
			int sync_timeout;	//��msΪ��λ��<0��ʶtimeout��Ч��==0��ʾ���ȴ�
			int close_timeout;	//��msΪ��λ��<0��ʶtimeout��Ч��==0��ʾ���ȴ�
			int replica;		//��������
			WriteMode write_mode;
			bool sync_on_close;		//�ر�File��ʱ�����̽�����д�����
			WriteOption() :flush_timeout(-1),sync_timeout(-1),close_timeout(-1),replica(-1),
							write_mode(kWriteDefault),sync_on_close(false){}
		};

		class File
		{
		public:
			File();
			virtual ~File();
			virtual int32_t Pread(char *buf,int32_t read_size,int64_t offset,bool reada = false) = 0;
			virtual int32_t Read(char *buf,int32_t read_size) = 0;
			virtual int32_t Write(const char *buf,int32_t write_size) = 0;
			virtual int32_t Seek(int64_t offset,int32_t whence) = 0;
			virtual int32_t Flush() = 0;
			virtual int32_t Sync() = 0;
			virtual int32_t Close() = 0;
		private:
			//��ֵ�Ϳ���������ʹ��
			File(const File &);
			File &operator=(const File &);

		};

		class ymdfs
		{
		public:
			ymdfs();
			virtual ~ymdfs();

			virtual int32_t OpenFile(const char *path,int32_t flags,File **file,
										const ReadOption &options) = 0;
			virtual int32_t OpenFile(const char *path, int32_t flags, File **file, 
										const WriteOption &options) = 0;
			virtual int32_t OpenFile(const char *path, int32_t flags,int32_t mode, 
										File **file, const WriteOption &options) = 0;
			virtual int32_t DeleteFile(const char *path) = 0;

		private:
			//��ֵ�������Ϳ������캯��������ʹ��
			ymdfs(const ymdfs&);
			ymdfs& operator=(const ymdfs&);
		};


	

	}
}


