#ifndef SENSOR_MSGS_IMAGE_HXX
#define SENSOR_MSGS_IMAGE_HXX

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
struct Image_
{
  typedef Image_<ContainerAllocator> Type;

  Image_()
    : height(0)
    , width(0)
    , encoding()
    , is_bigendian(0)
    , step(0)
    , data()  {
    }
  Image_(const ContainerAllocator& _alloc)
    : height(0)
    , width(0)
    , encoding(_alloc)
    , is_bigendian(0)
    , step(0)
    , data(_alloc)  {
  (void)_alloc;
    }

  typedef uint32_t _height_type;
  _height_type height;

  typedef uint32_t _width_type;
  _width_type width;

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _encoding_type;
  _encoding_type encoding;

  typedef uint8_t _is_bigendian_type;
  _is_bigendian_type is_bigendian;

  typedef uint32_t _step_type;
  _step_type step;

  typedef std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> _data_type;
  _data_type data;

  typedef std::shared_ptr< ::sensor_msgs::Image_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::sensor_msgs::Image_<ContainerAllocator> const> ConstPtr;

}; // struct Image_

typedef ::sensor_msgs::Image_<std::allocator<void> > Image;

typedef std::shared_ptr< ::sensor_msgs::Image > ImagePtr;
typedef std::shared_ptr< ::sensor_msgs::Image const> ImageConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::sensor_msgs::Image_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::sensor_msgs::Image_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace sensor_msgs

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::sensor_msgs::Image_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::sensor_msgs::Image_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sensor_msgs::Image_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sensor_msgs::Image_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::sensor_msgs::Image_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::sensor_msgs::Image_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::sensor_msgs::Image_<ContainerAllocator> >
{
  static const char* value()
  {
    return "5fefc57d1974371778d30c986c68d7f5";
  }

  static const char* value(const ::sensor_msgs::Image_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x5fefc57d19743717ULL;
  static const uint64_t static_value2 = 0x78d30c986c68d7f5ULL;
};

template<class ContainerAllocator>
struct DataType< ::sensor_msgs::Image_<ContainerAllocator> >
{
  static const char* value()
  {
    return "sensor_msgs/Image";
  }

  static const char* value(const ::sensor_msgs::Image_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::sensor_msgs::Image_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# This represents an RGB image\nuint32 height          # image height, that is, number of rows\nuint32 width           # image width, that is, number of columns\n\n# The legal values for encoding are in file src/image_encodings.cpp\n# If you want to standardize a new string format, join\n# ros-users@lists.sourceforge.net and send an email proposing a new encoding.\n\nstring encoding       # Encoding of pixels -- channel meaning, ordering, size\n                      # taken from the list of strings in include/sensor_msgs/image_encodings.h\n\nuint8 is_bigendian    # is this data bigendian?\nuint32 step           # Full row length in bytes\nuint8[] data          # actual matrix data, size is (step * rows)\n\
";
  }

  static const char* value(const ::sensor_msgs::Image_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::sensor_msgs::Image_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.height);
      stream.next(m.width);
      stream.next(m.encoding);
      stream.next(m.is_bigendian);
      stream.next(m.step);
      stream.next(m.data);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Image_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sensor_msgs::Image_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::sensor_msgs::Image_<ContainerAllocator>& v)
  {
    s << indent << "height: ";
    miniros::message_operations::Printer<uint32_t>::stream(s, indent + "  ", v.height);
    s << indent << "width: ";
    miniros::message_operations::Printer<uint32_t>::stream(s, indent + "  ", v.width);
    s << indent << "encoding: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.encoding);
    s << indent << "is_bigendian: ";
    miniros::message_operations::Printer<uint8_t>::stream(s, indent + "  ", v.is_bigendian);
    s << indent << "step: ";
    miniros::message_operations::Printer<uint32_t>::stream(s, indent + "  ", v.step);
    s << indent << "data: ";
    miniros::message_operations::Printer<std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>>::stream(s, indent + "  ", v.data);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // SENSOR_MSGS_IMAGE_HXX
