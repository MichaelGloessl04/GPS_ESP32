#include <HardwareSerial.h>
#include <MQTTHandler.h>
#include <ESP32Time.h>
#include <TinyGPSPlus.h>
#include <WiFiManager.h>

const char* ADR = "192.168.88.229";

MQTTHandler mqtt = MQTTHandler(ADR);
WiFiManager wifi;

int hour = 0;
int minute = 0;
int second = 0;

const int lichtschrnake = 18;
int reading = LOW;
int previous = LOW;
bool started = false;

String myTime;

void setup()  
{
  Serial.begin(115200);

  Serial.write("initializing GPS...");
  serial_port.begin(9600, SERIAL_8N1, 16, 17);
  Serial.write("Initialized");

  pinMode(lichtschrnake, INPUT);

  // set the time to the time i get from the gps (hour +2)
}

void setTime(){

  if (gps.encode(serial_port.read())){
    hour = gps.time.hour() + 1;
    minute = gps.time.minute();
    second = gps.time.second();
    Serial.print(hour);
    Serial.print(",");
    Serial.print(minute);
    Serial.print(",");
    Serial.println(second);

  }

  rtc.setTime(second, minute, hour, 17, 11, 2023);
}

void loop(){

  while (serial_port.available() > 0){
    // get the byte data from the GPS
    // uint8_t gpsData = serial_port.read();
    // Serial.write(gpsData);

    // do the synchronization

    setTime();
  }

  reading = digitalRead(lichtschrnake); 

  if (reading == HIGH && previous == LOW){
    started = !started;
  }

  previous = reading;

  if (started){
    // Serial.println(serial_port);
    myTime = rtc.getTime("%A, %B %d %Y %H:%M:%S:") + rtc.getMillis();
    Serial.println(myTime);
  }
}

/*
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
}*/

