#pragma once

#include <string>

class RosSpeed {

public:
  RosSpeed() = default;

  const std::string &name() const;
  void setName(const std::string &name);

  double speed() const;
  void setSpeed(double speed);

private:
  std::string name_;
  double speed_;
};
