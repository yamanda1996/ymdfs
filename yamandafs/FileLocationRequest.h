#pragma once
#include <string.h>

namespace yamanda
{

	namespace ymdfs
	{
		const int MAX_FILENAME_LEN = 128;

		class FileLocationRequest
		{
		public:
			FileLocationRequest();
			virtual ~FileLocationRequest();

			void set_filename(const char *filename) 
			{
				strcpy(filename_, filename);
				filename_[strlen(filename)] = '\0';

			}
			void set_sequence_id(const int id)
			{
				sequence_id_ = id;
			}


		private:
			char filename_[MAX_FILENAME_LEN];
			int sequence_id_;
		};

	}
}


