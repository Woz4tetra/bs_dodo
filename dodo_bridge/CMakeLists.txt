cmake_minimum_required(VERSION 3.10)
project(image_delay_subscriber)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)

# Find websocketpp (header-only library)
find_path(WEBSOCKETPP_INCLUDE_DIR websocketpp/config/asio_no_tls.hpp)
if(NOT WEBSOCKETPP_INCLUDE_DIR)
    message(FATAL_ERROR "WebSocket++ not found. Please install websocketpp-dev")
endif()

# Find jsoncpp
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Include directories
include_directories(${WEBSOCKETPP_INCLUDE_DIR})
include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

# Create executable
add_executable(image_delay_subscriber
    src/main.cpp
    src/ros_client.cpp
    src/topic_subscriber.cpp
    src/point_cloud_viewer.cpp
)

# Link libraries
target_link_libraries(image_delay_subscriber
    ${JSONCPP_LIBRARIES}
    ${OpenCV_LIBS}
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)

# Compiler flags
target_compile_options(image_delay_subscriber PRIVATE
    ${JSONCPP_CFLAGS_OTHER}
    -Wall
    -Wextra
    -O2
)

# Install target
install(TARGETS image_delay_subscriber
    RUNTIME DESTINATION bin
)