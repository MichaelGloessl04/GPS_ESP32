#ifndef MQTTHandler_h
#define MQTTHandler_h

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTHandler {
  public:
    MQTTHandler(const char* mqtt_server);
    void callback(char* topic, byte* message, unsigned int length);
    void reconnect();
    void setClientName(const char* client_name);
    PubSubClient client;
  private:
    const char* client_name;
    const char* mqtt_server;
    WiFiClient espClient;
};

#endif
