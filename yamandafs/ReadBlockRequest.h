#pragma once
#include <stdint.h>


namespace yamanda
{
	namespace ymdfs
	{
		class ReadBlockRequest
		{
		public:
			ReadBlockRequest();
			virtual ~ReadBlockRequest();
			void set_sequence_id(int64_t sequence_id);
			void set_block_id(int64_t block_id);
			void set_offset(int64_t offset);
			void set_read_len(int32_t len);
			int64_t block_id() const;
			int64_t offset() const;
			int32_t read_len() const;
			int64_t sequence_id() const;


		private:
			int64_t sequence_id_;
			int64_t block_id_;
			int64_t offset_;
			int32_t read_len_;
		};

	}
}


