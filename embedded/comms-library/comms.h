/*
comms.h
udp comms library for eSpidey
b4ked 2024
*/
#include <stdint.h>
#include <string.h>

//debug definitions
#define DEBUG_SERIAL_PRINT 1

//include udp definitions header file
#include "udp_defs.h"

bool parseUdpPacket(const char* packetIn, int lengthIn, uint8_t* dataOut);