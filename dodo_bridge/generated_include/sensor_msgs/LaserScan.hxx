#ifndef SENSOR_MSGS_LASERSCAN_HXX
#define SENSOR_MSGS_LASERSCAN_HXX

#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>

#include <miniros/types.h>
#include <miniros/serialization.h>
#include <miniros/traits/builtin_message_traits.h>
#include <miniros/message_operations.h>

namespace sensor_msgs
{

template <class ContainerAllocator>
struct LaserScan_
{
  typedef LaserScan_<ContainerAllocator> Type;

  LaserScan_()
    : angle_min(0.0)
    , angle_max(0.0)
    , angle_increment(0.0)
    , time_increment(0.0)
    , scan_time(0.0)
    , range_min(0.0)
    , range_max(0.0)
    , ranges()
    , intensities()  {
    }
  LaserScan_(const ContainerAllocator& _alloc)
    : angle_min(0.0)
    , angle_max(0.0)
    , angle_increment(0.0)
    , time_increment(0.0)
    , scan_time(0.0)
    , range_min(0.0)
    , range_max(0.0)
    , ranges(_alloc)
    , intensities(_alloc)  {
  (void)_alloc;
    }

  typedef float _angle_min_type;
  _angle_min_type angle_min;

  typedef float _angle_max_type;
  _angle_max_type angle_max;

  typedef float _angle_increment_type;
  _angle_increment_type angle_increment;

  typedef float _time_increment_type;
  _time_increment_type time_increment;

  typedef float _scan_time_type;
  _scan_time_type scan_time;

  typedef float _range_min_type;
  _range_min_type range_min;

  typedef float _range_max_type;
  _range_max_type range_max;

  typedef std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> _ranges_type;
  _ranges_type ranges;

  typedef std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> _intensities_type;
  _intensities_type intensities;

  typedef std::shared_ptr< ::sensor_msgs::LaserScan_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::sensor_msgs::LaserScan_<ContainerAllocator> const> ConstPtr;

}; // struct LaserScan_

typedef ::sensor_msgs::LaserScan_<std::allocator<void> > LaserScan;

typedef std::shared_ptr< ::sensor_msgs::LaserScan > LaserScanPtr;
typedef std::shared_ptr< ::sensor_msgs::LaserScan const> LaserScanConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::sensor_msgs::LaserScan_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::sensor_msgs::LaserScan_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace sensor_msgs

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::sensor_msgs::LaserScan_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::sensor_msgs::LaserScan_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sensor_msgs::LaserScan_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sensor_msgs::LaserScan_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::sensor_msgs::LaserScan_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::sensor_msgs::LaserScan_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::sensor_msgs::LaserScan_<ContainerAllocator> >
{
  static const char* value()
  {
    return "238f2a07623507820876ee6ed3dc598b";
  }

  static const char* value(const ::sensor_msgs::LaserScan_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x238f2a0762350782ULL;
  static const uint64_t static_value2 = 0x0876ee6ed3dc598bULL;
};

template<class ContainerAllocator>
struct DataType< ::sensor_msgs::LaserScan_<ContainerAllocator> >
{
  static const char* value()
  {
    return "sensor_msgs/LaserScan";
  }

  static const char* value(const ::sensor_msgs::LaserScan_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::sensor_msgs::LaserScan_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# This represents a laser scan\n# Each ray has an intensity and distance measurement\n\nfloat32 angle_min         # start angle of the scan [rad]\nfloat32 angle_max         # end angle of the scan [rad]\nfloat32 angle_increment   # angular distance between measurements [rad]\n\nfloat32 time_increment    # time between measurements [seconds] - if your scanner\n                          # is moving, this will be used in interpolating position\n                          # of 3d points\nfloat32 scan_time         # time between scans [seconds]\n\nfloat32 range_min         # minimum range value [m]\nfloat32 range_max         # maximum range value [m]\n\nfloat32[] ranges          # range data [m] (Note: values < range_min or > range_max should be discarded)\nfloat32[] intensities     # intensity data [device-specific units]\n\
";
  }

  static const char* value(const ::sensor_msgs::LaserScan_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::sensor_msgs::LaserScan_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.angle_min);
      stream.next(m.angle_max);
      stream.next(m.angle_increment);
      stream.next(m.time_increment);
      stream.next(m.scan_time);
      stream.next(m.range_min);
      stream.next(m.range_max);
      stream.next(m.ranges);
      stream.next(m.intensities);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LaserScan_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sensor_msgs::LaserScan_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::sensor_msgs::LaserScan_<ContainerAllocator>& v)
  {
    s << indent << "angle_min: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.angle_min);
    s << indent << "angle_max: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.angle_max);
    s << indent << "angle_increment: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.angle_increment);
    s << indent << "time_increment: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.time_increment);
    s << indent << "scan_time: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.scan_time);
    s << indent << "range_min: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.range_min);
    s << indent << "range_max: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.range_max);
    s << indent << "ranges: ";
    miniros::message_operations::Printer<std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>>::stream(s, indent + "  ", v.ranges);
    s << indent << "intensities: ";
    miniros::message_operations::Printer<std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>>::stream(s, indent + "  ", v.intensities);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // SENSOR_MSGS_LASERSCAN_HXX
