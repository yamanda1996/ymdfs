#include "nameserver.h"



namespace yamanda
{

	namespace ymdfs
	{
		nameserver::nameserver()
		{
		}


		nameserver::~nameserver()
		{
		}


		LocatedBlock::LocatedBlock()
		{
			
		}
		LocatedBlock::~LocatedBlock()
		{

		}

		int LocatedBlock::chains_size() const
		{
			return 3;
		}

		int64_t LocatedBlock::block_size() const
		{
			return block_size_;
		}

		int64_t LocatedBlock::block_id() const
		{
			return block_id_;
		}

		void LocatedBlock::CopyFrom(const ::google::protobuf::Message &from)
		{
			if (this == &from)
			{
				return;
			}
			Clear();
			MergeFrom(from);

		}


		void LocatedBlock::MergeFrom(const ::google::protobuf::Message &from)
		{
			GOOGLE_DCHECK_NE(&from,this);
			const LocatedBlock *source = 
				::google::protobuf::DynamicCastToGenerated<LocatedBlock>(&from);
			if (nullptr == source)
			{
				::google::protobuf::internal::ReflectionOps::Merge(from, this);
			}
			else
			{
				MergeFrom(*source);
			}
		}

		

		void LocatedBlock::Clear()
		{
			::google::protobuf::uint32 cached_has_bits = 0;
			(void)cached_has_bits;
			chains_.Clear();
			cached_has_bits = _has_bits_[0];

			if (cached_has_bits & 0x00000007u)
			{
				::memset(&block_id_, 0, static_cast<size_t>(
					reinterpret_cast<char *>(&status_) - 
					reinterpret_cast<char *>(&block_id_)) + sizeof(status_));
			}
			_has_bits_.Clear();
			_internal_metadata_.Clear();

		}

		::google::protobuf::Message* LocatedBlock::New() const
		{
			return NULL;
		}

		::google::protobuf::Metadata LocatedBlock::GetMetadata() const
		{

			::google::protobuf::Metadata *metadata = new ::google::protobuf::Metadata;
			return *metadata;
		}

		int LocatedBlock::GetCachedSize() const
		{
			return block_size_;
		}


		ChunkServerInfo::ChunkServerInfo()
		{
			
		}
		ChunkServerInfo::~ChunkServerInfo()
		{
			
		}

		const ChunkServerInfo& LocatedBlock::chains(int index) const
		{
			return chains_.Get(index);
		}

		inline std::string ChunkServerInfo::address() const
		{
			return address_;
		}
	}

}


