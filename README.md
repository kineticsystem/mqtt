# MQTT + Protobuf application

This is an example of a client sending a Protobuf message over MQTT. For this implementation I've used Mosquitto message broker, MQTT Paho C++ library and Google Protobuf library.

The simple application has been compiled and run on Ubuntu 20.04.

## Definitions

### MQTT

https://mqtt.org

MQTT is a lightweight, publish-subscribe network protocol that transports messages between devices. The protocol usually runs over TCP/IP.

### Mosquitto

https://mosquitto.org

Eclipse Mosquitto is an open source message broker that implements the MQTT protocol versions 5.0, 3.1.1 and 3.1. It is a server that receives and dispatches messages.
Eclipse Mosquitto provides a lightweight server implementation of the MQTT protocol that is suitable for all situations from full power machines to embedded and low power machines. Sensors and actuators, which are often the sources and destinations of MQTT messages, can be very small and lacking in power. This also applies to the embedded machines to which they are connected, which is where Mosquitto could be run.
As well as accepting connections from MQTT client applications, Mosquitto has a bridge which allows it to connect to other MQTT servers, including other Mosquitto instances. This allows networks of MQTT servers to be constructed, passing MQTT messages from any location in the network to any other, depending on the configuration of the bridges.

### Paho cpp client library

https://github.com/eclipse/paho.mqtt.cpp

The Eclipse Paho project provides open source, mainly client side, implementations of MQTT and MQTT-SN in a variety of programming languages. MQTT C++ client library, is a C++ library which implements versions 5.0, 3.1.1, and 3.1 of the MQTT protocol.

## Prerequisites

### Mosquitto installation

To install Mosquitto on Ubuntu 20.04 run the following command:

```sudo apt install mosquitto mosquitto-clients```

To test if mosquitto is working, open a teminal and execute the following:

```mosquitto_sub -h localhost -t test```

Then open another terminal and run the following:

```mosquitto_pub -h localhost -t test -m "hello world"```

A message "hello world" should be displayed on the subsriber terminal.

### Paho installation

There is no ready library for Ubuntu. We must compile the C library first and the the C++ library. For the C library run the following commands.

```
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
git checkout v1.3.8

cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
sudo cmake --build build/ --target install
sudo ldconfig
```

For the C++ library run the following commands.

```
git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp

cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
    -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
sudo cmake --build build/ --target install
sudo ldconfig
```
