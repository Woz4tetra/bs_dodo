#ifndef DB_PARSING_DODOBOTPIDSRV_HXX
#define DB_PARSING_DODOBOTPIDSRV_HXX

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
struct DodobotPidSrvRequest_
{
  typedef DodobotPidSrvRequest_<ContainerAllocator> Type;

  DodobotPidSrvRequest_()
    : kp_A(0.0)
    , ki_A(0.0)
    , kd_A(0.0)
    , kp_B(0.0)
    , ki_B(0.0)
    , kd_B(0.0)
    , speed_kA(0.0)
    , speed_kB(0.0)  {
    }
  DodobotPidSrvRequest_(const ContainerAllocator& _alloc)
    : kp_A(0.0)
    , ki_A(0.0)
    , kd_A(0.0)
    , kp_B(0.0)
    , ki_B(0.0)
    , kd_B(0.0)
    , speed_kA(0.0)
    , speed_kB(0.0)  {
  (void)_alloc;
    }

  typedef double _kp_A_type;
  _kp_A_type kp_A;

  typedef double _ki_A_type;
  _ki_A_type ki_A;

  typedef double _kd_A_type;
  _kd_A_type kd_A;

  typedef double _kp_B_type;
  _kp_B_type kp_B;

  typedef double _ki_B_type;
  _ki_B_type ki_B;

  typedef double _kd_B_type;
  _kd_B_type kd_B;

  typedef double _speed_kA_type;
  _speed_kA_type speed_kA;

  typedef double _speed_kB_type;
  _speed_kB_type speed_kB;

  typedef std::shared_ptr< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotPidSrvRequest_

typedef ::db_parsing::DodobotPidSrvRequest_<std::allocator<void> > DodobotPidSrvRequest;

typedef std::shared_ptr< ::db_parsing::DodobotPidSrvRequest > DodobotPidSrvRequestPtr;
typedef std::shared_ptr< ::db_parsing::DodobotPidSrvRequest const> DodobotPidSrvRequestConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "40de8075d1fd92bea3c3772f3db9de88";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x40de8075d1fd92beULL;
  static const uint64_t static_value2 = 0xa3c3772f3db9de88ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotPidSrvRequest";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 kp_A\nfloat64 ki_A\nfloat64 kd_A\nfloat64 kp_B\nfloat64 ki_B\nfloat64 kd_B\nfloat64 speed_kA\nfloat64 speed_kB\n\
";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.kp_A);
      stream.next(m.ki_A);
      stream.next(m.kd_A);
      stream.next(m.kp_B);
      stream.next(m.ki_B);
      stream.next(m.kd_B);
      stream.next(m.speed_kA);
      stream.next(m.speed_kB);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotPidSrvRequest_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotPidSrvRequest_<ContainerAllocator>& v)
  {
    s << indent << "kp_A: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.kp_A);
    s << indent << "ki_A: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.ki_A);
    s << indent << "kd_A: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.kd_A);
    s << indent << "kp_B: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.kp_B);
    s << indent << "ki_B: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.ki_B);
    s << indent << "kd_B: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.kd_B);
    s << indent << "speed_kA: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.speed_kA);
    s << indent << "speed_kB: ";
    miniros::message_operations::Printer<double>::stream(s, indent + "  ", v.speed_kB);
  }
};

} // namespace message_operations
} // namespace miniros


// Response message
template <class ContainerAllocator>
struct DodobotPidSrvResponse_
{
  typedef DodobotPidSrvResponse_<ContainerAllocator> Type;

  DodobotPidSrvResponse_()
    : resp(false)  {
    }
  DodobotPidSrvResponse_(const ContainerAllocator& _alloc)
    : resp(false)  {
  (void)_alloc;
    }

  typedef uint8_t _resp_type;
  _resp_type resp;

  typedef std::shared_ptr< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotPidSrvResponse_

typedef ::db_parsing::DodobotPidSrvResponse_<std::allocator<void> > DodobotPidSrvResponse;

typedef std::shared_ptr< ::db_parsing::DodobotPidSrvResponse > DodobotPidSrvResponsePtr;
typedef std::shared_ptr< ::db_parsing::DodobotPidSrvResponse const> DodobotPidSrvResponseConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe3a98d806e1c4feeULL;
  static const uint64_t static_value2 = 0x01a17d597e27ea8eULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotPidSrvResponse";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool resp\n\
";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.resp);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotPidSrvResponse_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotPidSrvResponse_<ContainerAllocator>& v)
  {
    s << indent << "resp: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.resp);
  }
};

} // namespace message_operations
} // namespace miniros


struct DodobotPidSrv
{
  typedef DodobotPidSrvRequest_<std::allocator<void>> Request;
  typedef DodobotPidSrvResponse_<std::allocator<void>> Response;
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
struct MD5Sum< ::db_parsing::DodobotPidSrv >
{
  static const char* value()
  {
    return "3e8e80dff119519e81b8b4fe3a373977";
  }

  static const char* value(const ::db_parsing::DodobotPidSrv&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotPidSrv >
{
  static const char* value()
  {
    return "db_parsing/DodobotPidSrv";
  }

  static const char* value(const ::db_parsing::DodobotPidSrv&) { return value(); }
};

template<>
struct MD5Sum< ::db_parsing::DodobotPidSrvRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "40de8075d1fd92bea3c3772f3db9de88";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotPidSrvRequest_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_parsing/DodobotPidSrvRequest";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvRequest_<std::allocator<void>>&) { return value(); }
};

template<>
struct MD5Sum< ::db_parsing::DodobotPidSrvResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "e3a98d806e1c4fee01a17d597e27ea8e";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvResponse_<std::allocator<void>>&) { return value(); }
};

template<>
struct DataType< ::db_parsing::DodobotPidSrvResponse_<std::allocator<void>> >
{
  static const char* value()
  {
    return "db_parsing/DodobotPidSrvResponse";
  }

  static const char* value(const ::db_parsing::DodobotPidSrvResponse_<std::allocator<void>>&) { return value(); }
};

} // namespace service_traits
} // namespace miniros

#endif // DB_PARSING_DODOBOTPIDSRV_HXX
