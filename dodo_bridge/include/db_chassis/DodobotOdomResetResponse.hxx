#ifndef DB_CHASSIS_DODOBOTODOMRESETRESPONSE_HXX
#define DB_CHASSIS_DODOBOTODOMRESETRESPONSE_HXX

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

} // namespace db_chassis

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

#endif // DB_CHASSIS_DODOBOTODOMRESETRESPONSE_HXX
