/*
comms-library.ino
udp comms library tester for eSpidey
b4ked 2024
*/

#include "comms.h"

// Include local header files
#include <udp_defs.h>
#include <network_defs.h>

// Include library files
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;
const int localUdpPort = PORT;  // Arbitrary port for UDP server

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

  // Define IP address, gateway, subnet, and DNS
  IPAddress staticIP(STATIC_IP1, STATIC_IP2, STATIC_IP3, STATIC_IP4);
  IPAddress gateway(GATEWAY_IP1, GATEWAY_IP2, GATEWAY_IP3, GATEWAY_IP4);
  IPAddress subnet(SUBNET_MASK1, SUBNET_MASK2, SUBNET_MASK3, SUBNET_MASK4);
  IPAddress dns(DNS_IP1, DNS_IP2, DNS_IP3, DNS_IP4);

  // Initialize WiFi with static IP configuration
  WiFi.config(staticIP, gateway, subnet, dns);

  // Connect to WiFi
  WiFi.begin(network_ssid, network_ssid_pw);

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

  uint8_t udpData[20];

  int packetSize = udp.parsePacket();

  if (packetSize) 
  {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0; // Null-terminate the received data
    }
    
    // Print received packet
    Serial.println("Received UDP Packet:");
    Serial.print("Length: ");
    Serial.println(len);

    // Parse and print the packet content
    Serial.println(parseUdpPacket(incomingPacket, len, udpData));

    for (int i = 0; i < 20; i++)
    {
      Serial.println(udpData[i], HEX);
    }
    
  }

}

