#pragma once
#include <stdint.h>
#include <vector>


#include "Common.h"
#include "utils.h"


namespace yamanda
{
	namespace ymdfs
	{
#define kBadParameter 1

		class ReadBlockResponse
		{
			class MutableDatabuf;
		public:
			ReadBlockResponse();
			ReadBlockResponse(int64_t sequence_id);
			virtual ~ReadBlockResponse();
			void set_status(int st);
			bool has_sequence_id();
			void set_sequence_id(int64_t sequence_id);
			void add_timestamp();
			MutableDatabuf* mutable_databuf();
			int64_t timestamp(int n) const;
			int status();

		public:
			class MutableDatabuf
			{
			public:
				MutableDatabuf(): databuf_len_(128),data_size_(0)
				{
					mutable_databuf_ = new char[databuf_len_];
				}

				virtual ~MutableDatabuf()
				{
					if (nullptr != mutable_databuf_)
					{
						delete mutable_databuf_;
						mutable_databuf_ = nullptr;
					}
				}
				int assign(const char* buf,int64_t len)
				{
					int ret = 0;
					if (databuf_len_ < len)
					{
						delete mutable_databuf_;
						uint64_t mutable_len = tableSizeFor(len);
						mutable_databuf_ = new char[mutable_len];
						databuf_len_ = mutable_len;
					}
					memcpy(mutable_databuf_, buf, len);
					data_size_ = len;
					return ret;
				}

				const char* data() const
				{
					return mutable_databuf_;
				}

				int64_t size()
				{
					return data_size_;
				}

			private:
				char*				mutable_databuf_;
				int64_t				databuf_len_;
				int64_t				data_size_;
			};

		private:
			int						status_;
			int64_t					sequence_id_;
			int64_t					time_stamp_;
			Common*					common_;
			MutableDatabuf*			mutable_databuf_;
			std::vector<int64_t>	timestamps_;

		};
	}
}


