#pragma once

#include <stdint.h>
#include <string>

#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"
#include "google/protobuf/has_bits.h"
#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/service.h>
#include <google/protobuf/unknown_field_set.h>

namespace yamanda
{

	namespace ymdfs
	{

		class ChunkServerInfo
		{
		public:
			
			inline std::string address() const;
			ChunkServerInfo();
			virtual ~ChunkServerInfo();

		private:
			std::string address_;

		};
		class nameserver
		{
		public:
			nameserver();
			virtual ~nameserver();
		};


		class LocatedBlock :public ::google::protobuf::Message
		{
		public:
			LocatedBlock();
			virtual ~LocatedBlock();
			//默认一个Block存三份
			int chains_size() const;
			int64_t block_size() const;
			int64_t block_id() const;

			const ChunkServerInfo& chains(int index) const;

			void CopyFrom(const ::google::protobuf::Message &from) final;
			void MergeFrom(const ::google::protobuf::Message &from) final;

			void Clear();

			;;google::protobuf:: Message* New() const;

			::google::protobuf::Metadata GetMetadata() const;

			int GetCachedSize() const;


		private:
			int64_t block_size_;
			int64_t block_id_;
			::google::protobuf::RepeatedPtrField<yamanda::ymdfs::ChunkServerInfo> chains_;
			::google::protobuf::internal::HasBits<1> _has_bits_;
			::google::protobuf::int32 status_;
			::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;

		};
	}
}


