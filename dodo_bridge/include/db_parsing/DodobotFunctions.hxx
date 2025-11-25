#ifndef DB_PARSING_DODOBOTFUNCTIONS_HXX
#define DB_PARSING_DODOBOTFUNCTIONS_HXX

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
struct DodobotFunctions_
{
  typedef DodobotFunctions_<ContainerAllocator> Type;

  DodobotFunctions_()
    : functions()  {
    }
  DodobotFunctions_(const ContainerAllocator& _alloc)
    : functions(_alloc)  {
  (void)_alloc;
    }

  typedef std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> _functions_type;
  _functions_type functions;

  typedef std::shared_ptr< ::db_parsing::DodobotFunctions_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotFunctions_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotFunctions_

typedef ::db_parsing::DodobotFunctions_<std::allocator<void> > DodobotFunctions;

typedef std::shared_ptr< ::db_parsing::DodobotFunctions > DodobotFunctionsPtr;
typedef std::shared_ptr< ::db_parsing::DodobotFunctions const> DodobotFunctionsConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotFunctions_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotFunctions_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotFunctions_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotFunctions_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotFunctions_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotFunctions_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotFunctions_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotFunctions_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotFunctions_<ContainerAllocator> >
{
  static const char* value()
  {
    return "36a892b92294cc681974413f99c688c3";
  }

  static const char* value(const ::db_parsing::DodobotFunctions_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x36a892b92294cc68ULL;
  static const uint64_t static_value2 = 0x1974413f99c688c3ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotFunctions_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotFunctions";
  }

  static const char* value(const ::db_parsing::DodobotFunctions_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotFunctions_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string[] functions\n\
";
  }

  static const char* value(const ::db_parsing::DodobotFunctions_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotFunctions_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.functions);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotFunctions_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotFunctions_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotFunctions_<ContainerAllocator>& v)
  {
    s << indent << "functions: ";
    miniros::message_operations::Printer<std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>>::stream(s, indent + "  ", v.functions);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTFUNCTIONS_HXX
