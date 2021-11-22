#include "default_asynch_client.hpp"

#include <string>
#include <vector>

namespace {
// The connection Quality of Service.
constexpr int QOS = 1;

// Connection and message publishing timeout.
constexpr auto TIMEOUT = std::chrono::seconds(10);
} // namespace

namespace protobuf {
DefaultAsynchClient::DefaultAsynchClient(const std::string &serverURI,
                                         const std::string &clientId)
    : client_{mqtt::async_client{serverURI, clientId}} {

  connection_opts_ = mqtt::connect_options_builder().clean_session().finalize();
}

void DefaultAsynchClient::connect() {
  client_.connect(connection_opts_)->wait();
}

void DefaultAsynchClient::disconnect() { client_.disconnect()->wait(); }

void DefaultAsynchClient::publish(const google::protobuf::Message &message,
                                  const std::string &topic) {

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
