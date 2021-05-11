#ifndef _TestmultiRingsApp_H_
#define _TestmultiRingsApp_H_

#include "VirtualApplication.h"
#include <map>

using namespace std;

enum TestmultiRingsAppTimers {
	SEND_DATA = 1,
};

class TestmultiRingsApp: public VirtualApplication {
 private:
	double packet_rate;
	double startupDelay;
	double getNeighboursDelay;
	double delayLimit;
	double sampleInterval;
	float packet_spacing;
	int dataSN;
	int currSampleSN;
	string recipientAddress;
	
	//variables below are used to determine the packet delivery rates.	
	int numNodes;

 protected:
	void startup();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	void handleNetworkControlMessage(cMessage *);
	void timerFiredCallback(int);
	// void handleSensorReading(SensorReadingMessage *);
	void finishSpecific();

 //public:
	//int getPacketsSent(int addr) { return packetsSent[addr]; }
	//int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	//int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _testMultiRingsApp_H_APPLICATIONMODULE_H_
