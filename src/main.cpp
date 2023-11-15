#include <HardwareSerial.h>
#include <MQTTHandler.h>
#include <ESP32Time.h>
#include <TinyGPSPlus.h>
#include <WiFiManager.h>

const char* ADR = "10.10.90.249";

const char* ssid = "ZeroETiming";
const char* password = "ChallengeTiming23";

int counter = 0;

HardwareSerial serial_port(2);
TinyGPSPlus gps;  
ESP32Time rtc(3600);
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

void setTime(){

  if (gps.encode(serial_port.read())){
    hour = gps.time.hour();
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

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  int attemptCount = 0;
  while (WiFi.status() != WL_CONNECTED && attemptCount < 20) {
    delay(500);
    Serial.print(".");
    attemptCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
  } else {
    Serial.println("\nFailed to connect to WiFi. Please check your credentials.");
  }
}

void setup()  
{
  Serial.begin(115200);

  Serial.write("initializing GPS...");
  serial_port.begin(9600, SERIAL_8N1, 16, 17);
  Serial.write("Initialized");

  pinMode(lichtschrnake, INPUT);
  connectToWiFi();

  mqtt.setClientName();
}

void loop(){
  if (!mqtt.connected()){
    mqtt.reconnect();
  }

  while (serial_port.available() > 0){
    setTime();
  }

  reading = digitalRead(lichtschrnake); 

  if (reading == HIGH && previous == LOW){
    started = !started;
  }

  previous = reading;

  if (started){
    myTime = rtc.getTime("%A, %B %d %Y %H:%M:%S:") + rtc.getMillis();
    mqtt.publish(myTime.c_str());
    Serial.println(myTime);
  }
}
