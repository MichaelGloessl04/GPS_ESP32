#ifndef MQTTHandler_h
#define MQTTHandler_h

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTHandler {
  public:
    MQTTHandler(const char* mqtt_server);
    void callback(char* topic, byte* message, unsigned int length);
    void reconnect();
    void publish(const char* payload);
    void setClientName();
    const char* getClientName();
  private:
    const char* client_name;
    const char* mqtt_server;
    WiFiClient espClient;
    PubSubClient client;
};

#endif