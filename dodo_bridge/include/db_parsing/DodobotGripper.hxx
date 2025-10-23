#ifndef DB_PARSING_DODOBOTGRIPPER_HXX
#define DB_PARSING_DODOBOTGRIPPER_HXX

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

template <class ContainerAllocator>
struct DodobotGripper_
{
  typedef DodobotGripper_<ContainerAllocator> Type;

  DodobotGripper_()
    : header()
    , position(0)
    , force_threshold(0)  {
    }
  DodobotGripper_(const ContainerAllocator& _alloc)
    : header()
    , position(0)
    , force_threshold(0)  {
  (void)_alloc;
    }

  typedef Header_<ContainerAllocator>  _header_type;
  _header_type header;

  typedef int32_t _position_type;
  _position_type position;

  typedef int32_t _force_threshold_type;
  _force_threshold_type force_threshold;

  typedef std::shared_ptr< ::db_parsing::DodobotGripper_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotGripper_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotGripper_

typedef ::db_parsing::DodobotGripper_<std::allocator<void> > DodobotGripper;

typedef std::shared_ptr< ::db_parsing::DodobotGripper > DodobotGripperPtr;
typedef std::shared_ptr< ::db_parsing::DodobotGripper const> DodobotGripperConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotGripper_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotGripper_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotGripper_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotGripper_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotGripper_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotGripper_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotGripper_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotGripper_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotGripper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "fe05448bef319b5e0216b33676b79e69";
  }

  static const char* value(const ::db_parsing::DodobotGripper_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xfe05448bef319b5eULL;
  static const uint64_t static_value2 = 0x0216b33676b79e69ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotGripper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotGripper";
  }

  static const char* value(const ::db_parsing::DodobotGripper_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotGripper_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\nint32 position\nint32 force_threshold\n\n\
";
  }

  static const char* value(const ::db_parsing::DodobotGripper_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotGripper_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.position);
      stream.next(m.force_threshold);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotGripper_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotGripper_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotGripper_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    miniros::message_operations::Printer<Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "position: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.position);
    s << indent << "force_threshold: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.force_threshold);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTGRIPPER_HXX
