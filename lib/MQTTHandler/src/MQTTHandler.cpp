#include "MQTTHandler.h"
#include "string.h"

MQTTHandler::MQTTHandler(const char* mqtt_server) : client(espClient) {
  this->mqtt_server = mqtt_server;
  client.setServer(mqtt_server, 1883);
}

void MQTTHandler::setClientName(const char* client_name) {
  /*uint8_t mac[6];
  WiFi.macAddress(mac);
  const char client_name[6];
  for (size_t i = 0; i < sizeof(mac); i++)
  {
    client_name[i] = mac[i];
  }*/
  this->client_name = client_name;
  Serial.print(this->client_name);
}

const char* MQTTHandler::getClientName() {
  return client_name;
}

void MQTTHandler::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(this->client_name, "admin", "ChallengeTiming23")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
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

void MQTTHandler::publish(const char* payload) {
  client.publish("TimeData", payload, 2);
}

bool MQTTHandler::connected() {
  return client.connected();
}
