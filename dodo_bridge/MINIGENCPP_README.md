# MiniROS C++ Message Generator

This script generates miniroscpp-compatible C++ header files from ROS message (.msg) files.

## Usage

```bash
python3 minigencpp.py <root_directory> <output_include_directory>
```

## Example

Given a directory structure like:
```
my_msgs/
├── geometry_msgs/
│   └── msg/
│       └── Vector3.msg
└── my_package/
    └── msg/
        ├── CustomMessage.msg
        └── AnotherMessage.msg
```

Run:
```bash
python3 minigencpp.py my_msgs include/
```

This will generate:
```
include/
├── geometry_msgs/
│   └── Vector3.hxx
└── my_package/
    ├── CustomMessage.hxx
    └── AnotherMessage.hxx
```

## Message Format Support

The generator supports:
- **Basic types**: `bool`, `byte`, `char`, `int8`, `uint8`, `int16`, `uint16`, `int32`, `uint32`, `int64`, `uint64`, `float32`, `float64`, `string`
- **Time types**: `time`, `duration` 
- **Arrays**: Both fixed-size (`type[N]`) and variable-size (`type[]`)
- **Constants**: `int32 CONSTANT_NAME=42`
- **Custom message types**: `other_package/MessageType`
- **Comments**: Lines starting with `#` and inline comments

## Example Message Files

### Simple Message with Constants
```ros.msg
# my_package/msg/Status.msg
int32 OK=0
int32 WARNING=1  
int32 ERROR=2

string message
int32 status_code
float64 timestamp
```

### Complex Message with Arrays
```ros.msg
# sensor_msgs/msg/LaserScan.msg
float32 angle_min         # start angle [rad]
float32 angle_max         # end angle [rad]
float32 angle_increment   # angular distance [rad]
float32 range_min         # minimum range [m] 
float32 range_max         # maximum range [m]
float32[] ranges          # range measurements [m]
float32[] intensities     # intensity data
```

### Message with Custom Types
```ros.msg
# my_package/msg/RobotState.msg
geometry_msgs/Vector3 position
geometry_msgs/Vector3 velocity
sensor_msgs/LaserScan laser_data
string[] joint_names
float64[] joint_positions
```

## Generated C++ Structure

Each message generates a miniroscpp-compatible header with:

1. **Template struct** with ContainerAllocator support
2. **Constants** as static constexpr members  
3. **Two constructors** (default and allocator-aware)
4. **Field type definitions** and declarations
5. **Smart pointer typedefs** (Ptr, ConstPtr)
6. **Message traits** (MD5Sum, DataType, Definition, etc.)
7. **Serialization support** for miniroscpp
8. **Pretty printing** support

## Features

- **Automatic package detection** from directory structure
- **Proper allocator handling** for containers and strings
- **MD5 hash generation** for message definitions
- **Fixed vs variable-size array detection** for IsFixedSize trait
- **Comment parsing** and removal
- **Error handling** with detailed error messages

## Integration with CMake

Add to your CMakeLists.txt:

```cmake
# Generate message headers
add_custom_target(generate_messages ALL
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/minigencpp.py 
            ${CMAKE_CURRENT_SOURCE_DIR}/msg 
            ${CMAKE_CURRENT_BINARY_DIR}/include
    COMMENT "Generating message headers"
)

# Include generated headers
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

# Make sure your targets depend on message generation
add_dependencies(your_executable generate_messages)
```