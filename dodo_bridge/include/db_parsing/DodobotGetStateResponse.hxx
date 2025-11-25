#ifndef DB_PARSING_DODOBOTGETSTATERESPONSE_HXX
#define DB_PARSING_DODOBOTGETSTATERESPONSE_HXX

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
struct DodobotGetStateResponse_
{
  typedef DodobotGetStateResponse_<ContainerAllocator> Type;

  DodobotGetStateResponse_()
    : ready(false)
    , reporting(false)
    , active(false)  {
    }
  DodobotGetStateResponse_(const ContainerAllocator& _alloc)
    : ready(false)
    , reporting(false)
    , active(false)  {
  (void)_alloc;
    }

  typedef uint8_t _ready_type;
  _ready_type ready;

  typedef uint8_t _reporting_type;
  _reporting_type reporting;

  typedef uint8_t _active_type;
  _active_type active;

  typedef std::shared_ptr< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotGetStateResponse_

typedef ::db_parsing::DodobotGetStateResponse_<std::allocator<void> > DodobotGetStateResponse;

typedef std::shared_ptr< ::db_parsing::DodobotGetStateResponse > DodobotGetStateResponsePtr;
typedef std::shared_ptr< ::db_parsing::DodobotGetStateResponse const> DodobotGetStateResponseConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4c01d362382e7c93b8d729b6e9ad99c8";
  }

  static const char* value(const ::db_parsing::DodobotGetStateResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4c01d362382e7c93ULL;
  static const uint64_t static_value2 = 0xb8d729b6e9ad99c8ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotGetStateResponse";
  }

  static const char* value(const ::db_parsing::DodobotGetStateResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool ready\nbool reporting\nbool active\n\
";
  }

  static const char* value(const ::db_parsing::DodobotGetStateResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ready);
      stream.next(m.reporting);
      stream.next(m.active);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotGetStateResponse_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotGetStateResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotGetStateResponse_<ContainerAllocator>& v)
  {
    s << indent << "ready: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.ready);
    s << indent << "reporting: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.reporting);
    s << indent << "active: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.active);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTGETSTATERESPONSE_HXX
