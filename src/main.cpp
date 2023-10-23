#include <HardwareSerial.h>

HardwareSerial serial_port(2); // use UART2

/*
$GPGGA: 3D location and accuracy data

*/

void setup()  
{
  Serial.begin(115200);

  Serial.write("initializing GPS...");
  serial_port.begin(9600, SERIAL_8N1, 16, 17);
  Serial.write("Initialized");
}

void loop(){
  while (serial_port.available() > 0){
    // get the byte data from the GPS
    uint8_t gpsData = serial_port.read();
    Serial.write(gpsData);
  }
}
