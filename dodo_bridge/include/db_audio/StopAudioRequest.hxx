#ifndef DB_AUDIO_STOPAUDIOREQUEST_HXX
#define DB_AUDIO_STOPAUDIOREQUEST_HXX

#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>

#include <miniros/types.h>
#include <miniros/serialization.h>
#include <miniros/traits/builtin_message_traits.h>
#include <miniros/message_operations.h>

namespace db_audio
{

template <class ContainerAllocator>
struct StopAudioRequest_
{
  typedef StopAudioRequest_<ContainerAllocator> Type;

  StopAudioRequest_()
    : name()  {
    }
  StopAudioRequest_(const ContainerAllocator& _alloc)
    : name(_alloc)  {
  (void)_alloc;
    }

  typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _name_type;
  _name_type name;

  typedef std::shared_ptr< ::db_audio::StopAudioRequest_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::db_audio::StopAudioRequest_<ContainerAllocator> const> ConstPtr;

}; // struct StopAudioRequest_

typedef ::db_audio::StopAudioRequest_<std::allocator<void> > StopAudioRequest;

typedef std::shared_ptr< ::db_audio::StopAudioRequest > StopAudioRequestPtr;
typedef std::shared_ptr< ::db_audio::StopAudioRequest const> StopAudioRequestConstPtr;

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::db_audio::StopAudioRequest_<ContainerAllocator> & v)
{
miniros::message_operations::Printer< ::db_audio::StopAudioRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace db_audio

namespace miniros
{
namespace message_traits
{

template <class ContainerAllocator>
struct IsMessage< ::db_audio::StopAudioRequest_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::db_audio::StopAudioRequest_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_audio::StopAudioRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::db_audio::StopAudioRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_audio::StopAudioRequest_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::db_audio::StopAudioRequest_<ContainerAllocator> const>
  : std::false_type
  { };

template<class ContainerAllocator>
struct MD5Sum< ::db_audio::StopAudioRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c1f3d28f1b044c871e6eff2e9fc3c667";
  }

  static const char* value(const ::db_audio::StopAudioRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc1f3d28f1b044c87ULL;
  static const uint64_t static_value2 = 0x1e6eff2e9fc3c667ULL;
};

template<class ContainerAllocator>
struct DataType< ::db_audio::StopAudioRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db_audio/StopAudioRequest";
  }

  static const char* value(const ::db_audio::StopAudioRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::db_audio::StopAudioRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string name\n\
";
  }

  static const char* value(const ::db_audio::StopAudioRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace miniros

namespace miniros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::db_audio::StopAudioRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.name);
    }

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct StopAudioRequest_

} // namespace serialization
} // namespace miniros

namespace miniros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::db_audio::StopAudioRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::db_audio::StopAudioRequest_<ContainerAllocator>& v)
  {
    s << indent << "name: ";
    miniros::message_operations::Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.name);
  }
};

} // namespace message_operations
} // namespace miniros

#endif // DB_AUDIO_STOPAUDIOREQUEST_HXX
