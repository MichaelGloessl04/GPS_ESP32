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
    const char* getClientName();
    void setTeamId(int new_id);
    int getTeamId();
    void loop();
    PubSubClient client;
  private:
    WiFiClient espClient;
    const char* client_name;
    const char* mqtt_server;
    int team_id;
};

#endif