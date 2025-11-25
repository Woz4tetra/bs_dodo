#ifndef DB_PARSING_DODOBOTSETSTATE_HXX
#define DB_PARSING_DODOBOTSETSTATE_HXX

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
struct DodobotSetStateRequest_
{
  typedef DodobotSetStateRequest_<ContainerAllocator> Type;

  DodobotSetStateRequest_()
    : reporting(false)
    , active(false)  {
    }
  DodobotSetStateRequest_(const ContainerAllocator& _alloc)
    : reporting(false)
    , active(false)  {
  (void)_alloc;
    }

  typedef uint8_t _reporting_type;
  _reporting_type reporting;

  typedef uint8_t _active_type;
  _active_type active;

  typedef std::shared_ptr< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotSetStateRequest_

typedef ::db_parsing::DodobotSetStateRequest_<std::allocator<void> > DodobotSetStateRequest;

typedef std::shared_ptr< ::db_parsing::DodobotSetStateRequest > DodobotSetStateRequestPtr;
typedef std::shared_ptr< ::db_parsing::DodobotSetStateRequest const> DodobotSetStateRequestConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c99305f73325c95014e0e3b135b416c3";
  }

  static const char* value(const ::db_parsing::DodobotSetStateRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc99305f73325c950ULL;
  static const uint64_t static_value2 = 0x14e0e3b135b416c3ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotSetStateRequest";
  }

  static const char* value(const ::db_parsing::DodobotSetStateRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool reporting\nbool active\n\
";
  }

  static const char* value(const ::db_parsing::DodobotSetStateRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.reporting);
      stream.next(m.active);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotSetStateRequest_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotSetStateRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotSetStateRequest_<ContainerAllocator>& v)
  {
    s << indent << "reporting: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.reporting);
    s << indent << "active: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.active);
  }
};

} // namespace message_operations
} // namespace miniros


// Response message
template <class ContainerAllocator>
struct DodobotSetStateResponse_
{
  typedef DodobotSetStateResponse_<ContainerAllocator> Type;

  DodobotSetStateResponse_()
    : resp(false)  {
    }
  DodobotSetStateResponse_(const ContainerAllocator& _alloc)
    : resp(false)  {
  (void)_alloc;
    }

  typedef uint8_t _resp_type;
  _resp_type resp;

  typedef std::shared_ptr< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotSetStateResponse_

typedef ::db_parsing::DodobotSetStateResponse_<std::allocator<void> > DodobotSetStateResponse;

typedef std::shared_ptr< ::db_parsing::DodobotSetStateResponse > DodobotSetStateResponsePtr;
typedef std::shared_ptr< ::db_parsing::DodobotSetStateResponse const> DodobotSetStateResponseConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_parsing::DodobotSetStateResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe3a98d806e1c4feeULL;
  static const uint64_t static_value2 = 0x01a17d597e27ea8eULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotSetStateResponse";
  }

  static const char* value(const ::db_parsing::DodobotSetStateResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool resp\n\
";
  }

  static const char* value(const ::db_parsing::DodobotSetStateResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.resp);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotSetStateResponse_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotSetStateResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotSetStateResponse_<ContainerAllocator>& v)
  {
    s << indent << "resp: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.resp);
  }
};

} // namespace message_operations
} // namespace miniros


struct DodobotSetState
{
  typedef DodobotSetStateRequest_<std::allocator<void>> Request;
  typedef DodobotSetStateResponse_<std::allocator<void>> Response;
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
struct MD5Sum< ::db_parsing::DodobotSetState >
{
  static const char* value()
  {
    return "65fa6a04681913150cdf63fa1ed7713c";
  }

  static const char* value(const ::db_parsing::DodobotSetState&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotSetState >
{
  static const char* value()
  {
    return "db_parsing/DodobotSetState";
  }

  static const char* value(const ::db_parsing::DodobotSetState&) { return value(); }
};

template<>
struct MD5Sum< ::db_parsing::DodobotSetStateRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "c99305f73325c95014e0e3b135b416c3";
  }

  static const char* value(const ::db_parsing::DodobotSetStateRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotSetStateRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_parsing/DodobotSetStateRequest";
  }

  static const char* value(const ::db_parsing::DodobotSetStateRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct MD5Sum< ::db_parsing::DodobotSetStateResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_parsing::DodobotSetStateResponse_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotSetStateResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_parsing/DodobotSetStateResponse";
  }

  static const char* value(const ::db_parsing::DodobotSetStateResponse_<std::allocator<void>>&) { return value(); }
};

} // namespace service_traits
} // namespace miniros

#endif // DB_PARSING_DODOBOTSETSTATE_HXX
