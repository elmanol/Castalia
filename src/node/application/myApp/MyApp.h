#ifndef _MyApp_H_
#define _MyApp_H_

#include "VirtualApplication.h"
#include <map>

#define SEND_DATA_NAME "myApp data packet"
#define GIMMIE_NEIGHBOURS_NAME "myApp getNeighbours packet"
#define PUSH_NEIGHBOUR_NAME "myApp pushNeighbour packet"


using namespace std;

enum myAppTimers {
	REQUEST_SAMPLE = 1,
	GET_NEIGHBOURS = 2,
};

class MyApp: public VirtualApplication {
 private:
	double packet_rate;
	double startupDelay;
	double getNeighboursDelay;
	double delayLimit;
	double sampleInterval;
	float packet_spacing;
	int dataSN;
	int pushNeighSN;
	int recipientId;
	int currSampleSN;
	string recipientAddress;
	
	//variables below are used to determine the packet delivery rates.	
	int numNodes;
	map<long,int> packetsReceived;
	map<long,int> bytesReceived;
	map<long,int> packetsSent;

	vector<int> peers;

 protected:
	void startup();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	//void handleRadioControlMessage(RadioControlMessage *);
	void timerFiredCallback(int);
	void handleSensorReading(SensorReadingMessage *);
	void finishSpecific();

 //public:
	//int getPacketsSent(int addr) { return packetsSent[addr]; }
	//int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	//int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _MyApp_H_APPLICATIONMODULE_H_
