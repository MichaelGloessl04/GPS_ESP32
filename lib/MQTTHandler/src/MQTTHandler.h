#ifndef MQTTHandler_h
#define MQTTHandler_h

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTHandler {
  public:
    MQTTHandler(const char* ssid, const char* password, const char* mqtt_server);
    void setup_wifi();
    void callback(char* topic, byte* message, unsigned int length);
    void reconnect();
  private:
    WiFiClient espClient;
    PubSubClient client;
};

#endif
