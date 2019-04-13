#include "ReadBlockResponse.h"

namespace yamanda
{
	namespace ymdfs
	{
		ReadBlockResponse::ReadBlockResponse():sequence_id_(-1)
		{
			common_ = new Common;
			mutable_databuf_ = new MutableDatabuf;
			
		}

		ReadBlockResponse::ReadBlockResponse(int64_t sequence_id):
			sequence_id_(sequence_id)
		{
			mutable_databuf_ = new MutableDatabuf;
		}


		ReadBlockResponse::~ReadBlockResponse()
		{
			if (nullptr != common_)
			{
				delete common_;
				common_ = nullptr;
			}
			if (nullptr != mutable_databuf_)
			{
				delete mutable_databuf_;
				mutable_databuf_ = nullptr;
			}

		}

		void ReadBlockResponse::set_status(int st)
		{
			status_ = st;
		}

		bool ReadBlockResponse::has_sequence_id()
		{
			return -1 != sequence_id_;
		}

		void ReadBlockResponse::set_sequence_id(int64_t sequence_id)
		{
			sequence_id_ = sequence_id;
		}

		void ReadBlockResponse::add_timestamp()
		{
			time_stamp_ = common_->get_micros_time();
		}

		ReadBlockResponse::MutableDatabuf* ReadBlockResponse::mutable_databuf()
		{
			return mutable_databuf_;
		}

	}
}


