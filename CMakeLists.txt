cmake_minimum_required(VERSION 2.8)
project(Suborbital)

# Output directories.
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Header search path.
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/swig)
include_directories(${PROJECT_SOURCE_DIR}/build)

# Compile flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

# Subdirectories.
add_subdirectory(source)
add_subdirectory(examples)
