#include "MQTTHandler.h"

MQTTHandler::MQTTHandler(String mqtt_server) : client(espClient) {
  this->mqtt_server = mqtt_server;
  this->client.setServer(mqtt_server.c_str(), 1883);
  this->team_id = 0;
}

void MQTTHandler::setClientName() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char client_name[18];
  snprintf(client_name, sizeof(client_name), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  const char* macChar = client_name;
  this->client_name = String(macChar);
  Serial.print("ClientName: ");
  Serial.println(this->client_name);
}

String MQTTHandler::getClientName() {
  return this->client_name;
}

void MQTTHandler::setTeamId(int team_id) {
  this->team_id = team_id;
}

int MQTTHandler::getTeamId() {
  return this->team_id;
}

void MQTTHandler::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection for: ");
    Serial.println(this->client_name.c_str());
    if (client.connect(this->client_name.c_str(), "admin", "ChallengeTiming23")) {
      Serial.println("connected");
      client.subscribe("set-team", 0);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds\n");
      delay(5000);
    }
  }
}

void MQTTHandler::publish(String payload) {
  this->client.publish("TimeData", payload.c_str(), 2);
}

bool MQTTHandler::connected() {
  return this->client.connected();
}

void MQTTHandler::loop() {
  this->client.loop();
}
