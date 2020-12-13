// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: movement.proto

#include "movement.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace lambda {
class MovementDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Movement> _instance;
} _Movement_default_instance_;
}  // namespace lambda
static void InitDefaultsscc_info_Movement_movement_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::lambda::_Movement_default_instance_;
    new (ptr) ::lambda::Movement();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Movement_movement_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Movement_movement_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_movement_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_movement_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_movement_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_movement_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::lambda::Movement, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::lambda::Movement, direction_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::lambda::Movement)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::lambda::_Movement_default_instance_),
};

const char descriptor_table_protodef_movement_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016movement.proto\022\006lambda\"\247\001\n\010Movement\022-\n"
  "\tdirection\030\001 \001(\0162\032.lambda.Movement.Direc"
  "tion\"l\n\tDirection\022\006\n\002UP\020\000\022\010\n\004DOWN\020\001\022\010\n\004L"
  "EFT\020\002\022\t\n\005RIGHT\020\003\022\013\n\007UP_LEFT\020\004\022\014\n\010UP_RIGH"
  "T\020\005\022\r\n\tDOWN_LEFT\020\006\022\016\n\nDOWN_RIGHT\020\007b\006prot"
  "o3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_movement_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_movement_2eproto_sccs[1] = {
  &scc_info_Movement_movement_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_movement_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_movement_2eproto = {
  false, false, descriptor_table_protodef_movement_2eproto, "movement.proto", 202,
  &descriptor_table_movement_2eproto_once, descriptor_table_movement_2eproto_sccs, descriptor_table_movement_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_movement_2eproto::offsets,
  file_level_metadata_movement_2eproto, 1, file_level_enum_descriptors_movement_2eproto, file_level_service_descriptors_movement_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_movement_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_movement_2eproto)), true);
namespace lambda {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Movement_Direction_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_movement_2eproto);
  return file_level_enum_descriptors_movement_2eproto[0];
}
bool Movement_Direction_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr Movement_Direction Movement::UP;
constexpr Movement_Direction Movement::DOWN;
constexpr Movement_Direction Movement::LEFT;
constexpr Movement_Direction Movement::RIGHT;
constexpr Movement_Direction Movement::UP_LEFT;
constexpr Movement_Direction Movement::UP_RIGHT;
constexpr Movement_Direction Movement::DOWN_LEFT;
constexpr Movement_Direction Movement::DOWN_RIGHT;
constexpr Movement_Direction Movement::Direction_MIN;
constexpr Movement_Direction Movement::Direction_MAX;
constexpr int Movement::Direction_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

class Movement::_Internal {
 public:
};

Movement::Movement(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:lambda.Movement)
}
Movement::Movement(const Movement& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  direction_ = from.direction_;
  // @@protoc_insertion_point(copy_constructor:lambda.Movement)
}

void Movement::SharedCtor() {
  direction_ = 0;
}

Movement::~Movement() {
  // @@protoc_insertion_point(destructor:lambda.Movement)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Movement::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void Movement::ArenaDtor(void* object) {
  Movement* _this = reinterpret_cast< Movement* >(object);
  (void)_this;
}
void Movement::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Movement::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Movement& Movement::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Movement_movement_2eproto.base);
  return *internal_default_instance();
}


void Movement::Clear() {
// @@protoc_insertion_point(message_clear_start:lambda.Movement)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  direction_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Movement::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .lambda.Movement.Direction direction = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_direction(static_cast<::lambda::Movement_Direction>(val));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Movement::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:lambda.Movement)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .lambda.Movement.Direction direction = 1;
  if (this->direction() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_direction(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:lambda.Movement)
  return target;
}

size_t Movement::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:lambda.Movement)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .lambda.Movement.Direction direction = 1;
  if (this->direction() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_direction());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Movement::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:lambda.Movement)
  GOOGLE_DCHECK_NE(&from, this);
  const Movement* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Movement>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:lambda.Movement)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:lambda.Movement)
    MergeFrom(*source);
  }
}

void Movement::MergeFrom(const Movement& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:lambda.Movement)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.direction() != 0) {
    _internal_set_direction(from._internal_direction());
  }
}

void Movement::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:lambda.Movement)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Movement::CopyFrom(const Movement& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:lambda.Movement)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Movement::IsInitialized() const {
  return true;
}

void Movement::InternalSwap(Movement* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(direction_, other->direction_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Movement::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace lambda
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::lambda::Movement* Arena::CreateMaybeMessage< ::lambda::Movement >(Arena* arena) {
  return Arena::CreateMessageInternal< ::lambda::Movement >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
