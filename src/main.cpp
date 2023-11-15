#include <HardwareSerial.h>
#include <MQTTHandler.h>
#include <JSONHandler.h>
#include <ESP32Time.h>
#include <TinyGPSPlus.h>
#include <WiFi.h>

#define lichtschranke 21

String ADR = "192.168.88.216";

HardwareSerial serial_port(2);
TinyGPSPlus gps;
ESP32Time rtc(3600);
MQTTHandler mqtt = MQTTHandler(ADR);
JSONHandler json = JSONHandler();

int hour = 0;
int minute = 0;
int second = 0;

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

void recordTime() {
  reading = digitalRead(lichtschranke); 
  if (reading == HIGH) {
    myTime = String(rtc.getEpoch());
    myTime += rtc.getMillis();
    Serial.println(myTime);
    mqtt.publish(json.newTimestamp(mqtt.getClientName(),
                                   myTime,
                                   mqtt.getTeamId()));
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  String charMessage;
  int new_id;

  for (int i = 0; i < length; i++) {
    charMessage += message[i];
  }

  new_id = json.getTeam(charMessage, mqtt.getClientName());
  if (new_id > 0) {
    mqtt.setTeamId(new_id);
  }
}

void setup()  
{
  Serial.begin(115200);
  serial_port.begin(9400, SERIAL_8N1, 16, 17);

  pinMode(lichtschranke, INPUT_PULLDOWN);
  for (int i = 0; i < 100; i++)
  {
    setTime();
    delay(100);
  }
  Serial.println("time set");

}

void loop(){
  recordTime();
}
