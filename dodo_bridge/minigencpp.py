#!/usr/bin/env python3

# Mini ROS C++ Message Generator
# Generates miniroscpp-compatible C++ headers from ROS message files
#
# Usage: python3 minigencpp.py <root_directory> <output_include_directory>

import os
import sys
import re
import hashlib
from pathlib import Path

class MessageField:
    """Represents a single field in a ROS message"""
    def __init__(self, field_type, name, is_array=False, array_size=None, is_constant=False, constant_value=None):
        self.field_type = field_type
        self.name = name
        self.is_array = is_array
        self.array_size = array_size  # None for variable-length arrays
        self.is_constant = is_constant
        self.constant_value = constant_value
        self.is_builtin = field_type in BUILTIN_TYPES

class MessageSpec:
    """Represents a parsed ROS message specification"""
    def __init__(self, package, name):
        self.package = package
        self.name = name
        self.fields = []
        self.constants = []
        self.raw_definition = ""

class ServiceSpec:
    """Represents a parsed ROS service specification"""
    def __init__(self, package, name):
        self.package = package
        self.name = name
        self.request = MessageSpec(package, name + "Request")
        self.response = MessageSpec(package, name + "Response")
        self.raw_definition = ""

# Mapping from ROS types to C++ types
BUILTIN_TYPES = {
    'bool': 'uint8_t',
    'byte': 'int8_t',
    'char': 'uint8_t', 
    'uint8': 'uint8_t',
    'int8': 'int8_t',
    'uint16': 'uint16_t',
    'int16': 'int16_t',
    'uint32': 'uint32_t',
    'int32': 'int32_t',
    'uint64': 'uint64_t',
    'int64': 'int64_t',
    'float32': 'float',
    'float64': 'double',
    'string': 'std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>',
    'time': 'miniros::Time',
    'duration': 'miniros::Duration',
}

def parse_type(type_str):
    """Parse a type string like 'uint32[]' or 'geometry_msgs/Vector3[10]' into components"""
    # Check for array notation
    array_match = re.match(r'(.+)\[(\d*)\]$', type_str)
    if array_match:
        base_type = array_match.group(1)
        array_size = array_match.group(2)
        return base_type, True, int(array_size) if array_size else None
    else:
        return type_str, False, None

def msg_type_to_cpp(field_type, is_array=False, array_size=None):
    """Convert ROS message type to C++ type"""
    base_type, _, _ = parse_type(field_type)
    
    if base_type in BUILTIN_TYPES:
        cpp_type = BUILTIN_TYPES[base_type]
    elif '/' in base_type:
        # External message type like geometry_msgs/Vector3
        pkg, msg = base_type.split('/')
        cpp_type = f' ::{pkg}::{msg}_<ContainerAllocator> '
    else:
        # Same package message type
        cpp_type = f'{base_type}_<ContainerAllocator> '
    
    if is_array:
        if array_size is None:
            return f'std::vector<{cpp_type}, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<{cpp_type}>>'
        else:
            return f'std::array<{cpp_type}, {array_size}>'
    else:
        return cpp_type

def default_value(field_type):
    """Return default initialization value for a type"""
    if field_type in ['byte', 'int8', 'int16', 'int32', 'int64', 
                     'char', 'uint8', 'uint16', 'uint32', 'uint64']:
        return '0'
    elif field_type in ['float32', 'float64']:
        return '0.0'
    elif field_type == 'bool':
        return 'false'
    return ''

def takes_allocator(field_type):
    """Return whether type needs allocator in constructor"""
    return field_type == 'string' or field_type not in BUILTIN_TYPES

def parse_msg_content(content, spec):
    """Parse message content and populate a MessageSpec object"""
    for line_num, line in enumerate(content.splitlines(), 1):
        # Remove comments - everything after #
        if '#' in line:
            line = line[:line.index('#')]
        line = line.strip()
        
        # Skip empty lines
        if not line:
            continue
            
        # Check for constants (lines with '=')
        if '=' in line:
            # Parse constant: "int32 CONSTANT_NAME=42"
            parts = line.split('=', 1)  # Split only on first =
            if len(parts) == 2:
                left_part = parts[0].strip()
                constant_value = parts[1].strip()
                
                type_name_parts = left_part.split()
                if len(type_name_parts) == 2:
                    const_type, const_name = type_name_parts
                    field = MessageField(const_type, const_name, is_constant=True, constant_value=constant_value)
                    spec.constants.append(field)
        else:
            # Parse regular field: "geometry_msgs/Vector3 linear"
            parts = line.split()
            if len(parts) >= 2:  # At least type and name
                field_type_str, field_name = parts[0], parts[1]
                field_type, is_array, array_size = parse_type(field_type_str)
                
                field = MessageField(field_type, field_name, is_array, array_size)
                spec.fields.append(field)

def parse_msg_file(file_path):
    """Parse a .msg file and return a MessageSpec object"""
    package = file_path.parts[-3] if len(file_path.parts) >= 3 else "unknown"
    name = file_path.stem
    
    spec = MessageSpec(package, name)
    
    with open(file_path, 'r') as f:
        content = f.read()
        spec.raw_definition = content
    
    parse_msg_content(content, spec)
    
    return spec

def parse_srv_file(file_path):
    """Parse a .srv file and return a ServiceSpec object"""
    # For .srv files: srv/package/ServiceName.srv -> package is parts[-2]
    package = file_path.parts[-2] if len(file_path.parts) >= 2 else "unknown"
    name = file_path.stem
    
    spec = ServiceSpec(package, name)
    
    with open(file_path, 'r') as f:
        content = f.read()
        spec.raw_definition = content
    
    # Split on '---' separator
    parts = content.split('---')
    
    if len(parts) != 2:
        raise ValueError(f"Service file must have exactly one '---' separator, found {len(parts)-1}")
    
    request_content = parts[0].strip()
    response_content = parts[1].strip()
    
    # Parse request and response
    spec.request.raw_definition = request_content
    parse_msg_content(request_content, spec.request)
    
    spec.response.raw_definition = response_content
    parse_msg_content(response_content, spec.response)
    
    return spec

def generate_md5_hash(spec):
    """Generate MD5 hash for the message definition using ROS canonical format"""
    # Create canonical message definition (constants + fields, no spaces around =, no blank lines)
    lines = []
    
    # Add constants first
    for const in spec.constants:
        lines.append(f'{const.field_type} {const.name}={const.constant_value}')
    
    # Add fields  
    for field in spec.fields:
        if field.is_array:
            if field.array_size is None:
                field_def = f'{field.field_type}[] {field.name}'
            else:
                field_def = f'{field.field_type}[{field.array_size}] {field.name}'
        else:
            field_def = f'{field.field_type} {field.name}'
        lines.append(field_def)
    
    canonical_def = '\n'.join(lines)
    return hashlib.md5(canonical_def.encode()).hexdigest()

def generate_header_guard(package, name):
    """Generate header guard macro"""
    return f"{package.upper()}_{name.upper()}_HXX"

def generate_header(spec):
    """Generate complete C++ header file content"""
    package = spec.package
    name = spec.name
    header_guard = generate_header_guard(package, name)
    
    # Generate MD5 hash
    md5_hash = generate_md5_hash(spec)
    
    # Check if message has variable-length fields (affects IsFixedSize)
    has_variable_length = any(
        field.field_type == 'string' or (field.is_array and field.array_size is None)
        for field in spec.fields
    )
    
    header_content = f'''#ifndef {header_guard}
#define {header_guard}

#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>

#include <miniros/types.h>
#include <miniros/serialization.h>
#include <miniros/traits/builtin_message_traits.h>
#include <miniros/message_operations.h>

namespace {package}
{{

template <class ContainerAllocator>
struct {name}_
{{
  typedef {name}_<ContainerAllocator> Type;

'''
    
    # Add constants
    for const_field in spec.constants:
        cpp_type = BUILTIN_TYPES.get(const_field.field_type, const_field.field_type)
        header_content += f'  static constexpr {cpp_type} {const_field.name} = {const_field.constant_value};\n'
    
    if spec.constants:
        header_content += '\n'
    
    # Default constructor
    header_content += f'  {name}_()\n'
    if spec.fields:
        header_content += '    : '
        init_parts = []
        for field in spec.fields:
            if field.is_array:
                init_parts.append(f'{field.name}()')  # Arrays initialized empty
            else:
                default_val = default_value(field.field_type)
                init_parts.append(f'{field.name}({default_val})')
        header_content += '\n    , '.join(init_parts)
        header_content += '  {\n'
    else:
        header_content += '  {\n'
    header_content += '    }\n'
    
    # Allocator constructor  
    header_content += f'  {name}_(const ContainerAllocator& _alloc)\n'
    if spec.fields:
        header_content += '    : '
        init_parts = []
        for field in spec.fields:
            if field.is_array and field.array_size is None:
                # Variable-length arrays need allocator
                init_parts.append(f'{field.name}(_alloc)')
            elif field.field_type == 'string':
                # Strings need allocator
                init_parts.append(f'{field.name}(_alloc)')
            elif field.is_array:
                # Fixed arrays initialized empty
                init_parts.append(f'{field.name}()')
            else:
                # Scalar types with default values
                default_val = default_value(field.field_type)
                init_parts.append(f'{field.name}({default_val})')
        header_content += '\n    , '.join(init_parts)
        header_content += '  {\n'
    else:
        header_content += '  {\n'
    header_content += '  (void)_alloc;\n'
    header_content += '    }\n\n'
    
    # Field type definitions and declarations
    for field in spec.fields:
        cpp_type = msg_type_to_cpp(field.field_type, field.is_array, field.array_size)
        header_content += f'  typedef {cpp_type} _{field.name}_type;\n'
        header_content += f'  _{field.name}_type {field.name};\n\n'
    
    # Pointer typedefs
    header_content += f'''  typedef std::shared_ptr< ::{package}::{name}_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::{package}::{name}_<ContainerAllocator> const> ConstPtr;

}}; // struct {name}_

typedef ::{package}::{name}_<std::allocator<void> > {name};

typedef std::shared_ptr< ::{package}::{name} > {name}Ptr;
typedef std::shared_ptr< ::{package}::{name} const> {name}ConstPtr;

'''
    
    # Constants out-of-line definitions
    if spec.constants:
        header_content += '// constants requiring out of line definition\n'
        for const_field in spec.constants:
            header_content += 'template<typename ContainerAllocator>\n'
            cpp_type = BUILTIN_TYPES.get(const_field.field_type, const_field.field_type)
            header_content += f'constexpr {cpp_type} {name}_<ContainerAllocator>::{const_field.name};\n'
        header_content += '\n'
    
    # Stream operator
    header_content += f'''template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::{package}::{name}_<ContainerAllocator> & v)
{{
miniros::message_operations::Printer< ::{package}::{name}_<ContainerAllocator> >::stream(s, "", v);
return s;
}}

}} // namespace {package}

namespace miniros
{{
namespace message_traits
{{

template <class ContainerAllocator>
struct IsMessage< ::{package}::{name}_<ContainerAllocator> >
  : std::true_type
  {{ }};

template <class ContainerAllocator>
struct IsMessage< ::{package}::{name}_<ContainerAllocator> const>
  : std::true_type
  {{ }};

template <class ContainerAllocator>
struct IsFixedSize< ::{package}::{name}_<ContainerAllocator> >
  : std::{'false' if has_variable_length else 'true'}_type
  {{ }};

template <class ContainerAllocator>
struct IsFixedSize< ::{package}::{name}_<ContainerAllocator> const>
  : std::{'false' if has_variable_length else 'true'}_type
  {{ }};

template <class ContainerAllocator>
struct HasHeader< ::{package}::{name}_<ContainerAllocator> >
  : std::false_type
  {{ }};

template <class ContainerAllocator>
struct HasHeader< ::{package}::{name}_<ContainerAllocator> const>
  : std::false_type
  {{ }};

template<class ContainerAllocator>
struct MD5Sum< ::{package}::{name}_<ContainerAllocator> >
{{
  static const char* value()
  {{
    return "{md5_hash}";
  }}

  static const char* value(const ::{package}::{name}_<ContainerAllocator>&) {{ return value(); }}
  static const uint64_t static_value1 = 0x{md5_hash[:16]}ULL;
  static const uint64_t static_value2 = 0x{md5_hash[16:32]}ULL;
}};

template<class ContainerAllocator>
struct DataType< ::{package}::{name}_<ContainerAllocator> >
{{
  static const char* value()
  {{
    return "{package}/{name}";
  }}

  static const char* value(const ::{package}::{name}_<ContainerAllocator>&) {{ return value(); }}
}};

template<class ContainerAllocator>
struct Definition< ::{package}::{name}_<ContainerAllocator> >
{{
  static const char* value()
  {{
    return "{_escape_string(spec.raw_definition)}\\n\\
";
  }}

  static const char* value(const ::{package}::{name}_<ContainerAllocator>&) {{ return value(); }}
}};

}} // namespace message_traits
}} // namespace miniros

namespace miniros
{{
namespace serialization
{{

  template<class ContainerAllocator> struct Serializer< ::{package}::{name}_<ContainerAllocator> >
  {{
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {{
'''
    
    # Serialization calls
    for field in spec.fields:
        header_content += f'      stream.next(m.{field.name});\n'
    
    header_content += f'''    }}

    MINIROS_DECLARE_ALLINONE_SERIALIZER
  }}; // struct {name}_

}} // namespace serialization
}} // namespace miniros

namespace miniros
{{
namespace message_operations
{{

template<class ContainerAllocator>
struct Printer< ::{package}::{name}_<ContainerAllocator> >
{{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::{package}::{name}_<ContainerAllocator>& v)
  {{
'''
    
    # Printer calls
    for field in spec.fields:
        cpp_type = msg_type_to_cpp(field.field_type, field.is_array, field.array_size)
        header_content += f'    s << indent << "{field.name}: ";\n'
        header_content += f'    miniros::message_operations::Printer<{cpp_type}>::stream(s, indent + "  ", v.{field.name});\n'
    
    header_content += f'''  }}
}};

}} // namespace message_operations
}} // namespace miniros

#endif // {header_guard}
'''
    
    return header_content

def _escape_string(s):
    """Escape string for C++ string literal"""
    s = s.replace('\\', '\\\\')
    s = s.replace('"', '\\"')
    s = s.replace('\n', '\\n')
    return s

def find_msg_files(root_dir):
    """Recursively find all .msg files in directory"""
    root_path = Path(root_dir)
    return list(root_path.rglob('*.msg'))

def find_srv_files(root_dir):
    """Recursively find all .srv files in directory"""
    root_path = Path(root_dir)
    return list(root_path.rglob('*.srv'))

def generate_service_header(spec):
    """Generate complete C++ service header file content"""
    package = spec.package
    name = spec.name
    
    # Calculate MD5 hash for the service (combination of request and response)
    request_md5 = generate_md5_hash(spec.request)
    response_md5 = generate_md5_hash(spec.response)
    
    # Service MD5 is MD5 of concatenated request and response MD5s
    service_md5_text = f"{request_md5}{response_md5}"
    service_md5 = hashlib.md5(service_md5_text.encode()).hexdigest()
    
    header_content = f'''// Generated by gencxx from file {package}/{name}.msg
// DO NOT EDIT!


#pragma once

#include <miniros/traits/service_traits.h>


#include <{package}/{name}Request.hxx>
#include <{package}/{name}Response.hxx>


namespace {package}
{{

struct {name}
{{

typedef {name}Request Request;
typedef {name}Response Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}}; // struct {name}
}} // namespace {package}


namespace miniros
{{
namespace service_traits
{{


template<>
struct MD5Sum< ::{package}::{name} > {{
  static const char* value()
  {{
    return "{service_md5}";
  }}

  static const char* value(const ::{package}::{name}&) {{ return value(); }}
}};

template<>
struct DataType< ::{package}::{name} > {{
  static const char* value()
  {{
    return "{package}/{name}";
  }}

  static const char* value(const ::{package}::{name}&) {{ return value(); }}
}};


// service_traits::MD5Sum< ::{package}::{name}Request> should match 
// service_traits::MD5Sum< ::{package}::{name} > 
template<>
struct MD5Sum< ::{package}::{name}Request>
{{
  static const char* value()
  {{
    return MD5Sum< ::{package}::{name} >::value();
  }}
  static const char* value(const ::{package}::{name}Request&)
  {{
    return value();
  }}
}};

// service_traits::DataType< ::{package}::{name}Request> should match 
// service_traits::DataType< ::{package}::{name} > 
template<>
struct DataType< ::{package}::{name}Request>
{{
  static const char* value()
  {{
    return DataType< ::{package}::{name} >::value();
  }}
  static const char* value(const ::{package}::{name}Request&)
  {{
    return value();
  }}
}};

// service_traits::MD5Sum< ::{package}::{name}Response> should match 
// service_traits::MD5Sum< ::{package}::{name} > 
template<>
struct MD5Sum< ::{package}::{name}Response>
{{
  static const char* value()
  {{
    return MD5Sum< ::{package}::{name} >::value();
  }}
  static const char* value(const ::{package}::{name}Response&)
  {{
    return value();
  }}
}};

// service_traits::DataType< ::{package}::{name}Response> should match 
// service_traits::DataType< ::{package}::{name} > 
template<>
struct DataType< ::{package}::{name}Response>
{{
  static const char* value()
  {{
    return DataType< ::{package}::{name} >::value();
  }}
  static const char* value(const ::{package}::{name}Response&)
  {{
    return value();
  }}
}};

}} // namespace service_traits
}} // namespace miniros
'''
    
    return header_content

def generate_messages(root_dir, output_dir):
    """Generate C++ headers for all messages found in root_dir"""
    msg_files = find_msg_files(root_dir)
    
    if not msg_files:
        print(f"No .msg files found in {root_dir}")
    
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    
    for msg_file in msg_files:
        print(f"Processing: {msg_file}")
        
        try:
            spec = parse_msg_file(msg_file)
            header_content = generate_header(spec)
            
            # Create package directory
            package_dir = output_path / spec.package
            package_dir.mkdir(parents=True, exist_ok=True)
            
            # Write header file
            output_file = package_dir / f"{spec.name}.hxx"
            with open(output_file, 'w') as f:
                f.write(header_content)
                
            print(f"Generated: {output_file}")
            
        except Exception as e:
            print(f"Error processing {msg_file}: {e}")

def generate_services(root_dir, output_dir):
    """Generate C++ headers for all services found in root_dir"""
    srv_files = find_srv_files(root_dir)
    
    if not srv_files:
        print(f"No .srv files found in {root_dir}")
        return
    
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    
    for srv_file in srv_files:
        print(f"Processing: {srv_file}")
        
        try:
            spec = parse_srv_file(srv_file)
            
            # Create package directory
            package_dir = output_path / spec.package
            package_dir.mkdir(parents=True, exist_ok=True)
            
            # Generate Request header
            request_header = generate_header(spec.request)
            request_file = package_dir / f"{spec.name}Request.hxx"
            with open(request_file, 'w') as f:
                f.write(request_header)
            print(f"Generated: {request_file}")
            
            # Generate Response header
            response_header = generate_header(spec.response)
            response_file = package_dir / f"{spec.name}Response.hxx"
            with open(response_file, 'w') as f:
                f.write(response_header)
            print(f"Generated: {response_file}")
            
            # Generate Service header
            service_header = generate_service_header(spec)
            service_file = package_dir / f"{spec.name}.hxx"
            with open(service_file, 'w') as f:
                f.write(service_header)
            print(f"Generated: {service_file}")
            
        except Exception as e:
            print(f"Error processing {srv_file}: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 minigencpp.py <root_directory> <output_include_directory>")
        sys.exit(1)
    
    root_directory = sys.argv[1]
    output_directory = sys.argv[2]
    
    if not os.path.exists(root_directory):
        print(f"Error: Root directory '{root_directory}' does not exist")
        sys.exit(1)
    
    generate_messages(root_directory, output_directory)
    generate_services(root_directory, output_directory)