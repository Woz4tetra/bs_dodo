cmake_minimum_required(VERSION 3.10)
project(image_delay_subscriber)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding miniros to the project
add_subdirectory(thirdparty/miniroscpp)

# Find required packages
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${MINIROS_INCLUDE_GENERATED_DIRS})

# Create executables
add_executable(image_delay_subscriber
    src/main.cpp
    src/point_cloud_viewer.cpp
)

add_executable(twist_publisher
    src/twist_publisher.cpp
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

# Compiler flags
target_compile_options(image_delay_subscriber PRIVATE
    -Wall
    -Wextra
    -O2
)

# Install targets
install(TARGETS image_delay_subscriber twist_publisher
    RUNTIME DESTINATION bin
)