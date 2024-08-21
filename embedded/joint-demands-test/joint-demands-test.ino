#include <WiFi.h>
#include <WiFiUdp.h>8

// Replace with your network credentials
const char* ssid = "VM9449556_EXT";
const char* password = "howdoiknow";

WiFiUDP udp;
const int localUdpPort = 1234;  // Arbitrary port for UDP server

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
      incomingPacket[len] = 0; // Null-terminate the received data
    }
    
    // Print received packet
    Serial.println("Received UDP Packet:");
    Serial.print("Length: ");
    Serial.println(len);

    // Parse and print the packet content
    parseUdpPacket(incomingPacket, len);
  }
}

void parseUdpPacket(const char* packet, int length) {
  if (length < 8) {
    Serial.println("Error: Packet too short");
    return;
  }

  // Header
  uint8_t startOfPacket = packet[0];
  uint8_t commandId = packet[1];
  uint16_t dataLength = (packet[2] << 8) | packet[3];
  uint32_t checksum = (packet[4] << 24) | (packet[5] << 16) | (packet[6] << 8) | packet[7];
  
  // Check start of packet
  if (startOfPacket != 0xAA) {
    Serial.println("Error: Invalid start of packet");
    return;
  }

  Serial.println("Header:");
  Serial.print("  Start of Packet: 0x");
  Serial.println(startOfPacket, HEX);
  Serial.print("  Command ID: 0x");
  Serial.println(commandId, HEX);
  Serial.print("  Data Length: ");
  Serial.println(dataLength);
  Serial.print("  Checksum: 0x");
  Serial.println(checksum, HEX);

  // Check if data length matches actual length
  if (length != 8 + dataLength) {
    Serial.println("Error: Data length mismatch");
    return;
  }

  // Data parsing
  Serial.println("Data:");
  if (commandId == 0x01) {  // Joint Position Demand
    if (dataLength < 17) {
      Serial.println("Error: Insufficient data length for Joint Position Demand");
      return;
    }

    uint8_t legId = packet[8];
    Serial.print("  Leg ID: ");
    Serial.println(legId);

    for (int i = 0; i < 4; i++) {
      int32_t jointPosition = (packet[9 + i * 4] |
                               (packet[10 + i * 4] << 8) |
                               (packet[11 + i * 4] << 16) |
                               (packet[12 + i * 4] << 24));
      Serial.print("  Joint ");
      Serial.print(i);
      Serial.print(" Position: ");
      Serial.println(jointPosition);
    }
  } else {
    Serial.println("Error: Unknown Command ID");
  }
}
