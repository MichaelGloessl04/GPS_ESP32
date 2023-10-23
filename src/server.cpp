#include <HardwareSerial.h>
#include <WiFi.h>

HardwareSerial serial_port(2); // use UART2

/*
$GPGGA: 3D location and accuracy data

*/

#define SERVER_PORT 4080

const char* ssid = "YOUR_WIFI_SSID";     // CHANGE TO YOUR WIFI SSID
const char* password = "YOUR_WIFI_PASSWORD"; // CHANGE TO YOUR WIFI PASSWORD

WiFiServer TCPserver(SERVER_PORT);


void setup()  
{
  Serial.begin(115200);

  Serial.write("initializing GPS...");
  serial_port.begin(9600, SERIAL_8N1, 16, 17);
  Serial.write("Initialized");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print your local IP address:
  Serial.print("ESP32 #2: TCP Server IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("ESP32 #2: -> Please update the serverAddress in ESP32 #1 code");


  TCPserver.begin();
}

void loop(){
  while (serial_port.available() > 0){
    // get the byte data from the GPS
    uint8_t gpsData = serial_port.read();
    Serial.write(gpsData);
  } 
  WiFiClient client = TCPserver.available();

  if (client) {
    // Read the command from the TCP client:
    char command = client.read();
    Serial.print("ESP32 #2: - Received command: ");
    Serial.println(command);

    client.stop();
  }
}
