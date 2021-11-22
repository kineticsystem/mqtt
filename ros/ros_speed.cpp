#include "ros_speed.hpp"

#include <string>

const std::string &RosSpeed::name() const { return name_; }

void RosSpeed::setName(const std::string &name) { name_ = name; }

double RosSpeed::speed() const { return speed_; }

void RosSpeed::setSpeed(double speed) { speed_ = speed; }
