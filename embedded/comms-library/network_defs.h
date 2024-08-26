/*
network definitions for eSpidey
b4ked 2024
*/

#ifndef NETWORK_DEFS_H
#define NETWORK_DEFS_H

//network information
//TODO: change esp32 to an access point later - start its own wifi network
extern const char* network_ssid = "VM9449556_EXT";
extern const char* network_ssid_pw = "howdoiknow";

//IP and port definitions
// Define your static IP address, gateway, and subnet
#define STATIC_IP1 192
#define STATIC_IP2 168
#define STATIC_IP3 0
#define STATIC_IP4 100

#define GATEWAY_IP1 192
#define GATEWAY_IP2 168
#define GATEWAY_IP3 0
#define GATEWAY_IP4 1

#define SUBNET_MASK1 255
#define SUBNET_MASK2 255
#define SUBNET_MASK3 255
#define SUBNET_MASK4 0

#define DNS_IP1 8
#define DNS_IP2 8
#define DNS_IP3 8
#define DNS_IP4 8

#define PORT 1234

//serial definnitions
//TODO: move to a different config?
#define SERIAL_BAUD_RATE 115200

#endif

