#pragma once

#include "mqtt/async_client.h"

#include <google/protobuf/message.h>

#include <string>
#include <vector>

namespace protobuf {

/**
 * This is a client to send a Protobuf message to the MQTT broker.
 */
class AsynchClient {
public:
  AsynchClient(const std::string &serverURI, const std::string &clientId,
               const std::string &topic);

  /**
   * @brief Connect to the MQTT message broker.
   */
  void connect();

  /**
   * @brief Disconnect from the MQTT message broker.
   */
  void disconnect() { client_.disconnect()->wait(); }

  /**
   * @brief Publish a message to the MQTT message broker.
   * @param message The Protobuf message to send.
   */
  void publish(const ::google::protobuf::Message &message);

private:
  // The topic to publish the message to.
  std::string topic_;

  // A buffer used to serialize the protobuf message.
  std::vector<uint8_t> buffer_;

  // MQTT connection options.
  mqtt::connect_options connection_opts_;

  // The MQTT client.
  mqtt::async_client client_;
};
} // namespace protobuf
