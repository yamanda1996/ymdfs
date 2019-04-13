#pragma once
#include <stdint.h>
#include <limits>


namespace yamanda
{
	namespace ymdfs
	{
		//ÓÃÓÚ¶¯Ì¬À©ÈÝ
		uint64_t tableSizeFor(uint64_t cap)
		{
			uint64_t n = cap - 1;
			n |= n >> 1;
			n |= n >> 2;
			n |= n >> 4;
			n |= n >> 8;
			n |= n >> 16;
			n |= n >> 32;
			return (n < 0) ? 1 : (n >= std::numeric_limits<uint64_t>::max()) ?
				std::numeric_limits<uint64_t>::max() : n + 1;
		}

		
	}
}