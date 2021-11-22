#pragma once

#include "mapper.hpp"
#include "proto/sensor.pb.h"
#include "ros/ros_sensor.hpp"

template <>
Sensor Mapper<RosSensor, Sensor>::toProtobuf(const RosSensor &message) {
  Sensor sensor;
  return sensor;
};
