#ifndef MQTTHandler_h
#define MQTTHandler_h

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTHandler {
  public:
    MQTTHandler(const char* mqtt_server);
    void callback(char* topic, byte* message, unsigned int length);
    void reconnect();
    PubSubClient client;
  private:
    const char* mqtt_server;
    WiFiClient espClient;
};

#endif
