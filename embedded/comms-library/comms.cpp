/*
comms.cpp
udp comms library for eSpidey
b4ked 2024
*/

#include "comms.h"

//TODO: add compiler ifdef to all print statements - clean up printing

bool parseUdpPacket(const char* packetIn, int lengthIn, uint8_t* dataOut)
{
  //transfer arguments into local variables - TODO: clean this up later
  int length = lengthIn;
  const char* packet = packetIn;

  if (length < UDP_PACKET_MIN_LEN) 
  {
    return false;
  }

  // Header
  uint8_t startOfPacket = packet[UDP_START_BYTE_LOC];
  legCommandIDType commandId = (legCommandIDType) packet[UDP_COMMAND_ID_LOC];
  uint16_t dataLength = (packet[UDP_DATA_LENGTH_LOC] << 8) | packet[UDP_DATA_LENGTH_LOC + 1];
  uint32_t checksum = (packet[UDP_CHECKSUM_LOC] << 24) | (packet[UDP_CHECKSUM_LOC + 1] << 16) | (packet[UDP_CHECKSUM_LOC + 2] << 8) | packet[UDP_CHECKSUM_LOC + 3];
  
  // Check start of packet
  if (startOfPacket != UDP_START_BYTE_DATA) {
    return false;
  }

  // Data parsing
  if (commandId == legJointDemandsCmd) 
  {  // Joint Position Demand
    if (dataLength < 17) 
    {
      return false;
    }

    uint8_t legId = packet[8];

    uint32_t jointPosition = 0;
    for (int i = 0; i < 4; i++) {
      jointPosition = (packet[9 + i * 4] |
                               (packet[10 + i * 4] << 8) |
                               (packet[11 + i * 4] << 16) |
                               (packet[12 + i * 4] << 24));

    }

    memcpy((void *) dataOut, (void *) &jointPosition, sizeof(jointPosition));
    return true;
  } 
  else 
  {
    //invalid command id
    return false;
  }
}