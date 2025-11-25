#ifndef DB_PARSING_DODOBOTPARALLELGRIPPER_HXX
#define DB_PARSING_DODOBOTPARALLELGRIPPER_HXX

#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>

#include <miniros/types.h>
#include <miniros/serialization.h>
#include <miniros/traits/builtin_message_traits.h>
#include <miniros/message_operations.h>
#include <std_msgs/Header.hxx>

namespace db_parsing
{

template <class ContainerAllocator>
struct DodobotParallelGripper_
{
  typedef DodobotParallelGripper_<ContainerAllocator> Type;

  DodobotParallelGripper_()
    : header()
    , distance(0.0)
    , force_threshold(0.0)  {
    }
  DodobotParallelGripper_(const ContainerAllocator& _alloc)
    : header()
    , distance(0.0)
    , force_threshold(0.0)  {
  (void)_alloc;
    }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef float _distance_type;
  _distance_type distance;

  typedef float _force_threshold_type;
  _force_threshold_type force_threshold;

  typedef std::shared_ptr< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotParallelGripper_

typedef ::db_parsing::DodobotParallelGripper_<std::allocator<void> > DodobotParallelGripper;

typedef std::shared_ptr< ::db_parsing::DodobotParallelGripper > DodobotParallelGripperPtr;
typedef std::shared_ptr< ::db_parsing::DodobotParallelGripper const> DodobotParallelGripperConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotParallelGripper_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> const>
  : std::true_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "31e6d713e74b2cf088e9dc8950c2e10f";
  }

  static const char* value(const ::db_parsing::DodobotParallelGripper_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x31e6d713e74b2cf0ULL;
  static const uint64_t static_value2 = 0x88e9dc8950c2e10fULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotParallelGripper";
  }

  static const char* value(const ::db_parsing::DodobotParallelGripper_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\nfloat32 distance\nfloat32 force_threshold\n\
";
  }

  static const char* value(const ::db_parsing::DodobotParallelGripper_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.distance);
      stream.next(m.force_threshold);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotParallelGripper_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotParallelGripper_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotParallelGripper_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "distance: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.distance);
    s << indent << "force_threshold: ";
    miniros::message_operations::Printer<float>::stream(s, indent + "  ", v.force_threshold);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTPARALLELGRIPPER_HXX
