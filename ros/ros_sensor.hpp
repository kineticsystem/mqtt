#pragma once

#include <string>

class RosSensor {

public:
  RosSensor() = default;

  const std::string &name() const;
  void setName(const std::string &name);

  double temperature() const;
  void setTemperature(double temperature);

  int32_t humidity() const;
  void setHumidity(int32_t humidity);

  enum class SwitchLevel { kClosed, kOPen };
  SwitchLevel door() const;
  void setDoor(SwitchLevel door);

private:
  std::string name_;
  double temperature_;
  int32_t humidity_;
  SwitchLevel door_ = SwitchLevel::kClosed;
};
