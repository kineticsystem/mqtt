#pragma once

#include <string>

#include <google/protobuf/message.h>

namespace protobuf {

/**
 * This is a client interface to implement for a Protobuf client.
 */
class AsynchClient {
public:
  /**
   * @brief Connect to the MQTT message broker.
   */
  virtual void connect() = 0;

  /**
   * @brief Disconnect from the MQTT message broker.
   */
  virtual void disconnect() = 0;

  /**
   * @brief Publish a message to the MQTT message broker.
   * @param message The Protobuf message to send.
   * @param topic The topic to send the Protobuf message to.
   */
  virtual void publish(const ::google::protobuf::Message &message,
                       const std::string &topic) = 0;
};
} // namespace protobuf
