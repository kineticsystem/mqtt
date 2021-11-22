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
template <class RosMessage, class ProtobufMessage>
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

  // The connection Quality of Service.
  static constexpr int QOS = 1;

  // Connection and message publishing timeout.
  static constexpr auto TIMEOUT = std::chrono::seconds(10);
};

template <class RosMessage, class ProtobufMessage>
DefaultAsynchClient<RosMessage, ProtobufMessage>::DefaultAsynchClient(
    const std::string &serverURI, const std::string &clientId)
    : client_{mqtt::async_client{serverURI, clientId}} {

  connection_opts_ = mqtt::connect_options_builder().clean_session().finalize();
}

template <class RosMessage, class ProtobufMessage>
void DefaultAsynchClient<RosMessage, ProtobufMessage>::connect() {
  client_.connect(connection_opts_)->wait();
}

template <class RosMessage, class ProtobufMessage>
void DefaultAsynchClient<RosMessage, ProtobufMessage>::disconnect() {
  client_.disconnect()->wait();
}

template <class RosMessage, class ProtobufMessage>
void DefaultAsynchClient<RosMessage, ProtobufMessage>::publish(
    const google::protobuf::Message &message, const std::string &topic) {

  // Resize the buffer to fit the message.
  const int size = message.ByteSizeLong();
  if (size > buffer_.size()) {
    buffer_.resize(size);
  }
  message.SerializeToArray(buffer_.data(), buffer_.size());

  mqtt::message_ptr mqtt_message =
      mqtt::make_message(topic, buffer_.data(), buffer_.size());
  mqtt_message->set_qos(QOS);
  client_.publish(mqtt_message)->wait_for(TIMEOUT);
}
} // namespace protobuf
