#ifndef MQTTHandler_h
#define MQTTHandler_h

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTHandler {
  public:
    MQTTHandler(String mqtt_server);
    void reconnect();
    void publish(String payload);
    bool connected();
    void setClientName();
    String getClientName();
    void setTeamId(int new_id);
    int getTeamId();
    void loop();
    PubSubClient client;
  private:
    WiFiClient espClient;
    String client_name;
    String mqtt_server;
    int team_id;
};

#endif