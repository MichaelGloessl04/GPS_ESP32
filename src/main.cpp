#include <HardwareSerial.h>
#include <MQTTHandler.h>
#include <ESP32Time.h>
#include <TinyGPSPlus.h>
#include <WiFiManager.h>

const char* ADR = "192.168.88.229";

MQTTHandler mqtt = MQTTHandler(ADR);
WiFiManager wifi;

void setup()
{
  Serial.begin(115200);
  wifi.autoConnect("Lichtschranken Wifi", "LichtschrankenPWD");
}

void loop(){
  if (!mqtt.client.connected()){
    mqtt.reconnect();
  }

  mqtt.client.publish("test", "tetetetet");
}