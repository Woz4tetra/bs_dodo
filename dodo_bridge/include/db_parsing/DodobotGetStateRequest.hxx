#ifndef DB_PARSING_DODOBOTGETSTATEREQUEST_HXX
#define DB_PARSING_DODOBOTGETSTATEREQUEST_HXX

#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>

#include <miniros/types.h>
#include <miniros/serialization.h>
#include <miniros/traits/builtin_message_traits.h>
#include <miniros/message_operations.h>

namespace db_parsing
{

template <class ContainerAllocator>
struct DodobotGetStateRequest_
{
  typedef DodobotGetStateRequest_<ContainerAllocator> Type;

  DodobotGetStateRequest_()
  {
    }
  DodobotGetStateRequest_(const ContainerAllocator& _alloc)
  {
  (void)_alloc;
    }

  typedef std::shared_ptr< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotGetStateRequest_

typedef ::db_parsing::DodobotGetStateRequest_<std::allocator<void> > DodobotGetStateRequest;

typedef std::shared_ptr< ::db_parsing::DodobotGetStateRequest > DodobotGetStateRequestPtr;
typedef std::shared_ptr< ::db_parsing::DodobotGetStateRequest const> DodobotGetStateRequestConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::db_parsing::DodobotGetStateRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotGetStateRequest";
  }

  static const char* value(const ::db_parsing::DodobotGetStateRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
";
  }

  static const char* value(const ::db_parsing::DodobotGetStateRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotGetStateRequest_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotGetStateRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotGetStateRequest_<ContainerAllocator>& v)
  {
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTGETSTATEREQUEST_HXX
