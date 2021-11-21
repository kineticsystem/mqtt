# Minimum CMake required
cmake_minimum_required(VERSION 3.16.3)

# Project name
project(mqtt LANGUAGES CXX)

# Set C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add directory containing protobuffer message definitions.
add_subdirectory(proto)

# Find required libraries.
find_package(Protobuf REQUIRED)

# Include directories.
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Executable.
add_executable(${PROJECT_NAME}
    main.cpp)

# Libraries.
target_link_libraries(${PROJECT_NAME}
    proto
    ${PROTOBUF_LIBRARY}
    pthread)
