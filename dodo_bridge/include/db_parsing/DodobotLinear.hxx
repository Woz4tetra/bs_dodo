#ifndef DB_PARSING_DODOBOTLINEAR_HXX
#define DB_PARSING_DODOBOTLINEAR_HXX

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
struct DodobotLinear_
{
  typedef DodobotLinear_<ContainerAllocator> Type;

  DodobotLinear_()
    : header()
    , position(0)
    , has_error(false)
    , is_homed(false)
    , is_active(false)
    , command_type(0)
    , command_value(0)
    , max_speed(0)
    , acceleration(0)  {
    }
  DodobotLinear_(const ContainerAllocator& _alloc)
    : header()
    , position(0)
    , has_error(false)
    , is_homed(false)
    , is_active(false)
    , command_type(0)
    , command_value(0)
    , max_speed(0)
    , acceleration(0)  {
  (void)_alloc;
    }

  typedef Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef int32_t _position_type;
  _position_type position;

  typedef uint8_t _has_error_type;
  _has_error_type has_error;

  typedef uint8_t _is_homed_type;
  _is_homed_type is_homed;

  typedef uint8_t _is_active_type;
  _is_active_type is_active;

  typedef uint8_t _command_type_type;
  _command_type_type command_type;

  typedef int32_t _command_value_type;
  _command_value_type command_value;

  typedef int32_t _max_speed_type;
  _max_speed_type max_speed;

  typedef int32_t _acceleration_type;
  _acceleration_type acceleration;

  typedef std::shared_ptr< ::db_parsing::DodobotLinear_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotLinear_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotLinear_

typedef ::db_parsing::DodobotLinear_<std::allocator<void> > DodobotLinear;

typedef std::shared_ptr< ::db_parsing::DodobotLinear > DodobotLinearPtr;
typedef std::shared_ptr< ::db_parsing::DodobotLinear const> DodobotLinearConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotLinear_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotLinear_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotLinear_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotLinear_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotLinear_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotLinear_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotLinear_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotLinear_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotLinear_<ContainerAllocator> >
{
  static const char* value()
  {
    return "48cd0f7c129e2f02db82f0e554e790cc";
  }

  static const char* value(const ::db_parsing::DodobotLinear_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x48cd0f7c129e2f02ULL;
  static const uint64_t static_value2 = 0xdb82f0e554e790ccULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotLinear_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotLinear";
  }

  static const char* value(const ::db_parsing::DodobotLinear_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotLinear_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\nint32 position\nbool has_error\nbool is_homed\nbool is_active\n\nuint8 command_type\nint32 command_value\nint32 max_speed\nint32 acceleration\n\n\
";
  }

  static const char* value(const ::db_parsing::DodobotLinear_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotLinear_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.position);
      stream.next(m.has_error);
      stream.next(m.is_homed);
      stream.next(m.is_active);
      stream.next(m.command_type);
      stream.next(m.command_value);
      stream.next(m.max_speed);
      stream.next(m.acceleration);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotLinear_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotLinear_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotLinear_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer<Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "position: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.position);
    s << indent << "has_error: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.has_error);
    s << indent << "is_homed: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.is_homed);
    s << indent << "is_active: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.is_active);
    s << indent << "command_type: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.command_type);
    s << indent << "command_value: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.command_value);
    s << indent << "max_speed: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.max_speed);
    s << indent << "acceleration: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.acceleration);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTLINEAR_HXX
