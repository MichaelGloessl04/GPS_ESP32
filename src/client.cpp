#include <HardwareSerial.h>
#include <WiFi.h>

HardwareSerial serial_port(2); // use UART2

/*
$GPGGA: 3D location and accuracy data

*/

const char* ssid = "YOUR_WIFI_SSID";     // CHANGE TO YOUR WIFI SSID
const char* password = "YOUR_WIFI_PASSWORD"; // CHANGE TO YOUR WIFI PASSWORD
const char* serverAddress = "192.168.0.180"; // CHANGE TO ESP32#2'S IP ADDRESS
const int serverPort = 4080;
WiFiClient TCPclient;

void setup()  
{  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // connect to TCP server (Arduino #2)
  if (TCPclient.connect(serverAddress, serverPort)) {
    Serial.println("Connected to TCP server");
  } else {
    Serial.println("Failed to connect to TCP server");
  }

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

  if (!TCPclient.connected()) {   
    Serial.println("Connection is disconnected");
    TCPclient.stop();

    // reconnect to TCP server (Arduino #2)
    if (TCPclient.connect(serverAddress, serverPort)) {
      Serial.println("Reconnected to TCP server");
    } else {
      Serial.println("Failed to reconnect to TCP server");
    }
  }

  TCPclient.write('connected');
  TCPclient.flush();
}
