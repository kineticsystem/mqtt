#pragma once

#include "asynch_client.hpp"

#include <string>
#include <vector>

#include "mqtt/async_client.h"

#include <google/protobuf/message.h>

namespace protobuf {

/**
 * This is a client to send a Protobuf message to the MQTT broker.
 */
class DefaultAsynchClient : public AsynchClient {
public:
  /**
   * @brief A client to send a Protobuf message to the MQTT broker.
   * @param serverURI The HQTT server broker URI.
   * @param clientId A client global unique identifier.
   */
  DefaultAsynchClient(const std::string &serverURI,
                      const std::string &clientId);

  /**
   * @brief Connect to the MQTT message broker.
   */
  void connect() override;

  /**
   * @brief Disconnect from the MQTT message broker.
   */
  void disconnect() override;

  /**
   * @brief Publish a message to the MQTT message broker.
   * @param message The Protobuf message to send.
   * @param topic The topic to send the Protobuf message to.
   */
  void publish(const ::google::protobuf::Message &message,
               const std::string &topic) override;

private:
  // A buffer used to serialize the protobuf message.
  std::vector<uint8_t> buffer_;

  // MQTT connection options.
  mqtt::connect_options connection_opts_;

  // The MQTT client.
  mqtt::async_client client_;
};
} // namespace protobuf
