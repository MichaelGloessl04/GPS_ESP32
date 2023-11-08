#include "MQTTHandler.h"

MQTTHandler::MQTTHandler(const char* mqtt_server) : client(espClient) {
  this->mqtt_server = mqtt_server;
  client.setServer(mqtt_server, 1883);
}

void MQTTHandler::callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void MQTTHandler::setClientName() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char client_name[18];
  snprintf(client_name, sizeof(client_name), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  const char* macChar = client_name;
  this->client_name = client_name;
}

char* MQTTHandler::getClientName() {
  return this->client_name;
}

void MQTTHandler::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(client_name, "admin", "ChallengeTiming23")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}