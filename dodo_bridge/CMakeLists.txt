cmake_minimum_required(VERSION 3.14)
project(image_delay_subscriber)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch miniroscpp from git
include(FetchContent)
FetchContent_Declare(
    miniroscpp
    GIT_REPOSITORY https://github.com/dkargin/miniroscpp.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(miniroscpp)

# Find required packages
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# Note: miniroscpp include directories are handled automatically by FetchContent

# Create executables
add_executable(image_delay_subscriber
    src/main.cpp
    src/point_cloud_viewer.cpp
)

add_executable(twist_publisher
    src/twist_publisher.cpp
)

add_executable(lidar_visualizer
    src/lidar_visualizer.cpp
)

add_executable(dodobot_notify_publisher
    src/dodobot_notify_publisher.cpp
)

# Link libraries
target_link_libraries(image_delay_subscriber
    miniros::roscxx
    ${OpenCV_LIBS}
    Threads::Threads
)

target_link_libraries(twist_publisher
    miniros::roscxx
    Threads::Threads
)

target_link_libraries(lidar_visualizer
    miniros::roscxx
    ${OpenCV_LIBS}
    Threads::Threads
)

target_link_libraries(dodobot_notify_publisher
    miniros::roscxx
    Threads::Threads
)

# Compiler flags
target_compile_options(image_delay_subscriber PRIVATE
    -Wall
    -Wextra
    -O2
)

# Install targets
install(TARGETS image_delay_subscriber twist_publisher lidar_visualizer dodobot_notify_publisher
    RUNTIME DESTINATION bin
)