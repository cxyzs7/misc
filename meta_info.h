#ifndef _META_INFO_H
#define _META_INFO_H

#include <string>
#include <typeinfo>

//! struct to contain meta info for each class member
struct member_meta
{
  member_meta() {}
  member_meta(const char* _type, const char* _name, const size_t _size, const size_t _offset):type(_type), name(_name), size(_size), offset(_offset) { }
  const char* type;
  const char* name;
  size_t size;
  size_t offset;
};

//! macro to create a member_meta
#define MEMBER_INFO(STRUCT, FIELD) member_meta(typeid(((STRUCT*)0)->FIELD).name(), #FIELD, sizeof ((STRUCT*)0)->FIELD, offsetof(STRUCT, FIELD))

//! template class for class meta data
template<class STRUCT>
struct class_meta
{
  class_meta():num_members(0), members(0) {}
  int num_members;
  member_meta* members;
};

// ugly way to initialize members
#define ADD_MEMBER_1(STRUCT, a)                                                        members[0] = MEMBER_INFO(STRUCT, a);
#define ADD_MEMBER_2(STRUCT, a, b)               ADD_MEMBER_1(STRUCT, a)              members[1] = MEMBER_INFO(STRUCT, b);
#define ADD_MEMBER_3(STRUCT, a, b, c)            ADD_MEMBER_2(STRUCT, a, b)           members[2] = MEMBER_INFO(STRUCT, c);
#define ADD_MEMBER_4(STRUCT, a, b, c, d)         ADD_MEMBER_3(STRUCT, a, b, c)        members[3] = MEMBER_INFO(STRUCT, d);
#define ADD_MEMBER_5(STRUCT, a, b, c, d, e)      ADD_MEMBER_4(STRUCT, a, b, c, d)     members[4] = MEMBER_INFO(STRUCT, e);
#define ADD_MEMBER_6(STRUCT, a, b, c, d, e, f)   ADD_MEMBER_5(STRUCT, a, b, c, d, e)  members[5] = MEMBER_INFO(STRUCT, f);

//! template specialization
//! e.g. call META(data, 3, x1, x2, x3); after defining
//! struct data { int x1; double x2; char x3; };
//! then you can use class_meta<data> to get class meta info
#define META(STRUCT, COUNT, ...)              \
template<>                                    \
struct class_meta<STRUCT> {                   \
  class_meta():num_members(COUNT) {           \
    members = new member_meta[num_members];   \
    ADD_MEMBER_##COUNT(STRUCT, __VA_ARGS__)      \
  }                                           \
  ~class_meta() { delete[] members; }         \
  int num_members;                            \
  member_meta* members;                       \
};

#endif