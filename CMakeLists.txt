cmake_minimum_required(VERSION 3.10)
project(cpp-raytracer VERSION 0.1.0)

# Use C++17 or later
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include public headers
include_directories(include)

# Automatically find all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cc)

# Build the main executable
add_executable(${PROJECT_NAME} ${SOURCES})
