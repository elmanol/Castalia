cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;

enum MyAppRoutingPacketDef {
	MPRINGS_DATA_PACKET = 1;
	MPRINGS_TOPOLOGY_SETUP_PACKET = 2;
	DATA_PACKET = 3;
} 

packet MyAppRoutingPacket extends RoutingPacket {
	int MyAppRoutingPacketKind enum (MyAppRoutingPacketDef);	// 1 byte
	int sinkID;			// 2 bytes
	int senderLevel;	// 1 byte

	//DATA packet overhead contains all fields, making its total size 13 bytes
	//SETUP packet does not contain sequence number field, making its size 12 bytes
}

