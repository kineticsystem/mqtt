#pragma once

#include "mqtt/async_client.h"

#include <iostream>
#include <string>
#include <vector>

namespace {
constexpr int QOS = 1;
constexpr auto TIMEOUT = std::chrono::seconds(10);
} // namespace

namespace protobuf {

/**
 * This is a client to send a Protobuf message to the MQTT broker.
 */
template <class Protobuf> class AsynchClient {
public:
  AsynchClient<Protobuf>(const std::string &serverURI,
                         const std::string &clientId, const std::string &topic)
      : client_{mqtt::async_client{serverURI, clientId}}, topic_{topic} {

    connection_opts_ =
        mqtt::connect_options_builder().clean_session().finalize();
  }

  void connect() { client_.connect(connection_opts_)->wait(); }

  void disconnect() { client_.disconnect()->wait(); }

  void publish(const Protobuf &message) {

    // Resize the buffer to fit the message.
    const int size = message.ByteSizeLong();
    if (size > buffer_.size()) {
      buffer_.resize(size);
    }
    message.SerializeToArray(buffer_.data(), buffer_.size());

    mqtt::message_ptr pubmsg =
        mqtt::make_message(topic_, buffer_.data(), buffer_.size());
    pubmsg->set_qos(QOS);
    client_.publish(pubmsg)->wait_for(TIMEOUT);
  }

private:
  std::string topic_;
  std::vector<uint8_t> buffer_;
  mqtt::connect_options connection_opts_;
  mqtt::async_client client_;
};
} // namespace protobuf
