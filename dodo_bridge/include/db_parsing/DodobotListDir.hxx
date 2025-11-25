#ifndef DB_PARSING_DODOBOTLISTDIR_HXX
#define DB_PARSING_DODOBOTLISTDIR_HXX

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

// Request message
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


// Response message
template <class ContainerAllocator>
struct DodobotListDirResponse_
{
  typedef DodobotListDirResponse_<ContainerAllocator> Type;

  DodobotListDirResponse_()
    : resp(false)  {
    }
  DodobotListDirResponse_(const ContainerAllocator& _alloc)
    : resp(false)  {
  (void)_alloc;
    }

  typedef uint8_t _resp_type;
  _resp_type resp;

  typedef std::shared_ptr< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotListDirResponse_

typedef ::db_parsing::DodobotListDirResponse_<std::allocator<void> > DodobotListDirResponse;

typedef std::shared_ptr< ::db_parsing::DodobotListDirResponse > DodobotListDirResponsePtr;
typedef std::shared_ptr< ::db_parsing::DodobotListDirResponse const> DodobotListDirResponseConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotListDirResponse_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_parsing::DodobotListDirResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe3a98d806e1c4feeULL;
  static const uint64_t static_value2 = 0x01a17d597e27ea8eULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotListDirResponse";
  }

  static const char* value(const ::db_parsing::DodobotListDirResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool resp\n\
";
  }

  static const char* value(const ::db_parsing::DodobotListDirResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.resp);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotListDirResponse_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotListDirResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotListDirResponse_<ContainerAllocator>& v)
  {
    s << indent << "resp: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.resp);
  }
};

} // namespace message_operations
} // namespace miniros


struct DodobotListDir
{
  typedef DodobotListDirRequest_<std::allocator<void>> Request;
  typedef DodobotListDirResponse_<std::allocator<void>> Response;
  Request request;
  Response response;

  typedef Request RequestType;
  typedef Response ResponseType;
};

} // namespace db_parsing

namespace miniros
{
namespace service_traits
{

template<>
struct MD5Sum< ::db_parsing::DodobotListDir >
{
  static const char* value()
  {
    return "5a5b4801fd61fb145ec709d282847152";
  }

  static const char* value(const ::db_parsing::DodobotListDir&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotListDir >
{
  static const char* value()
  {
    return "db_parsing/DodobotListDir";
  }

  static const char* value(const ::db_parsing::DodobotListDir&) { return value(); }
};

template<>
struct MD5Sum< ::db_parsing::DodobotListDirRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "1b12230345832fcff174cc4e204a12f5";
  }

  static const char* value(const ::db_parsing::DodobotListDirRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotListDirRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_parsing/DodobotListDirRequest";
  }

  static const char* value(const ::db_parsing::DodobotListDirRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct MD5Sum< ::db_parsing::DodobotListDirResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_parsing::DodobotListDirResponse_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotListDirResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_parsing/DodobotListDirResponse";
  }

  static const char* value(const ::db_parsing::DodobotListDirResponse_<std::allocator<void>>&) { return value(); }
};

} // namespace service_traits
} // namespace miniros

#endif // DB_PARSING_DODOBOTLISTDIR_HXX
