#ifndef DB_PARSING_DODOBOTLISTDIRREQUEST_HXX
#define DB_PARSING_DODOBOTLISTDIRREQUEST_HXX

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
struct DodobotListDirRequest_
{
  typedef DodobotListDirRequest_<ContainerAllocator> Type;

  DodobotListDirRequest_()
    : dirname()  {
    }
  DodobotListDirRequest_(const ContainerAllocator& _alloc)
    : dirname(_alloc)  {
  (void)_alloc;
    }

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _dirname_type;
  _dirname_type dirname;

  typedef std::shared_ptr< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotListDirRequest_

typedef ::db_parsing::DodobotListDirRequest_<std::allocator<void> > DodobotListDirRequest;

typedef std::shared_ptr< ::db_parsing::DodobotListDirRequest > DodobotListDirRequestPtr;
typedef std::shared_ptr< ::db_parsing::DodobotListDirRequest const> DodobotListDirRequestConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotListDirRequest_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1b12230345832fcff174cc4e204a12f5";
  }

  static const char* value(const ::db_parsing::DodobotListDirRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1b12230345832fcfULL;
  static const uint64_t static_value2 = 0xf174cc4e204a12f5ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotListDirRequest";
  }

  static const char* value(const ::db_parsing::DodobotListDirRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string dirname\n\
";
  }

  static const char* value(const ::db_parsing::DodobotListDirRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.dirname);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotListDirRequest_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotListDirRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotListDirRequest_<ContainerAllocator>& v)
  {
    s << indent << "dirname: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.dirname);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTLISTDIRREQUEST_HXX
