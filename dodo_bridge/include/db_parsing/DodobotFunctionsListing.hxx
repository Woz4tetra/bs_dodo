#ifndef DB_PARSING_DODOBOTFUNCTIONSLISTING_HXX
#define DB_PARSING_DODOBOTFUNCTIONSLISTING_HXX

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
struct DodobotFunctionsListing_
{
  typedef DodobotFunctionsListing_<ContainerAllocator> Type;

  DodobotFunctionsListing_()
    : menu()
    , selected()  {
    }
  DodobotFunctionsListing_(const ContainerAllocator& _alloc)
    : menu(_alloc)
    , selected(_alloc)  {
  (void)_alloc;
    }

  typedef std::vector<DodobotFunctions_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<DodobotFunctions_<ContainerAllocator> >> _menu_type;
  _menu_type menu;

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _selected_type;
  _selected_type selected;

  typedef std::shared_ptr< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> const> ConstPtr;

}; // struct DodobotFunctionsListing_

typedef ::db_parsing::DodobotFunctionsListing_<std::allocator<void> > DodobotFunctionsListing;

typedef std::shared_ptr< ::db_parsing::DodobotFunctionsListing > DodobotFunctionsListingPtr;
typedef std::shared_ptr< ::db_parsing::DodobotFunctionsListing const> DodobotFunctionsListingConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_parsing

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >
{
  static const char* value()
  {
    return "66f5890bcf6a550bbf8ef1a8fb5a0eb6";
  }

  static const char* value(const ::db_parsing::DodobotFunctionsListing_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x66f5890bcf6a550bULL;
  static const uint64_t static_value2 = 0xbf8ef1a8fb5a0eb6ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_parsing/DodobotFunctionsListing";
  }

  static const char* value(const ::db_parsing::DodobotFunctionsListing_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >
{
  static const char* value()
  {
    return "DodobotFunctions[] menu\nstring selected\n\n\
";
  }

  static const char* value(const ::db_parsing::DodobotFunctionsListing_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.menu);
      stream.next(m.selected);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DodobotFunctionsListing_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_parsing::DodobotFunctionsListing_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_parsing::DodobotFunctionsListing_<ContainerAllocator>& v)
  {
    s << indent << "menu: ";
    miniros::message_operations::Printer<std::vector<DodobotFunctions_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<DodobotFunctions_<ContainerAllocator> >>>::stream(s, indent + "  ", v.menu);
    s << indent << "selected: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.selected);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_PARSING_DODOBOTFUNCTIONSLISTING_HXX
