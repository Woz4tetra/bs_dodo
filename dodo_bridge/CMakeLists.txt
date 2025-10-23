cmake_minimum_required(VERSION 3.10)
project(image_delay_subscriber)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding miniros to the project
add_subdirectory(thirdparty/miniroscpp)

# Find required packages
find_package(Threads REQUIRED)

# Include directories
include_directories(${MINIROS_INCLUDE_GENERATED_DIRS})

# Create executables
add_executable(dodo_bridge
    src/main.cpp
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

# Compiler flags
target_compile_options(image_delay_subscriber PRIVATE
    -Wall
    -Wextra
    -O2
)

# Install targets
install(TARGETS image_delay_subscriber twist_publisher lidar_visualizer
    RUNTIME DESTINATION bin
)