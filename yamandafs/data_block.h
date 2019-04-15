#pragma once
#include <assert.h>
#include <algorithm>
#include <vector>

#include "Common.h"
#include "file_cache.h"
#include "counter_manager.h"
#include "Disk.h"

namespace yamanda
{
	namespace ymdfs
	{
#define WRONG_PARAM				-1
//BlockÒÑ¾­±»É¾³ý
#define DEL_BLOCK				-2	
#define READ_FILE_FAIL			-3
#define FLAGS_write_buf_size	4*1024

		class BlockMeta
		{
		public:
			BlockMeta(std::string store_path,int64_t block_id);
			virtual ~BlockMeta();
			int64_t block_size() const;
			void set_block_size(int64_t size);
			std::string store_path() const;
			int64_t block_id() const;

		private:


		private:
			int64_t				block_size_;
			std::string			store_path_;
			int64_t				block_id_;
		};

		class Data_Block
		{
		public:
			Data_Block(const BlockMeta &meta, Disk* disk);
			virtual ~Data_Block();
			int AddRef();
			int64_t Read(char *buf,int64_t len,int64_t offset);
			std::string BuildFilePath(int64_t block_id);
			int DecRef();

		private:


		private:
			volatile int		refs_;
			Common*				common_;
			char*				blockbuf_;
			std::mutex			mutex_;
			BlockMeta			meta_;
			volatile bool		deleted_;
			int64_t				disk_file_size_;
			std::string			disk_file_;

			File_Cache*			file_cache_;
			std::vector<std::pair<const char*, int>> block_buf_list_;
			int64_t				bufdatalen_;

			Disk*				disk_;

		};
	}
}


