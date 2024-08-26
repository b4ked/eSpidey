/*
udp protocol specification definitions for eSpidey
b4ked 2024
*/

#ifndef UDP_DEFS_H
#define UDP_DEFS_H

//data byte definitions for udp buffer
#define UDP_START_BYTE_DATA 0xAA
#define UDP_DEFAULT_CHECKSUM_DATA 0xFFFFFFFF

//byte location definitions in udp buffer
//header locations
#define UDP_START_BYTE_LOC 0
#define UDP_COMMAND_ID_LOC 1
#define UDP_DATA_LENGTH_LOC 2
#define UDP_CHECKSUM_LOC 4
//data locations
#define UDP_LEG_ID_LOC 8
#define UDP_JOINT_DATA_START_LOC 9

//byte length definitions for udp buffer
#define UDP_START_BYTE_LEN 1
#define UDP_COMMAND_ID_LEN 1
#define UDP_DATA_LENGTH_LEN 2
#define UDP_CHECKSUM_LEN 4
//data locations
#define UDP_LEG_ID_LEN 1
#define UDP_JOINT_DEMAND_LEN 4
//minimum udp packet lenght
#define UDP_PACKET_MIN_LEN 8 //TODO: check all command ids and chane this later

//enum of command ids for a leg
typedef enum 
{
    legEStopCmd = 0,
    legJointDemandsCmd,
    legTelemetryCmd,
    legConfigCmd,
    legResetCmd,
    legMaxCmd
} legCommandIDType;


#endif // UDP_DEFS_H






