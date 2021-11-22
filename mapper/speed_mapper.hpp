#pragma once

#include "mapper/mapper.hpp"
#include "proto/speed.pb.h"
#include "ros/ros_speed.hpp"

template <> Speed Mapper<RosSpeed, Speed>::toProtobuf(const RosSpeed &message) {
  Speed speed;
  return speed;
};
