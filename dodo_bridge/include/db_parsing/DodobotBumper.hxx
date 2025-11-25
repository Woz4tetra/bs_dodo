#ifndef DB_PARSING_DODOBOTBUMPER_HXX
#define DB_PARSING_DODOBOTBUMPER_HXX

#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>

#include <miniros/types.h>
#include <miniros/serialization.h>
#include <miniros/traits/builtin_message_traits.h>
#include <miniros/message_operations.h>
#include <std_msgs/Header.hxx>

namespace db_parsing
{

template <class ContainerAllocator>
struct DodobotBumper_
{
  typedef DodobotBumper_<ContainerAllocator> Type;

  DodobotBumper_()
    : header()
    , left(false)
    , right(false)  {
    }
  DodobotBumper_(const ContainerAllocator& _alloc)
    : header()
    , left(false)
    , right(false)  {
  (void)_alloc;
    }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef uint8_t _left_type;
  _left_type left;

  typedef uint8_t _right_type;
  _right_type right;

  typedef std::shared_ptr< ::db_parsing::DodobotBumper_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotBumper_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotBumper_

typedef ::db_parsing::DodobotBumper_<std::allocator<void> > DodobotBumper;

typedef std::shared_ptr< ::db_parsing::DodobotBumper > DodobotBumperPtr;
typedef std::shared_ptr< ::db_parsing::DodobotBumper const> DodobotBumperConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotBumper_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotBumper_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotBumper_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotBumper_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotBumper_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotBumper_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotBumper_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotBumper_<ContainerAllocator> const>
  : std::true_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotBumper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a39bfc831de5c58751c4df286437dc15";
  }

  static const char* value(const ::db_parsing::DodobotBumper_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa39bfc831de5c587ULL;
  static const uint64_t static_value2 = 0x51c4df286437dc15ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotBumper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotBumper";
  }

  static const char* value(const ::db_parsing::DodobotBumper_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotBumper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\nbool left\nbool right\n\
";
  }

  static const char* value(const ::db_parsing::DodobotBumper_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotBumper_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.left);
      stream.next(m.right);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotBumper_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotBumper_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotBumper_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "left: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.left);
    s << indent << "right: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.right);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTBUMPER_HXX
