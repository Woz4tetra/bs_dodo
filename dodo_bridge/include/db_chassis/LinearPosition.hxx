#ifndef DB_CHASSIS_LINEARPOSITION_HXX
#define DB_CHASSIS_LINEARPOSITION_HXX

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
struct LinearPosition_
{
  typedef LinearPosition_<ContainerAllocator> Type;

  LinearPosition_()
    : position(0.0)
    , max_speed(0.0)
    , acceleration(0.0)  {
    }
  LinearPosition_(const ContainerAllocator& _alloc)
    : position(0.0)
    , max_speed(0.0)
    , acceleration(0.0)  {
  (void)_alloc;
    }

  typedef float _position_type;
  _position_type position;

  typedef float _max_speed_type;
  _max_speed_type max_speed;

  typedef float _acceleration_type;
  _acceleration_type acceleration;

  typedef std::shared_ptr< ::db_chassis::LinearPosition_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_chassis::LinearPosition_<ContainerAllocator> const> ConstPtr;

}; // struct LinearPosition_

typedef ::db_chassis::LinearPosition_<std::allocator<void> > LinearPosition;

typedef std::shared_ptr< ::db_chassis::LinearPosition > LinearPositionPtr;
typedef std::shared_ptr< ::db_chassis::LinearPosition const> LinearPositionConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_chassis::LinearPosition_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_chassis::LinearPosition_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_chassis

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_chassis::LinearPosition_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_chassis::LinearPosition_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_chassis::LinearPosition_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_chassis::LinearPosition_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_chassis::LinearPosition_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_chassis::LinearPosition_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_chassis::LinearPosition_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e8ff8ee74f72ddd530b00f2c2eb4651c";
  }

  static const char* value(const ::db_chassis::LinearPosition_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe8ff8ee74f72ddd5ULL;
  static const uint64_t static_value2 = 0x30b00f2c2eb4651cULL;
};

template<class ContainerAllocator>
struct DataType< ::db_chassis::LinearPosition_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_chassis/LinearPosition";
  }

  static const char* value(const ::db_chassis::LinearPosition_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_chassis::LinearPosition_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 position\nfloat32 max_speed\nfloat32 acceleration\n\n\
";
  }

  static const char* value(const ::db_chassis::LinearPosition_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_chassis::LinearPosition_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.position);
      stream.next(m.max_speed);
      stream.next(m.acceleration);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LinearPosition_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_chassis::LinearPosition_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_chassis::LinearPosition_<ContainerAllocator>& v)
  {
    s << indent << "position: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.position);
    s << indent << "max_speed: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.max_speed);
    s << indent << "acceleration: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.acceleration);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_CHASSIS_LINEARPOSITION_HXX
