#ifndef MQTTHandler_h
#define MQTTHandler_h

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTHandler {
  public:
    MQTTHandler(const char* mqtt_server);
    void reconnect();
    void publish(const char* payload);
    bool connected();
    void setClientName();
    void loop();
    const char* getClientName();
    PubSubClient client;
  private:
    WiFiClient espClient;
    const char* client_name;
    const char* mqtt_server;
};

#endif