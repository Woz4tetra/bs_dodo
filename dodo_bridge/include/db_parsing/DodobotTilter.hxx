#ifndef DB_PARSING_DODOBOTTILTER_HXX
#define DB_PARSING_DODOBOTTILTER_HXX

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
struct DodobotTilter_
{
  typedef DodobotTilter_<ContainerAllocator> Type;

  DodobotTilter_()
    : header()
    , position(0)
    , command(0)  {
    }
  DodobotTilter_(const ContainerAllocator& _alloc)
    : header()
    , position(0)
    , command(0)  {
  (void)_alloc;
    }

  typedef Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef int32_t _position_type;
  _position_type position;

  typedef uint8_t _command_type;
  _command_type command;

  typedef std::shared_ptr< ::db_parsing::DodobotTilter_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotTilter_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotTilter_

typedef ::db_parsing::DodobotTilter_<std::allocator<void> > DodobotTilter;

typedef std::shared_ptr< ::db_parsing::DodobotTilter > DodobotTilterPtr;
typedef std::shared_ptr< ::db_parsing::DodobotTilter const> DodobotTilterConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotTilter_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotTilter_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotTilter_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotTilter_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotTilter_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotTilter_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotTilter_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotTilter_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotTilter_<ContainerAllocator> >
{
  static const char* value()
  {
    return "7a8b28241bce7f20da0a6f06eb979a95";
  }

  static const char* value(const ::db_parsing::DodobotTilter_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x7a8b28241bce7f20ULL;
  static const uint64_t static_value2 = 0xda0a6f06eb979a95ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotTilter_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotTilter";
  }

  static const char* value(const ::db_parsing::DodobotTilter_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotTilter_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\nint32 position\nuint8 command\n\n\
";
  }

  static const char* value(const ::db_parsing::DodobotTilter_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotTilter_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.position);
      stream.next(m.command);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotTilter_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotTilter_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotTilter_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer<Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "position: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.position);
    s << indent << "command: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.command);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTTILTER_HXX
