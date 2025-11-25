#ifndef DB_PARSING_DODOBOTLINEAREVENT_HXX
#define DB_PARSING_DODOBOTLINEAREVENT_HXX

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
struct DodobotLinearEvent_
{
  typedef DodobotLinearEvent_<ContainerAllocator> Type;

  DodobotLinearEvent_()
    : stamp()
    , event_num(0)  {
    }
  DodobotLinearEvent_(const ContainerAllocator& _alloc)
    : stamp()
    , event_num(0)  {
  (void)_alloc;
    }

  typedef miniros::Time _stamp_type;
  _stamp_type stamp;

  typedef int32_t _event_num_type;
  _event_num_type event_num;

  typedef std::shared_ptr< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotLinearEvent_

typedef ::db_parsing::DodobotLinearEvent_<std::allocator<void> > DodobotLinearEvent;

typedef std::shared_ptr< ::db_parsing::DodobotLinearEvent > DodobotLinearEventPtr;
typedef std::shared_ptr< ::db_parsing::DodobotLinearEvent const> DodobotLinearEventConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotLinearEvent_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8f57088490e47cab943dafdcbbca8386";
  }

  static const char* value(const ::db_parsing::DodobotLinearEvent_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8f57088490e47cabULL;
  static const uint64_t static_value2 = 0x943dafdcbbca8386ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotLinearEvent";
  }

  static const char* value(const ::db_parsing::DodobotLinearEvent_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >
{
  static const char* value()
  {
    return "time stamp\nint32 event_num\n\
";
  }

  static const char* value(const ::db_parsing::DodobotLinearEvent_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.stamp);
      stream.next(m.event_num);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotLinearEvent_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotLinearEvent_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotLinearEvent_<ContainerAllocator>& v)
  {
    s << indent << "stamp: ";
    miniros::message_operations::Printer<miniros::Time>::stream(s, indent + "  ", v.stamp);
    s << indent << "event_num: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.event_num);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTLINEAREVENT_HXX
