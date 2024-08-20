#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "VM9449556_EXT";
const char* password = "howdoiknow";

WiFiUDP udp;
const int localUdpPort = 1234;  // Arbitrary port

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());  // Print the ESP32 IP address

  udp.begin(localUdpPort);
  Serial.println("UDP server started");
  
}

void loop() {

  char incomingPacket[255];
  int packetSize = udp.parsePacket();

  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    Serial.printf("Received packet: %s\n", incomingPacket);
    // Process packet data to control GPIO, etc.
  }
  
}
