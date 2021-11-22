#include "default_asynch_client.hpp"

#include "proto/sensor.pb.h"
#include "ros/ros_sensor.hpp"

#include <iostream>

constexpr auto DEFAULT_SERVER_ADDRESS = "tcp://localhost:1883";
constexpr auto CLIENT_ID = "paho_cpp_async_publish";
constexpr auto TOPIC = "test";

/**
 * Send a Protobuf message to an MQTT message broker.
 *
 * To test this example, first open a terminal and start a Mosquito subscriber
 * with the following command: "mosquitto_sub -h localhost -t test".
 *
 * Then execute this application.
 */
int main() {

  // Create a Protobuf payload.

  Sensor sensor;
  sensor.set_name("Laboratory");
  sensor.set_temperature(23.4);
  sensor.set_humidity(68);
  sensor.set_door(Sensor_SwitchLevel_OPEN);

  // Initialize a client.
  protobuf::DefaultAsynchClient<RosSensor, Sensor> client(
      DEFAULT_SERVER_ADDRESS, CLIENT_ID);

  // Connect to the MQTT broker, send a message and disconnect.
  try {

    client.connect();
    client.publish(sensor, TOPIC);
    client.disconnect();

  } catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << std::endl;
    return 1;
  }

  return 0;
}
