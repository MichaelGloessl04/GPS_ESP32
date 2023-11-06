#include <HardwareSerial.h>
#include <MQTTHandler.h>
#include <ESP32Time.h>
#include <TinyGPSPlus.h>

const char* WIFI = "Atomkraftwerk-Sektor-6";
const char* PWD = "healuwuu";
const char* ADR = "192.168.88.229";

MQTTHandler mqtt = MQTTHandler(WIFI, PWD, ADR);

void setup()  
{
  Serial.begin(115200);
  mqtt.setup_wifi();
}

void loop(){
  if (!mqtt.client.connected()){
    mqtt.reconnect();
  }

  mqtt.client.publish("test", "tetetetet");
}