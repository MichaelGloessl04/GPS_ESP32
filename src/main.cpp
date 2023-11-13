#include <HardwareSerial.h>
#include <MQTTHandler.h>
#include <JSONHandler.h>
#include <ESP32Time.h>
#include <TinyGPSPlus.h>
#include <WiFiManager.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <chro

const char* ADR = "192.168.88.216";

TaskHandle_t timeTaskHandle = NULL;
TaskHandle_t timePublisherTaskHandle = NULL;

HardwareSerial serial_port(2);
TinyGPSPlus gps;
ESP32Time rtc(3600);
MQTTHandler mqtt = MQTTHandler(ADR);
JSONHandler json = JSONHandler();
WiFiManager wifi;

int hour = 0;
int minute = 0;
int second = 0;

// PIN 18 is responsible for signal input
const int lichtschrnake = 18;
int reading = LOW;
int previous = LOW;
bool started = false;

int counter = 0;
String myTime;

int team_id;

void setTime(){
  if (gps.encode(serial_port.read())){
    hour = gps.time.hour();
    minute = gps.time.minute();
    second = gps.time.second();
  }
  rtc.setTime(second, minute, hour, 17, 11, 2023);
}

void recordTime(void *args) {

  while (1){

    reading = digitalRead(lichtschrnake); 

    if (reading == HIGH) { // && previous == LOW){
      myTime = counter++ + rtc.getTime(": %A, %B %d %Y %H:%M:%S:") + rtc.getMillis();
      Serial.println(myTime);
    }

    /*
    previous = reading;

    if (started){
      myTime = counter++ + rtc.getTime(": %A, %B %d %Y %H:%M:%S:") + rtc.getMillis();
      mqtt.publish(myTime.c_str());

      myTime = rtc.getTime("%A, %B %d %Y %H:%M:%S:") + rtc.getMillis();
      mqtt.publish(json.newTimestamp(mqtt.getClientName(), 0, team_id));

      Serial.println(myTime);
    }
    */
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String charMessage;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    charMessage += (char)message[i];
  }
  int new_id = json.getTeam(charMessage, mqtt.getClientName());
  if (new_id > 0) {
    team_id = new_id;
  }
}

void setup()  
{
  Serial.begin(115200);

  Serial.write("initializing GPS...");
  serial_port.begin(9400, SERIAL_8N1, 16, 17);
  Serial.write("Initialized");

  pinMode(lichtschrnake, INPUT);
  wifi.autoConnect("Lichtschranken Wifi", "LichtschrankenPWD");

  xTaskCreatePinnedToCore(recordTime, "TimeRecorder", 4096, NULL, 25, &timeTaskHandle, 1);

  mqtt.setClientName();
  mqtt.client.setCallback(callback);
}

void loop(){
  if (!mqtt.connected()){
    mqtt.reconnect();
  }
  mqtt.loop();
}
