#ifndef DB_CHASSIS_DODOBOTODOMRESET_HXX
#define DB_CHASSIS_DODOBOTODOMRESET_HXX

#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>

#include <miniros/types.h>
#include <miniros/serialization.h>
#include <miniros/traits/builtin_message_traits.h>
#include <miniros/message_operations.h>

namespace db_chassis
{

// Request message
template <class ContainerAllocator>
struct DodobotOdomResetRequest_
{
  typedef DodobotOdomResetRequest_<ContainerAllocator> Type;

  DodobotOdomResetRequest_()
    : x(0.0)
    , y(0.0)
    , t(0.0)  {
    }
  DodobotOdomResetRequest_(const ContainerAllocator& _alloc)
    : x(0.0)
    , y(0.0)
    , t(0.0)  {
  (void)_alloc;
    }

  typedef double _x_type;
  _x_type x;

  typedef double _y_type;
  _y_type y;

  typedef double _t_type;
  _t_type t;

  typedef std::shared_ptr< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotOdomResetRequest_

typedef ::db_chassis::DodobotOdomResetRequest_<std::allocator<void> > DodobotOdomResetRequest;

typedef std::shared_ptr< ::db_chassis::DodobotOdomResetRequest > DodobotOdomResetRequestPtr;
typedef std::shared_ptr< ::db_chassis::DodobotOdomResetRequest const> DodobotOdomResetRequestConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4a28bd10bf2ad79a2c715f25c5a7ebd3";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4a28bd10bf2ad79aULL;
  static const uint64_t static_value2 = 0x2c715f25c5a7ebd3ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_chassis/DodobotOdomResetRequest";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 x\nfloat64 y\nfloat64 t\n\
";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.t);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotOdomResetRequest_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_chassis::DodobotOdomResetRequest_<ContainerAllocator>& v)
  {
    s << indent << "x: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.y);
    s << indent << "t: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.t);
  }
};

} // namespace message_operations
} // namespace miniros


// Response message
template <class ContainerAllocator>
struct DodobotOdomResetResponse_
{
  typedef DodobotOdomResetResponse_<ContainerAllocator> Type;

  DodobotOdomResetResponse_()
    : resp(false)  {
    }
  DodobotOdomResetResponse_(const ContainerAllocator& _alloc)
    : resp(false)  {
  (void)_alloc;
    }

  typedef uint8_t _resp_type;
  _resp_type resp;

  typedef std::shared_ptr< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotOdomResetResponse_

typedef ::db_chassis::DodobotOdomResetResponse_<std::allocator<void> > DodobotOdomResetResponse;

typedef std::shared_ptr< ::db_chassis::DodobotOdomResetResponse > DodobotOdomResetResponsePtr;
typedef std::shared_ptr< ::db_chassis::DodobotOdomResetResponse const> DodobotOdomResetResponseConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe3a98d806e1c4feeULL;
  static const uint64_t static_value2 = 0x01a17d597e27ea8eULL;
};

template<class ContainerAllocator>
struct DataType< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_chassis/DodobotOdomResetResponse";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool resp\n\
";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.resp);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotOdomResetResponse_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_chassis::DodobotOdomResetResponse_<ContainerAllocator>& v)
  {
    s << indent << "resp: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.resp);
  }
};

} // namespace message_operations
} // namespace miniros


struct DodobotOdomReset
{
  typedef DodobotOdomResetRequest_<std::allocator<void>> Request;
  typedef DodobotOdomResetResponse_<std::allocator<void>> Response;
  Request request;
  Response response;

  typedef Request RequestType;
  typedef Response ResponseType;
};

} // namespace db_chassis

namespace miniros
{
namespace service_traits
{

template<>
struct MD5Sum< ::db_chassis::DodobotOdomReset >
{
  static const char* value()
  {
    return "609a076e2d1f8c411ad990f9ed753f7d";
  }

  static const char* value(const ::db_chassis::DodobotOdomReset&) { return value(); }
};

template<>
struct DataType< ::db_chassis::DodobotOdomReset >
{
  static const char* value()
  {
    return "db_chassis/DodobotOdomReset";
  }

  static const char* value(const ::db_chassis::DodobotOdomReset&) { return value(); }
};

template<>
struct MD5Sum< ::db_chassis::DodobotOdomResetRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "4a28bd10bf2ad79a2c715f25c5a7ebd3";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_chassis::DodobotOdomResetRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_chassis/DodobotOdomResetRequest";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct MD5Sum< ::db_chassis::DodobotOdomResetResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetResponse_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_chassis::DodobotOdomResetResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_chassis/DodobotOdomResetResponse";
  }

  static const char* value(const ::db_chassis::DodobotOdomResetResponse_<std::allocator<void>>&) { return value(); }
};

} // namespace service_traits
} // namespace miniros

#endif // DB_CHASSIS_DODOBOTODOMRESET_HXX
