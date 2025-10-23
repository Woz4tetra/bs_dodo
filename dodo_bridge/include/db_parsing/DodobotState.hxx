#ifndef DB_PARSING_DODOBOTSTATE_HXX
#define DB_PARSING_DODOBOTSTATE_HXX

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
struct DodobotState_
{
  typedef DodobotState_<ContainerAllocator> Type;

  DodobotState_()
    : header()
    , battery_ok(false)
    , motors_active(false)
    , loop_rate(0.0)
    , is_ready(false)
    , robot_name()  {
    }
  DodobotState_(const ContainerAllocator& _alloc)
    : header()
    , battery_ok(false)
    , motors_active(false)
    , loop_rate(0.0)
    , is_ready(false)
    , robot_name(_alloc)  {
  (void)_alloc;
    }

  typedef Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef uint8_t _battery_ok_type;
  _battery_ok_type battery_ok;

  typedef uint8_t _motors_active_type;
  _motors_active_type motors_active;

  typedef float _loop_rate_type;
  _loop_rate_type loop_rate;

  typedef uint8_t _is_ready_type;
  _is_ready_type is_ready;

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _robot_name_type;
  _robot_name_type robot_name;

  typedef std::shared_ptr< ::db_parsing::DodobotState_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotState_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotState_

typedef ::db_parsing::DodobotState_<std::allocator<void> > DodobotState;

typedef std::shared_ptr< ::db_parsing::DodobotState > DodobotStatePtr;
typedef std::shared_ptr< ::db_parsing::DodobotState const> DodobotStateConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotState_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotState_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotState_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotState_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotState_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotState_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotState_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotState_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8f1ba2512049f0c4cfc0d584937a9ef2";
  }

  static const char* value(const ::db_parsing::DodobotState_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8f1ba2512049f0c4ULL;
  static const uint64_t static_value2 = 0xcfc0d584937a9ef2ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotState";
  }

  static const char* value(const ::db_parsing::DodobotState_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\nbool battery_ok\nbool motors_active\nfloat32 loop_rate\nbool is_ready\nstring robot_name\n\n\
";
  }

  static const char* value(const ::db_parsing::DodobotState_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotState_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.battery_ok);
      stream.next(m.motors_active);
      stream.next(m.loop_rate);
      stream.next(m.is_ready);
      stream.next(m.robot_name);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotState_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotState_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotState_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer<Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "battery_ok: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.battery_ok);
    s << indent << "motors_active: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.motors_active);
    s << indent << "loop_rate: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.loop_rate);
    s << indent << "is_ready: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.is_ready);
    s << indent << "robot_name: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.robot_name);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTSTATE_HXX
