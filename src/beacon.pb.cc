// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: beacon.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "beacon.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace beacon {

namespace {

const ::google::protobuf::Descriptor* Election_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Election_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_beacon_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_beacon_2eproto() {
  protobuf_AddDesc_beacon_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "beacon.proto");
  GOOGLE_CHECK(file != NULL);
  Election_descriptor_ = file->message_type(0);
  static const int Election_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Election, is_leader_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Election, last_node_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Election, added_node_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Election, removed_node_id_),
  };
  Election_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Election_descriptor_,
      Election::default_instance_,
      Election_offsets_,
      -1,
      -1,
      -1,
      sizeof(Election),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Election, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Election, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_beacon_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Election_descriptor_, &Election::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_beacon_2eproto() {
  delete Election::default_instance_;
  delete Election_reflection_;
}

void protobuf_AddDesc_beacon_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_beacon_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014beacon.proto\022\006beacon\"c\n\010Election\022\021\n\tis"
    "_leader\030\001 \001(\005\022\024\n\014last_node_id\030\002 \001(\r\022\025\n\ra"
    "dded_node_id\030\003 \003(\r\022\027\n\017removed_node_id\030\004 "
    "\003(\rb\006proto3", 131);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "beacon.proto", &protobuf_RegisterTypes);
  Election::default_instance_ = new Election();
  Election::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_beacon_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_beacon_2eproto {
  StaticDescriptorInitializer_beacon_2eproto() {
    protobuf_AddDesc_beacon_2eproto();
  }
} static_descriptor_initializer_beacon_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Election::kIsLeaderFieldNumber;
const int Election::kLastNodeIdFieldNumber;
const int Election::kAddedNodeIdFieldNumber;
const int Election::kRemovedNodeIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Election::Election()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:beacon.Election)
}

void Election::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

Election::Election(const Election& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:beacon.Election)
}

void Election::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
  is_leader_ = 0;
  last_node_id_ = 0u;
}

Election::~Election() {
  // @@protoc_insertion_point(destructor:beacon.Election)
  SharedDtor();
}

void Election::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Election::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Election::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Election_descriptor_;
}

const Election& Election::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_beacon_2eproto();
  return *default_instance_;
}

Election* Election::default_instance_ = NULL;

Election* Election::New(::google::protobuf::Arena* arena) const {
  Election* n = new Election;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Election::Clear() {
// @@protoc_insertion_point(message_clear_start:beacon.Election)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(Election, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<Election*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(is_leader_, last_node_id_);

#undef ZR_HELPER_
#undef ZR_

  added_node_id_.Clear();
  removed_node_id_.Clear();
}

bool Election::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:beacon.Election)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 is_leader = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &is_leader_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_last_node_id;
        break;
      }

      // optional uint32 last_node_id = 2;
      case 2: {
        if (tag == 16) {
         parse_last_node_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &last_node_id_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_added_node_id;
        break;
      }

      // repeated uint32 added_node_id = 3;
      case 3: {
        if (tag == 26) {
         parse_added_node_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_added_node_id())));
        } else if (tag == 24) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 26, input, this->mutable_added_node_id())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_removed_node_id;
        break;
      }

      // repeated uint32 removed_node_id = 4;
      case 4: {
        if (tag == 34) {
         parse_removed_node_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_removed_node_id())));
        } else if (tag == 32) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 34, input, this->mutable_removed_node_id())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:beacon.Election)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:beacon.Election)
  return false;
#undef DO_
}

void Election::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:beacon.Election)
  // optional int32 is_leader = 1;
  if (this->is_leader() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->is_leader(), output);
  }

  // optional uint32 last_node_id = 2;
  if (this->last_node_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->last_node_id(), output);
  }

  // repeated uint32 added_node_id = 3;
  if (this->added_node_id_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(3, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(_added_node_id_cached_byte_size_);
  }
  for (int i = 0; i < this->added_node_id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32NoTag(
      this->added_node_id(i), output);
  }

  // repeated uint32 removed_node_id = 4;
  if (this->removed_node_id_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(4, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(_removed_node_id_cached_byte_size_);
  }
  for (int i = 0; i < this->removed_node_id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32NoTag(
      this->removed_node_id(i), output);
  }

  // @@protoc_insertion_point(serialize_end:beacon.Election)
}

::google::protobuf::uint8* Election::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:beacon.Election)
  // optional int32 is_leader = 1;
  if (this->is_leader() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->is_leader(), target);
  }

  // optional uint32 last_node_id = 2;
  if (this->last_node_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->last_node_id(), target);
  }

  // repeated uint32 added_node_id = 3;
  if (this->added_node_id_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      3,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
      _added_node_id_cached_byte_size_, target);
  }
  for (int i = 0; i < this->added_node_id_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32NoTagToArray(this->added_node_id(i), target);
  }

  // repeated uint32 removed_node_id = 4;
  if (this->removed_node_id_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      4,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
      _removed_node_id_cached_byte_size_, target);
  }
  for (int i = 0; i < this->removed_node_id_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32NoTagToArray(this->removed_node_id(i), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:beacon.Election)
  return target;
}

int Election::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:beacon.Election)
  int total_size = 0;

  // optional int32 is_leader = 1;
  if (this->is_leader() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->is_leader());
  }

  // optional uint32 last_node_id = 2;
  if (this->last_node_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->last_node_id());
  }

  // repeated uint32 added_node_id = 3;
  {
    int data_size = 0;
    for (int i = 0; i < this->added_node_id_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->added_node_id(i));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _added_node_id_cached_byte_size_ = data_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  // repeated uint32 removed_node_id = 4;
  {
    int data_size = 0;
    for (int i = 0; i < this->removed_node_id_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->removed_node_id(i));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _removed_node_id_cached_byte_size_ = data_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Election::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:beacon.Election)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const Election* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const Election>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:beacon.Election)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:beacon.Election)
    MergeFrom(*source);
  }
}

void Election::MergeFrom(const Election& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:beacon.Election)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  added_node_id_.MergeFrom(from.added_node_id_);
  removed_node_id_.MergeFrom(from.removed_node_id_);
  if (from.is_leader() != 0) {
    set_is_leader(from.is_leader());
  }
  if (from.last_node_id() != 0) {
    set_last_node_id(from.last_node_id());
  }
}

void Election::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:beacon.Election)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Election::CopyFrom(const Election& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:beacon.Election)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Election::IsInitialized() const {

  return true;
}

void Election::Swap(Election* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Election::InternalSwap(Election* other) {
  std::swap(is_leader_, other->is_leader_);
  std::swap(last_node_id_, other->last_node_id_);
  added_node_id_.UnsafeArenaSwap(&other->added_node_id_);
  removed_node_id_.UnsafeArenaSwap(&other->removed_node_id_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Election::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Election_descriptor_;
  metadata.reflection = Election_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Election

// optional int32 is_leader = 1;
void Election::clear_is_leader() {
  is_leader_ = 0;
}
 ::google::protobuf::int32 Election::is_leader() const {
  // @@protoc_insertion_point(field_get:beacon.Election.is_leader)
  return is_leader_;
}
 void Election::set_is_leader(::google::protobuf::int32 value) {
  
  is_leader_ = value;
  // @@protoc_insertion_point(field_set:beacon.Election.is_leader)
}

// optional uint32 last_node_id = 2;
void Election::clear_last_node_id() {
  last_node_id_ = 0u;
}
 ::google::protobuf::uint32 Election::last_node_id() const {
  // @@protoc_insertion_point(field_get:beacon.Election.last_node_id)
  return last_node_id_;
}
 void Election::set_last_node_id(::google::protobuf::uint32 value) {
  
  last_node_id_ = value;
  // @@protoc_insertion_point(field_set:beacon.Election.last_node_id)
}

// repeated uint32 added_node_id = 3;
int Election::added_node_id_size() const {
  return added_node_id_.size();
}
void Election::clear_added_node_id() {
  added_node_id_.Clear();
}
 ::google::protobuf::uint32 Election::added_node_id(int index) const {
  // @@protoc_insertion_point(field_get:beacon.Election.added_node_id)
  return added_node_id_.Get(index);
}
 void Election::set_added_node_id(int index, ::google::protobuf::uint32 value) {
  added_node_id_.Set(index, value);
  // @@protoc_insertion_point(field_set:beacon.Election.added_node_id)
}
 void Election::add_added_node_id(::google::protobuf::uint32 value) {
  added_node_id_.Add(value);
  // @@protoc_insertion_point(field_add:beacon.Election.added_node_id)
}
 const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Election::added_node_id() const {
  // @@protoc_insertion_point(field_list:beacon.Election.added_node_id)
  return added_node_id_;
}
 ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Election::mutable_added_node_id() {
  // @@protoc_insertion_point(field_mutable_list:beacon.Election.added_node_id)
  return &added_node_id_;
}

// repeated uint32 removed_node_id = 4;
int Election::removed_node_id_size() const {
  return removed_node_id_.size();
}
void Election::clear_removed_node_id() {
  removed_node_id_.Clear();
}
 ::google::protobuf::uint32 Election::removed_node_id(int index) const {
  // @@protoc_insertion_point(field_get:beacon.Election.removed_node_id)
  return removed_node_id_.Get(index);
}
 void Election::set_removed_node_id(int index, ::google::protobuf::uint32 value) {
  removed_node_id_.Set(index, value);
  // @@protoc_insertion_point(field_set:beacon.Election.removed_node_id)
}
 void Election::add_removed_node_id(::google::protobuf::uint32 value) {
  removed_node_id_.Add(value);
  // @@protoc_insertion_point(field_add:beacon.Election.removed_node_id)
}
 const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Election::removed_node_id() const {
  // @@protoc_insertion_point(field_list:beacon.Election.removed_node_id)
  return removed_node_id_;
}
 ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Election::mutable_removed_node_id() {
  // @@protoc_insertion_point(field_mutable_list:beacon.Election.removed_node_id)
  return &removed_node_id_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace beacon

// @@protoc_insertion_point(global_scope)