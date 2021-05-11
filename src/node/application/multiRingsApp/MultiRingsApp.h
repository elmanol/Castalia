#ifndef _MultiRingsApp_H_
#define _MultiRingsApp_H_

#include "VirtualApplication.h"
#include <map>
#include "MultiRingDataPacket_m.h"
#define DATA_PACKET_NAME "Data packet"
#define SETUP_PACKET_NAME "Setup packet"

using namespace std;

enum MultiRingsAppTimers {
	REQUEST_SAMPLE = 1,
};

class MultiRingsApp: public VirtualApplication {
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
	void handleSensorReading(SensorReadingMessage *);
	void finishSpecific();

 //public:
	//int getPacketsSent(int addr) { return packetsSent[addr]; }
	//int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	//int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _MultiRingsApp_H_APPLICATIONMODULE_H_
