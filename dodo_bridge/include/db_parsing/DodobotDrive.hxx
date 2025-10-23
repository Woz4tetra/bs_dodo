#ifndef DB_PARSING_DODOBOTDRIVE_HXX
#define DB_PARSING_DODOBOTDRIVE_HXX

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
struct DodobotDrive_
{
  typedef DodobotDrive_<ContainerAllocator> Type;

  DodobotDrive_()
    : header()
    , left_setpoint(0.0)
    , right_setpoint(0.0)
    , left_enc_pos(0)
    , right_enc_pos(0)
    , left_enc_speed(0.0)
    , right_enc_speed(0.0)
    , left_bumper(false)
    , right_bumper(false)  {
    }
  DodobotDrive_(const ContainerAllocator& _alloc)
    : header()
    , left_setpoint(0.0)
    , right_setpoint(0.0)
    , left_enc_pos(0)
    , right_enc_pos(0)
    , left_enc_speed(0.0)
    , right_enc_speed(0.0)
    , left_bumper(false)
    , right_bumper(false)  {
  (void)_alloc;
    }

  typedef Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef float _left_setpoint_type;
  _left_setpoint_type left_setpoint;

  typedef float _right_setpoint_type;
  _right_setpoint_type right_setpoint;

  typedef int64_t _left_enc_pos_type;
  _left_enc_pos_type left_enc_pos;

  typedef int64_t _right_enc_pos_type;
  _right_enc_pos_type right_enc_pos;

  typedef float _left_enc_speed_type;
  _left_enc_speed_type left_enc_speed;

  typedef float _right_enc_speed_type;
  _right_enc_speed_type right_enc_speed;

  typedef uint8_t _left_bumper_type;
  _left_bumper_type left_bumper;

  typedef uint8_t _right_bumper_type;
  _right_bumper_type right_bumper;

  typedef std::shared_ptr< ::db_parsing::DodobotDrive_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotDrive_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotDrive_

typedef ::db_parsing::DodobotDrive_<std::allocator<void> > DodobotDrive;

typedef std::shared_ptr< ::db_parsing::DodobotDrive > DodobotDrivePtr;
typedef std::shared_ptr< ::db_parsing::DodobotDrive const> DodobotDriveConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotDrive_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotDrive_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotDrive_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotDrive_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotDrive_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotDrive_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotDrive_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotDrive_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotDrive_<ContainerAllocator> >
{
  static const char* value()
  {
    return "30842a23f107c9440e3bce1d9fbf4d2a";
  }

  static const char* value(const ::db_parsing::DodobotDrive_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x30842a23f107c944ULL;
  static const uint64_t static_value2 = 0x0e3bce1d9fbf4d2aULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotDrive_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotDrive";
  }

  static const char* value(const ::db_parsing::DodobotDrive_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotDrive_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\nfloat32 left_setpoint\nfloat32 right_setpoint\n\nint64 left_enc_pos\nint64 right_enc_pos\nfloat32 left_enc_speed\nfloat32 right_enc_speed\n\nbool left_bumper\nbool right_bumper\n\n\
";
  }

  static const char* value(const ::db_parsing::DodobotDrive_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotDrive_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.left_setpoint);
      stream.next(m.right_setpoint);
      stream.next(m.left_enc_pos);
      stream.next(m.right_enc_pos);
      stream.next(m.left_enc_speed);
      stream.next(m.right_enc_speed);
      stream.next(m.left_bumper);
      stream.next(m.right_bumper);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotDrive_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotDrive_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotDrive_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer<Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "left_setpoint: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.left_setpoint);
    s << indent << "right_setpoint: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.right_setpoint);
    s << indent << "left_enc_pos: ";
    miniros::message_operations::Printer<int64_t>::stream(s, indent + "  ", v.left_enc_pos);
    s << indent << "right_enc_pos: ";
    miniros::message_operations::Printer<int64_t>::stream(s, indent + "  ", v.right_enc_pos);
    s << indent << "left_enc_speed: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.left_enc_speed);
    s << indent << "right_enc_speed: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.right_enc_speed);
    s << indent << "left_bumper: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.left_bumper);
    s << indent << "right_bumper: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.right_bumper);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTDRIVE_HXX
