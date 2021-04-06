#ifndef _MYAPPROUTING_H_
#define _MYAPPROUTING_H_

#include <map>
#include "VirtualRouting.h"
#include "MyAppRoutingPacket_m.h"

#define NO_LEVEL  -110
#define NO_SINK   -120
#define SEND_DATA_NAME "MyAppRouting data packet"
#define GET_NEIGHBOURS_NAME "myApp getNeighbours packet"
#define PUSH_NEIGHBOUR_NAME "myApp pushNeighbour packet"


using namespace std;

enum MyAppRoutingTimers {
	TOPOLOGY_SETUP_TIMEOUT = 1,
	GIMMIE_NEIGHBOURS_TIMER = 2,
};

class MyAppRouting: public VirtualRouting {
 private:

	// MyAppRouting - related member variables
	double startupDelay;
	int currentSequenceNumber;
	int currentSinkID;
	int currentLevel;
	int tmpSinkID;
	int tmpLevel;
	bool isSink;		//is a .ned file parameter of the Application module
	bool isConnected;	//attached under a parent node
	bool isScheduledNetSetupTimeout;

 protected:
	void startup();
	void fromApplicationLayer(cPacket *, const char *);
	void fromMacLayer(cPacket *, int, double, double);

	void timerFiredCallback(int);
	void processBufferedPacket();
};

#endif				//MYAPPROUTINGMODULE
