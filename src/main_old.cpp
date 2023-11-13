#include <HardwareSerial.h>
#include <MQTTHandler.h>
#include <ESP32Time.h>
#include <TinyGPSPlus.h>
#include <WiFiManager.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <chro

const char* ADR = "192.168.88.229";

TaskHandle_t timeTaskHandle = NULL;
TaskHandle_t timePublisherTaskHandle = NULL;

HardwareSerial serial_port(2);
TinyGPSPlus gps;  
ESP32Time rtc(3600);
MQTTHandler mqtt = MQTTHandler(ADR);
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

void setTime(){

    if (gps.encode(serial_port.read())){
      hour = gps.time.hour();
      minute = gps.time.minute();
      second = gps.time.second();
    } 

    rtc.setTime(second, minute, hour, 17, 11, 2023);
}

void publishTime(void *args) {
  mqtt.publish("myTime.c_str()");
  mqtt.publish(myTime.c_str());
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
      Serial.println(myTime);
    }
    */
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

  mqtt.setClientName();

  for (int i = 0; i < 200; i++){
    setTime();
  }
  Serial.write("FInished setting time");
  xTaskCreatePinnedToCore( recordTime, "TimeRecorder", 4096, NULL, 25, &timeTaskHandle, 0); // task for getting time //core0 // highest
  // task for connection just run until not connected // core1 ( in loop() )
  
  xTaskCreatePinnedToCore( publishTime, "PublishTimer", 4096, NULL, 25, &timePublisherTaskHandle, 1); // task for sending time // core1 // highest priority
  // task for setting the time // core1
}

void loop(){
  if (!mqtt.connected()){
    mqtt.reconnect();
  }
  
  /*
  reading = digitalRead(lichtschrnake); 

  if (reading == HIGH) {// && previous == LOW){
    started = !started;
    myTime = counter++ + rtc.getTime(": %A, %B %d %Y %H:%M:%S:") + rtc.getMillis();
    Serial.println(myTime);
  }

  previous = reading;

  if (started){
    mqtt.publish(myTime.c_str());
  }
  */
}
