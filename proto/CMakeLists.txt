# Minimum CMake required
cmake_minimum_required(VERSION 3.16.3)

# Project name
project(proto LANGUAGES CXX)

# Set C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required libraries.
find_package(Protobuf REQUIRED)

# Include directories.
include_directories(${PROTOBUF_INCLUDE_DIR})

protobuf_generate_cpp(PROTO_SRC PROTO_HEADER
    sensor.proto
    speed.proto)

# Create a library.
add_library(${PROJECT_NAME}
    ${PROTO_HEADER}
    ${PROTO_SRC})
