/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2011                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Dimosthenis Pediaditakis, Yuriy Tselishchev                  *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *
 ****************************************************************************/

#ifndef _VALUEREPORTING_H_
#define _VALUEREPORTING_H_

#include "VirtualApplication.h"
#include "ValueReportingPacket_m.h"

using namespace std;

enum ValueReportingTimers {
	REQUEST_SAMPLE = 1,
	METRICS = 2,
};

class ValueReporting: public VirtualApplication {
 private:
	double maxSampleInterval;
	double sampleInterval;
	double firstSampleInterval;
	double metricsInterval;
	int metricsSN;
	int routingLevel;
	double lastSensedValue;
	int currSentSampleSN;

	double randomBackoffIntervalFraction;
	bool sentOnce;
	bool hasDied=false;
	bool countFinal;		//is a .ned file parameter of the Application module
	//variables below are used to determine the packet delivery rates.	
	int numNodes;
	//simtime_t packetLatency;
	//simtime_t packetLatencySum;
	int packetsReceivedSum;
	int packetsSentSum;
	int ssum;
	int rsum;
	map<long, double> packetLatency;
	map<long,int> packetsReceived;
	map<long,int> bytesReceived;
	map<long,int> packetsSent;

 protected:
	void startup();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	void handleSensorReading(SensorReadingMessage *);
	void timerFiredCallback(int);
	void handleNetworkControlMessage(cMessage *);
	void finishSpecific();

 public:
	int getPacketsSent(int addr) { return packetsSent[addr]; }
	int getPacketsReceived(int addr) { return packetsReceived[addr]; }
	int getBytesReceived(int addr) { return bytesReceived[addr]; }

};

#endif				// _VALUEREPORTING_APPLICATIONMODULE_H_
