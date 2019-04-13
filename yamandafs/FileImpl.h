#pragma once
#include <string>
#include <mutex>
#include <stdint.h>
#include <assert.h>
#include <atomic>
#include <vector>
#include <functional>

#include "ymdfs.h"
#include "Common.h"
#include "nameserver.h"
#include "chunkserver.h"
#include "ymdfs_impl.h"
#include "ReadBlockRequest.h"
#include "ReadBlockResponse.h"

#define FLAGS_sdk_file_reada_len 4*1024*1024*1024

namespace yamanda
{

	namespace ymdfs
	{

		class WriteBuffer 
		{
		public:
			WriteBuffer(int32_t seq, int32_t buf_size, int64_t block_id, int64_t offset);
			virtual ~WriteBuffer();
			int Available() const;
			int Append(const char *buf,int len);
			const char* Data() const;
			int Size() const;
			int Sequence() const;
			void Clear();
			void SetLast();
			bool IsLast() const;
			int64_t offset() const;
			int64_t block_id() const;
			void AddRefBy(int counter);
			void AddRef();
			void DecRef();


		private:
			int32_t buf_size_;
			int32_t data_size_;
			char *buf_;
			int64_t block_id_;
			int64_t offset_;
			int32_t seq_id_;
			bool is_last_;
			volatile int refs_;
			Common common_;
		};

		struct LocatedBlocks
		{
			int64_t file_length_;
			std::vector<LocatedBlock> blocks_;
			void CopyFrom(const ::google::protobuf::RepeatedPtrFiled<LocatedBlock> &blocks)
			{
				for (int i = 0;i < blocks.size();++i)
				{
					blocks_.push_back(blocks.Get(i));
				}
			}


		};

		class FileImpl:public File
		{
		public:
			FileImpl(ymdfs_impl *ymdfs, std::string name);
			virtual ~FileImpl();


			int32_t Pread(char *buf, int32_t read_size, int64_t offset, bool reada = false);
			int32_t Read(char *buf, int32_t read_size);
			int32_t Write(const char *buf, int32_t write_size);
			int32_t Seek(int64_t offset, int32_t whence);
			int32_t Flush();
			int32_t Sync();
			int32_t Close();

		private:
			ymdfs_impl *ymdfs_;

			std::string name_;
			std::mutex mutex_;
			//上一次读取的偏移量
			int64_t last_read_offset_;
			//顺序读取比例
			int32_t sequential_ratio_;
			char * reada_buf_;
			int64_t reada_base_;
			int32_t reada_buf_len_;

			//Block默认保存三份，所以chains_size默认就是3
			LocatedBlocks located_blocks_;
			int32_t last_chunkserver_index_;
			ChunkServer_Stub *chunkserver_stub_;



			Common *common_;


		};
	}
}



