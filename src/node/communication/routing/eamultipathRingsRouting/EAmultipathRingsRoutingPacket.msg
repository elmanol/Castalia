//****************************************************************************
//*  Copyright: National ICT Australia,  2007 - 2011                         *
//*  Developed at the ATP lab, Networked Systems research theme              *
//*  Author(s): Athanassios Boulis, Yuriy Tselishchev                        *
//*  This file is distributed under the terms in the attached LICENSE file.  *
//*  If you do not find this file, copies can be found by writing to:        *
//*                                                                          *
//*      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
//*      Attention:  License Inquiry.                                        *
//*                                                                          *  
//****************************************************************************/

cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;

enum eamultipathRingsRoutingPacketDef {
	MPRINGS_DATA_PACKET = 1;
	MPRINGS_TOPOLOGY_SETUP_PACKET = 2;
	MPRINGS_ENERGY_PACKET= 3;
} 

packet EAmultipathRingsRoutingPacket extends RoutingPacket {
	int eamultipathRingsRoutingPacketKind enum (eamultipathRingsRoutingPacketDef);	// 1 byte
	int sinkID;			// 2 bytes
	int senderLevel;	// 1 byte
	float energyLevel;	//4 bytes
	float harvestingRate;	//4 bytes
	float kidsStatus;	//4 bytes
	int myX;
	int myY;
	//int sX;
	//int sY;
	//DATA packet overhead contains all fields, making its total size 13 bytes
	//SETUP packet does not contain sequence number field, making its size 12 bytes
}

