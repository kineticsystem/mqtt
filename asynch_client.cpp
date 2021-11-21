#include "asynch_client.hpp"

#include <string>
#include <vector>

namespace {
// The connection Quality of Service.
constexpr int QOS = 1;

// Connection and message publishing timeout.
constexpr auto TIMEOUT = std::chrono::seconds(10);
} // namespace

namespace protobuf {
AsynchClient::AsynchClient(const std::string &serverURI,
                           const std::string &clientId,
                           const std::string &topic)
    : client_{mqtt::async_client{serverURI, clientId}}, topic_{topic} {

  connection_opts_ = mqtt::connect_options_builder().clean_session().finalize();
}

void AsynchClient::connect() { client_.connect(connection_opts_)->wait(); }

void AsynchClient::publish(const google::protobuf::Message &message) {

  // Resize the buffer to fit the message.
  const int size = message.ByteSizeLong();
  if (size > buffer_.size()) {
    buffer_.resize(size);
  }
  message.SerializeToArray(buffer_.data(), buffer_.size());

  mqtt::message_ptr mqtt_message =
      mqtt::make_message(topic_, buffer_.data(), buffer_.size());
  mqtt_message->set_qos(QOS);
  client_.publish(mqtt_message)->wait_for(TIMEOUT);
}
} // namespace protobuf
