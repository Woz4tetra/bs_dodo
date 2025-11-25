#ifndef DB_CHASSIS_LINEARVELOCITY_HXX
#define DB_CHASSIS_LINEARVELOCITY_HXX

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
struct LinearVelocity_
{
  typedef LinearVelocity_<ContainerAllocator> Type;

  LinearVelocity_()
    : velocity(0.0)
    , acceleration(0.0)  {
    }
  LinearVelocity_(const ContainerAllocator& _alloc)
    : velocity(0.0)
    , acceleration(0.0)  {
  (void)_alloc;
    }

  typedef float _velocity_type;
  _velocity_type velocity;

  typedef float _acceleration_type;
  _acceleration_type acceleration;

  typedef std::shared_ptr< ::db_chassis::LinearVelocity_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_chassis::LinearVelocity_<ContainerAllocator> const> ConstPtr;

}; // struct LinearVelocity_

typedef ::db_chassis::LinearVelocity_<std::allocator<void> > LinearVelocity;

typedef std::shared_ptr< ::db_chassis::LinearVelocity > LinearVelocityPtr;
typedef std::shared_ptr< ::db_chassis::LinearVelocity const> LinearVelocityConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_chassis::LinearVelocity_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_chassis::LinearVelocity_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_chassis

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_chassis::LinearVelocity_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_chassis::LinearVelocity_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_chassis::LinearVelocity_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_chassis::LinearVelocity_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_chassis::LinearVelocity_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_chassis::LinearVelocity_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_chassis::LinearVelocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "24d3f00ff2de191eaff7b9fec46550e8";
  }

  static const char* value(const ::db_chassis::LinearVelocity_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x24d3f00ff2de191eULL;
  static const uint64_t static_value2 = 0xaff7b9fec46550e8ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_chassis::LinearVelocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_chassis/LinearVelocity";
  }

  static const char* value(const ::db_chassis::LinearVelocity_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_chassis::LinearVelocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 velocity\nfloat32 acceleration\n\
";
  }

  static const char* value(const ::db_chassis::LinearVelocity_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_chassis::LinearVelocity_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.velocity);
      stream.next(m.acceleration);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LinearVelocity_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_chassis::LinearVelocity_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_chassis::LinearVelocity_<ContainerAllocator>& v)
  {
    s << indent << "velocity: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.velocity);
    s << indent << "acceleration: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.acceleration);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_CHASSIS_LINEARVELOCITY_HXX
