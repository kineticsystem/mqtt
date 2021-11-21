// Copyright 2021 PickNik Inc.
// All rights reserved.
//
// Unauthorized copying of this code base via any medium is strictly prohibited.
// Proprietary and confidential.

#include "mqtt/async_client.h"
#include "proto/sensor.pb.h"

#include <fstream>
#include <iostream>

namespace {

constexpr auto DFLT_SERVER_ADDRESS = "tcp://localhost:1883";
constexpr auto CLIENT_ID = "paho_cpp_async_publish";

constexpr auto TOPIC = "test";
constexpr int QOS = 1;
constexpr auto LWT_PAYLOAD = "Last will and testament.";
constexpr auto TIMEOUT = std::chrono::seconds(10);

// Message content.
constexpr auto PAYLOAD = "Hello World!";

} // namespace

/**
 * @brief This is a MQTT client example.
 * To test this example, open a terminal and run a mosquito subscriber
 * with the following command: "mosquitto_sub -h localhost -t test".
 * Then execute this application.
 */
int main() {

  // Create a Protobuf payload.

  Sensor sensor;
  sensor.set_name("Laboratory");
  sensor.set_temperature(23.4);
  sensor.set_humidity(68);
  sensor.set_door(Sensor_SwitchLevel_OPEN);

  std::ofstream ofs("sensor.data", std::ios_base::out | std::ios_base::binary);
  sensor.SerializeToOstream(&ofs);

  // Initialize an MQTT client.

  mqtt::async_client client(DFLT_SERVER_ADDRESS, CLIENT_ID);

  auto connection_opts = mqtt::connect_options_builder()
                             .clean_session()
                             .will(mqtt::message(TOPIC, LWT_PAYLOAD, QOS))
                             .finalize();

  try {

    // Connect.

    mqtt::token_ptr token = client.connect(connection_opts);
    token->wait();

    // Send a message.

    mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, PAYLOAD);
    pubmsg->set_qos(QOS);
    client.publish(pubmsg)->wait_for(TIMEOUT);

    // Disconnect.

    client.disconnect()->wait();

  } catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << std::endl;
    return 1;
  }

  return 0;
}
