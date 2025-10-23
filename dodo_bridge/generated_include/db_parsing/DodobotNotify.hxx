#ifndef DB_PARSING_DODOBOTNOTIFY_HXX
#define DB_PARSING_DODOBOTNOTIFY_HXX

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
struct DodobotNotify_
{
  typedef DodobotNotify_<ContainerAllocator> Type;

  static constexpr int32_t INFO = 0;
  static constexpr int32_t WARN = 1;
  static constexpr int32_t ERROR = 2;

  DodobotNotify_()
    : message()
    , level(0)
    , timeout(0)  {
    }
  DodobotNotify_(const ContainerAllocator& _alloc)
    : message(_alloc)
    , level(0)
    , timeout(0)  {
  (void)_alloc;
    }

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _message_type;
  _message_type message;

  typedef int32_t _level_type;
  _level_type level;

  typedef uint32_t _timeout_type;
  _timeout_type timeout;

  typedef std::shared_ptr< ::db_parsing::DodobotNotify_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotNotify_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotNotify_

typedef ::db_parsing::DodobotNotify_<std::allocator<void> > DodobotNotify;

typedef std::shared_ptr< ::db_parsing::DodobotNotify > DodobotNotifyPtr;
typedef std::shared_ptr< ::db_parsing::DodobotNotify const> DodobotNotifyConstPtr;

// constants requiring out of line definition
template<typename ContainerAllocator>
constexpr int32_t DodobotNotify_<ContainerAllocator>::INFO;
template<typename ContainerAllocator>
constexpr int32_t DodobotNotify_<ContainerAllocator>::WARN;
template<typename ContainerAllocator>
constexpr int32_t DodobotNotify_<ContainerAllocator>::ERROR;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotNotify_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotNotify_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotNotify_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotNotify_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotNotify_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotNotify_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotNotify_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotNotify_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotNotify_<ContainerAllocator> >
{
  static const char* value()
  {
    return "82e25da28600e4be0bbd9da78608534d";
  }

  static const char* value(const ::db_parsing::DodobotNotify_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x82e25da28600e4beULL;
  static const uint64_t static_value2 = 0x0bbd9da78608534dULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotNotify_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotNotify";
  }

  static const char* value(const ::db_parsing::DodobotNotify_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotNotify_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 INFO=0\nint32 WARN=1\nint32 ERROR=2\n\nstring message\nint32 level\nuint32 timeout\n\
";
  }

  static const char* value(const ::db_parsing::DodobotNotify_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotNotify_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.message);
      stream.next(m.level);
      stream.next(m.timeout);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotNotify_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotNotify_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotNotify_<ContainerAllocator>& v)
  {
    s << indent << "message: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.message);
    s << indent << "level: ";
    miniros::message_operations::Printer<int32_t>::stream(s, indent + "  ", v.level);
    s << indent << "timeout: ";
    miniros::message_operations::Printer<uint32_t>::stream(s, indent + "  ", v.timeout);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTNOTIFY_HXX
