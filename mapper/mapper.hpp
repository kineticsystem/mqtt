#pragma once

template <class RosMessage, class ProtobufMessage> class Mapper {
public:
  ProtobufMessage toProtobuf(const RosMessage &message) {
    ProtobufMessage protobuf;
    return protobuf;
  }
};
