/*******************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2011                            *
 *  Developed at the ATP lab, Networked Systems research theme                 *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                           *
 *  This file is distributed under the terms in the attached LICENSE file.     *
 *  If you do not find this file, copies can be found by writing to:           *
 *                                                                             *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                *
 *      Attention:  License Inquiry.                                           *
 *                                                                             *
 *******************************************************************************/

#ifndef _EAmultipathRingsROUTING_H_
#define _EAmultipathRingsROUTING_H_

#include <map>
#include "VirtualRouting.h"
#include "EAmultipathRingsRoutingPacket_m.h"
#include "EAmultipathRingsRoutingControl_m.h"
#define DATA_PACKET_NAME "Data packet"
#define SETUP_PACKET_NAME "Setup packet"

#define NO_LEVEL  -110
#define NO_SINK   -120

using namespace std;

enum EAmultipathRingsRoutingTimers {
	TOPOLOGY_SETUP_TIMEOUT = 1,
	COLLECT_BATTERY = 2,
	ENERGY_MSG = 3,
	TOPOLOGY_MSG = 4
};

class EAmultipathRingsRouting: public VirtualRouting {
 private:
	int mpathRingsSetupFrameOverhead;	// in bytes
	double netSetupTimeout;
	double startupDelay;
	int collectBatterySN;
	double collectBatteryTimer;
	double sendEnergyTimer;
	double energyMetricPercentage;
	double h_energyMetricPercentage;
	double kidsMetricPercentage;
	double rssiMetricPercentage;
	int distanceThreshold;
	double energyThreshold;
	// EAmultipathRingsRouting-related member variables
	bool hasDied=false;
	bool emergency=false;
	int engyMgrCounter;
	int currentSequenceNumber;
	int currentSinkID;
	int currentLevel;
	int tmpSinkID;
	int tmpLevel;
	int rssiThreshold;
	int myX;
	int myY;
	int nX;
	int nY;
	bool isSink;		//is a .ned file parameter of the Application module
	bool isConnected;	//attached under a parent node
	bool isScheduledNetSetupTimeout;
	
	struct neighbour{
		float EnergyLevel;
		float HarvestingRate;
		float KidsStatus;
		int RingLevel;
		float Rssi;
		neighbour(){
			EnergyLevel = 0;
			HarvestingRate = 0;
			KidsStatus = 0;
			RingLevel = 0;
			Rssi = 0;
		}
	};

	map<string,neighbour> neighboursMap;


 protected:
	void startup();
	void fromApplicationLayer(cPacket *, const char *);
	void fromMacLayer(cPacket *, int, double, double);

	void sendTopologySetupPacket();
	void sendControlMessage(eamultipathRingsRoutingControlDef);
	void sendPacket();

	void timerFiredCallback(int);
	void processBufferedPacket();
	
	int findNextHop();
};

#endif				//EAmultipathRingsROUTINGMODULE
