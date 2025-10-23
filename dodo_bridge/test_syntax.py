#!/usr/bin/env python3

# Test syntax validation of generated headers
import subprocess
import tempfile
import os

def test_header_syntax(header_file):
    """Test that a header file has valid C++ syntax"""
    
    # Create a minimal test file
    test_content = '''
#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>
#include <iostream>

// Mock types to avoid miniroscpp dependencies
namespace miniros {
    struct Time { int sec, nsec; };
    struct Duration { int sec, nsec; };
    namespace message_traits {}
    namespace serialization {}
    namespace message_operations {
        template<typename T>
        struct Printer {
            template<typename Stream> 
            static void stream(Stream& s, const std::string& indent, const T& v) {}
        };
    }
    namespace traits {}
}

#define MINIROS_DECLARE_ALLINONE_SERIALIZER

int main() { return 0; }
'''
    
    # Read and modify the header to remove problematic includes
    with open(header_file, 'r') as f:
        header_content = f.read()
    
    # Remove miniros includes
    lines = header_content.split('\n')
    filtered_lines = []
    for line in lines:
        if '#include <miniros/' not in line:
            filtered_lines.append(line)
        else:
            filtered_lines.append('// ' + line)  # Comment out
    
    # Insert the test content at the top, after header guard
    result_lines = []
    for i, line in enumerate(filtered_lines):
        result_lines.append(line)
        if line.startswith('#define') and line.endswith('_HXX'):
            # Insert our mock definitions after the header guard
            result_lines.append(test_content)
    
    # Write to temporary file
    with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False) as f:
        f.write('\n'.join(result_lines))
        temp_file = f.name
    
    try:
        # Try to compile
        result = subprocess.run(['g++', '-std=c++17', '-fsyntax-only', temp_file], 
                              capture_output=True, text=True)
        return result.returncode == 0, result.stderr
    finally:
        os.unlink(temp_file)

# Test our generated headers
headers = [
    'generated_include/db_parsing/DodobotNotify.hxx',
    'generated_include/sensor_msgs/LaserScan.hxx',
    'generated_include/sensor_msgs/Image.hxx'
]

for header in headers:
    success, error = test_header_syntax(header)
    print(f'{header}: {"✓ PASS" if success else "✗ FAIL"}')
    if not success:
        print(f'  Error: {error}')