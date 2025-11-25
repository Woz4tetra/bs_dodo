#ifndef DB_PARSING_DODOBOTUPLOADFILE_HXX
#define DB_PARSING_DODOBOTUPLOADFILE_HXX

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
struct DodobotUploadFileRequest_
{
  typedef DodobotUploadFileRequest_<ContainerAllocator> Type;

  DodobotUploadFileRequest_()
    : path()
    , dest()  {
    }
  DodobotUploadFileRequest_(const ContainerAllocator& _alloc)
    : path(_alloc)
    , dest(_alloc)  {
  (void)_alloc;
    }

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _path_type;
  _path_type path;

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _dest_type;
  _dest_type dest;

  typedef std::shared_ptr< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotUploadFileRequest_

typedef ::db_parsing::DodobotUploadFileRequest_<std::allocator<void> > DodobotUploadFileRequest;

typedef std::shared_ptr< ::db_parsing::DodobotUploadFileRequest > DodobotUploadFileRequestPtr;
typedef std::shared_ptr< ::db_parsing::DodobotUploadFileRequest const> DodobotUploadFileRequestConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f49aed6002d4df3784e60c025cd75a01";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf49aed6002d4df37ULL;
  static const uint64_t static_value2 = 0x84e60c025cd75a01ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotUploadFileRequest";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string path\nstring dest\n\
";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.path);
      stream.next(m.dest);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotUploadFileRequest_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotUploadFileRequest_<ContainerAllocator>& v)
  {
    s << indent << "path: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.path);
    s << indent << "dest: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.dest);
  }
};

} // namespace message_operations
} // namespace miniros


// Response message
template <class ContainerAllocator>
struct DodobotUploadFileResponse_
{
  typedef DodobotUploadFileResponse_<ContainerAllocator> Type;

  DodobotUploadFileResponse_()
    : resp(false)  {
    }
  DodobotUploadFileResponse_(const ContainerAllocator& _alloc)
    : resp(false)  {
  (void)_alloc;
    }

  typedef uint8_t _resp_type;
  _resp_type resp;

  typedef std::shared_ptr< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotUploadFileResponse_

typedef ::db_parsing::DodobotUploadFileResponse_<std::allocator<void> > DodobotUploadFileResponse;

typedef std::shared_ptr< ::db_parsing::DodobotUploadFileResponse > DodobotUploadFileResponsePtr;
typedef std::shared_ptr< ::db_parsing::DodobotUploadFileResponse const> DodobotUploadFileResponseConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe3a98d806e1c4feeULL;
  static const uint64_t static_value2 = 0x01a17d597e27ea8eULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotUploadFileResponse";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool resp\n\
";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.resp);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotUploadFileResponse_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotUploadFileResponse_<ContainerAllocator>& v)
  {
    s << indent << "resp: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.resp);
  }
};

} // namespace message_operations
} // namespace miniros


struct DodobotUploadFile
{
  typedef DodobotUploadFileRequest_<std::allocator<void>> Request;
  typedef DodobotUploadFileResponse_<std::allocator<void>> Response;
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
struct MD5Sum< ::db_parsing::DodobotUploadFile >
{
  static const char* value()
  {
    return "55eae999a99b9f986a0d94ba0956fe73";
  }

  static const char* value(const ::db_parsing::DodobotUploadFile&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotUploadFile >
{
  static const char* value()
  {
    return "db_parsing/DodobotUploadFile";
  }

  static const char* value(const ::db_parsing::DodobotUploadFile&) { return value(); }
};

template<>
struct MD5Sum< ::db_parsing::DodobotUploadFileRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "f49aed6002d4df3784e60c025cd75a01";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotUploadFileRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_parsing/DodobotUploadFileRequest";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct MD5Sum< ::db_parsing::DodobotUploadFileResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileResponse_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotUploadFileResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_parsing/DodobotUploadFileResponse";
  }

  static const char* value(const ::db_parsing::DodobotUploadFileResponse_<std::allocator<void>>&) { return value(); }
};

} // namespace service_traits
} // namespace miniros

#endif // DB_PARSING_DODOBOTUPLOADFILE_HXX
