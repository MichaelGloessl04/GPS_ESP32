#include <HardwareSerial.h>
#include <ESP32Time.h>
#include <TinyGPSPlus.h>

HardwareSerial serial_port(2); // use UART2
TinyGPSPlus gps;
ESP32Time rtc(3600);  // offset in seconds GMT+1


// $GPGGA: 3D location and accuracy data

int hour = 0;
int minute = 0;
int second = 0;

const int lichtschrnake = 18;
bool started = false;

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

void loop(){
  while (serial_port.available() > 0){
    // get the byte data from the GPS
    // uint8_t gpsData = serial_port.read();
    // Serial.write(gpsData);

    // do the synchronization

    setTime();
  }

  if (digitalRead(lichtschrnake) == HIGH && started == false){
    started != started;
  }
  else if (digitalRead(lichtschrnake) == HIGH && started == true) {
    started != started;
  }

  if (started){
    // Serial.println(serial_port);
    Serial.print(rtc.getTime("%A, %B %d %Y %H:%M:%S:"));
    Serial.println(rtc.getMillis());
  }
}

// make a jumper and conntect the gps sensors