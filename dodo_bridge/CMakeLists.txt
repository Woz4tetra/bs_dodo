cmake_minimum_required(VERSION 3.14)
project(dodo_bridge)

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

# Fetch CLI11 for command line parsing
FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.1  # Use stable version
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(miniroscpp cli11)

# Find required packages
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
# Note: miniroscpp include directories are handled automatically by FetchContent

# Create executables
add_executable(dodo_bridge
    src/main.cpp
)

# Link libraries
target_link_libraries(dodo_bridge
    miniros::roscxx
    CLI11::CLI11
    ${OpenCV_LIBS}
    Threads::Threads
)

# Compiler flags
target_compile_options(dodo_bridge PRIVATE
    -Wall
    -Wextra
    -O2
)

# Install targets
install(TARGETS dodo_bridge
    RUNTIME DESTINATION bin
)