#ifndef DB_PARSING_DODOBOTFSRS_HXX
#define DB_PARSING_DODOBOTFSRS_HXX

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
struct DodobotFSRs_
{
  typedef DodobotFSRs_<ContainerAllocator> Type;

  DodobotFSRs_()
    : header()
    , left(0)
    , right(0)  {
    }
  DodobotFSRs_(const ContainerAllocator& _alloc)
    : header()
    , left(0)
    , right(0)  {
  (void)_alloc;
    }

  typedef Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef uint16_t _left_type;
  _left_type left;

  typedef uint16_t _right_type;
  _right_type right;

  typedef std::shared_ptr< ::db_parsing::DodobotFSRs_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotFSRs_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotFSRs_

typedef ::db_parsing::DodobotFSRs_<std::allocator<void> > DodobotFSRs;

typedef std::shared_ptr< ::db_parsing::DodobotFSRs > DodobotFSRsPtr;
typedef std::shared_ptr< ::db_parsing::DodobotFSRs const> DodobotFSRsConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotFSRs_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotFSRs_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotFSRs_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotFSRs_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotFSRs_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotFSRs_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotFSRs_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotFSRs_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotFSRs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e88e5ab1aa2e0abc43436a5c68f50a25";
  }

  static const char* value(const ::db_parsing::DodobotFSRs_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe88e5ab1aa2e0abcULL;
  static const uint64_t static_value2 = 0x43436a5c68f50a25ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotFSRs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotFSRs";
  }

  static const char* value(const ::db_parsing::DodobotFSRs_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotFSRs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\nuint16 left\nuint16 right\n\n\
";
  }

  static const char* value(const ::db_parsing::DodobotFSRs_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotFSRs_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.left);
      stream.next(m.right);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotFSRs_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotFSRs_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotFSRs_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer<Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "left: ";
    miniros::message_operations::Printer<uint16_t>::stream(s, indent + "  ", v.left);
    s << indent << "right: ";
    miniros::message_operations::Printer<uint16_t>::stream(s, indent + "  ", v.right);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTFSRS_HXX
