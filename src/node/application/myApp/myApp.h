/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                        *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *
 ****************************************************************************/

#ifndef _MYAPP_H_
#define _MYAPP_H_

#include "VirtualApplication.h"
#include <map>

using namespace std;

enum MyAppTimers {
	REQUEST_SAMPLE = 1,
	SEND_PACKET = 2,
};

class MyApp: public VirtualApplication {
 private:
	double packet_rate;
	double startupDelay;
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
	void handleRadioControlMessage(RadioControlMessage *);
	void timerFiredCallback(int);
	void handleSensorReading(SensorReadingMessage *);
	void finishSpecific();

 public:
	int getPacketsSent(int addr) { return packetsSent[addr]; }
	int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	int getBytesReceived(int addr) { return bytesReceived[addr]; }
	
};

#endif				// _MYAPP_H_APPLICATIONMODULE_H_
