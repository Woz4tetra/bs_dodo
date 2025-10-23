#ifndef DB_PARSING_PING_HXX
#define DB_PARSING_PING_HXX

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
struct Ping_
{
  typedef Ping_<ContainerAllocator> Type;

  Ping_()
    : header()
    , source()  {
    }
  Ping_(const ContainerAllocator& _alloc)
    : header()
    , source(_alloc)  {
  (void)_alloc;
    }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _source_type;
  _source_type source;

  typedef std::shared_ptr< ::db_parsing::Ping_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::Ping_<ContainerAllocator> const> ConstPtr;

}; // struct Ping_

typedef ::db_parsing::Ping_<std::allocator<void> > Ping;

typedef std::shared_ptr< ::db_parsing::Ping > PingPtr;
typedef std::shared_ptr< ::db_parsing::Ping const> PingConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::Ping_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::Ping_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::Ping_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::Ping_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::Ping_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::Ping_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::Ping_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::Ping_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::Ping_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ca88d565df1a371a47bfcb7ac0bb6e5b";
  }

  static const char* value(const ::db_parsing::Ping_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xca88d565df1a371aULL;
  static const uint64_t static_value2 = 0x47bfcb7ac0bb6e5bULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::Ping_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/Ping";
  }

  static const char* value(const ::db_parsing::Ping_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::Ping_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\nstring source\n\n\
";
  }

  static const char* value(const ::db_parsing::Ping_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::Ping_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.source);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Ping_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::Ping_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::Ping_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "source: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.source);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_PING_HXX
