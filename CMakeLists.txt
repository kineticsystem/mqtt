# Minimum CMake required
cmake_minimum_required(VERSION 3.16.3)

# Project name
project(mqtt LANGUAGES CXX)

# Set C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (THREADS_PREFER_PTHREAD_FLAG ON)

# Add directory containing protobuffer message definitions.
add_subdirectory(proto)

# Libraries.
find_package(Protobuf REQUIRED)    # Protobuf library.
find_package(PahoMqttCpp REQUIRED) # Paho MQTT client library
find_package(Threads REQUIRED)     # PThread library required by both Protobuf and Paho.

# Include directories.
include_directories(${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

# Executable.
add_executable(${PROJECT_NAME}
    asynch_client.hpp
    default_asynch_client.hpp
    ros/ros_sensor.hpp
    ros/ros_speed.hpp
    mapper/mapper.hpp
    mapper/sensor_mapper.hpp
    mapper/speed_mapper.hpp
    main.cpp
    ros/ros_sensor.cpp
    ros/ros_speed.cpp
)

# Libraries.
target_link_libraries(${PROJECT_NAME}
    proto
    ${PROTOBUF_LIBRARY}
    paho-mqttpp3
    paho-mqtt3as
    pthread)
