#ifndef DB_CHASSIS_DODOBOTODOMRESETREQUEST_HXX
#define DB_CHASSIS_DODOBOTODOMRESETREQUEST_HXX

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

} // namespace db_chassis

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

#endif // DB_CHASSIS_DODOBOTODOMRESETREQUEST_HXX
