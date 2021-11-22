#include "ros_sensor.hpp"

#include <string>

const std::string &RosSensor::name() const { return name_; }

void RosSensor::setName(const std::string &name) { name_ = name; }

double RosSensor::temperature() const { return temperature_; }

void RosSensor::setTemperature(double temperature) {
  temperature_ = temperature;
}

int32_t RosSensor::humidity() const { return humidity_; }

void RosSensor::setHumidity(int32_t newHumidity) { humidity_ = newHumidity; }

RosSensor::SwitchLevel RosSensor::door() const { return door_; }

void RosSensor::setDoor(RosSensor::SwitchLevel newDoor) { door_ = newDoor; }
