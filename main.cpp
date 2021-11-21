// Copyright 2021 PickNik Inc.
// All rights reserved.
//
// Unauthorized copying of this code base via any medium is strictly prohibited.
// Proprietary and confidential.

#include "proto/sensor.pb.h"
#include <fstream>
#include <iostream>

int main() {

  Sensor sensor;
  sensor.set_name("Laboratory");
  sensor.set_temperature(23.4);
  sensor.set_humidity(68);
  sensor.set_door(Sensor_SwitchLevel_OPEN);

  std::ofstream ofs("sensor.data", std::ios_base::out | std::ios_base::binary);
  sensor.SerializeToOstream(&ofs);

  std::cout << "Hello Proto!" << std::endl;
  return 0;
}
