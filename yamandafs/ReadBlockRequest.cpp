#include "ReadBlockRequest.h"


namespace yamanda
{
	namespace ymdfs
	{
		ReadBlockRequest::ReadBlockRequest()
		{
		}


		ReadBlockRequest::~ReadBlockRequest()
		{
		}

		void ReadBlockRequest::set_sequence_id(int64_t sequence_id)
		{
			sequence_id_ = sequence_id;
		}

		void ReadBlockRequest::set_block_id(int64_t block_id)
		{
			block_id_ = block_id;
		}

		void ReadBlockRequest::set_offset(int64_t offset)
		{
			offset_ = offset;
		}

		void ReadBlockRequest::set_read_len(int32_t len)
		{
			read_len_ = len;
		}

		int64_t ReadBlockRequest::block_id() const
		{
			return block_id_;
		}

		int64_t ReadBlockRequest::offset() const
		{
			return offset_;
		}
		int32_t ReadBlockRequest::read_len() const
		{
			return read_len_;
		}
		int64_t ReadBlockRequest::sequence_id() const
		{
			return sequence_id_;
		}
	}
}

