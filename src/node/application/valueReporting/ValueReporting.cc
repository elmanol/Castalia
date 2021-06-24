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

#include "ValueReporting.h"

Define_Module(ValueReporting);

void ValueReporting::startup()
{
	maxSampleInterval = par("maxSampleInterval");
	minSampleInterval = par("minSampleInterval");
	firstSampleInterval = par("firstSampleInterval");
	metricsInterval = par("metricsInterval");
	currSentSampleSN = 0;
	packetsSentSum = 0;
	packetsReceivedSum =0;
	metricsSN=0;
	ssum=0;
	rsum=0;
	declareOutput("Packets sensed per node");
	int locX = mobilityModule->getLocation().x;
	int locY = mobilityModule->getLocation().y;
	trace() << locX<<", "<<locY;
	numNodes = getParentModule()->getParentModule()->par("numNodes");
	packetsSent.clear();
	packetsReceived.clear();
	bytesReceived.clear();
	packetLatency.clear();
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");
	declareOutput("Avg latency");
	declareOutput("Packets sent");
	declareOutput("Packets sent sum");
	declareOutput("Packets received");
	declareOutput("Packets Rate");
	declareOutput("Simulation duration");
	

	if (isSink) {
	  setTimer(METRICS, metricsInterval);
	}

}

void ValueReporting::timerFiredCallback(int index)
{
	trace() << "timer fired";

	switch (index) {
		case REQUEST_SAMPLE:{
			requestSensorReading();
			setTimer(REQUEST_SAMPLE, minSampleInterval);
			break;
		}
		case METRICS:{

			metricsSN++;
			setTimer(METRICS, metricsInterval);
			long bytesDelivered = 0;
			cTopology *topo;	// temp variable to access packets received by other nodes
			topo = new cTopology("topo");
			topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());
			float latency=0;
			float rate=0;
			for (int i = 0; i < numNodes; i++) {
				ValueReporting *appModule = dynamic_cast<ValueReporting*>(topo->getNode(i)->getModule()->getSubmodule("Application"));
				if (appModule) {
					int packetsSent = appModule->getPacketsSent(self);
					packetsSentSum += packetsSent;
					if (packetsSent > 0) { // this node sent us some packets
						latency += (float)packetLatency[i]/packetsSent;
						rate += (float)packetsReceived[i]/packetsSent;
						
					}

					bytesDelivered += appModule->getBytesReceived(self);
					
				}
				
			}		

			collectOutput("Avg latency", metricsSN, "total", latency/numNodes);
			collectOutput("Packets reception rate", metricsSN, "total", rate/numNodes);
			collectOutput("Packets loss rate", metricsSN, "total", 1-rate/numNodes);
			if (packetsSentSum>0){
			  collectOutput("Packets Rate", metricsSN, "total", (float)(packetsReceivedSum-rsum)/(packetsSentSum - ssum));
			}
			collectOutput("Packets sent sum", metricsSN, "total", (packetsSentSum));
			collectOutput("Packets sent", metricsSN, "total", (packetsSentSum-ssum));
			collectOutput("Packets received", metricsSN, "total", (packetsReceivedSum-rsum));
			
			rsum = packetsReceivedSum;
			ssum = packetsSentSum;
			
			delete(topo);
			
			break;
		}
	}
}

void ValueReporting::fromNetworkLayer(ApplicationPacket * genericPacket,
		 const char *source, double rssi, double lqi)
{
	int sourceId = atoi(source);
	ValueReportingDataPacket *rcvPacket = check_and_cast<ValueReportingDataPacket*>(genericPacket);
	ValueReportData theData = rcvPacket->getExtraData();

	if (isSink){
		trace() << "Sink received from: " << theData.nodeID << " \tvalue=" << rcvPacket->getData();
		simtime_t timeDifference = simTime() - rcvPacket->getCreationTime();
		packetLatency[sourceId] += timeDifference.dbl();
 		trace() << "packetLatency[sourceId]1: " << packetLatency[sourceId];
 		packetsReceived[sourceId]++;
		packetsReceivedSum++;
	}

}

void ValueReporting::handleSensorReading(SensorReadingMessage * rcvReading)
{
	// int sensIndex =  rcvReading->getSensorIndex();
	// string sensType(rcvReading->getSensorType());
	collectOutput("Packets sensed per node");
	double sensValue = rcvReading->getSensedValue();

	// schedule the TX of the value
	trace() << "Sensed = " << sensValue;

	ValueReportData tmpData;
	tmpData.nodeID = (unsigned short)self;
	tmpData.locX = mobilityModule->getLocation().x;
	tmpData.locY = mobilityModule->getLocation().y;

	ValueReportingDataPacket *packet2Net =
	    new ValueReportingDataPacket("Value reporting pck", APPLICATION_PACKET);
	packet2Net->setExtraData(tmpData);
	packet2Net->setData(sensValue);
	packet2Net->setSequenceNumber(currSentSampleSN);
	currSentSampleSN++;

	toNetworkLayer(packet2Net, SINK_NETWORK_ADDRESS);
	packetsSent[atoi(SINK_NETWORK_ADDRESS)]++;

    trace() << "Sent data packet to network layer";
}

void ValueReporting::handleNetworkControlMessage(cMessage * msg){

    if (isSink) {
        trace() << "I am the sink. I don't send packets";

    } else {
        setTimer(REQUEST_SAMPLE, firstSampleInterval);
    }

}

void ValueReporting::finishSpecific() {
	

	if (isSink) {

		collectOutput("Simulation duration","",simTime().dbl());
		// if (packet_rate > 0 && bytesDelivered > 0) {
		// 	double energy = (enMgrModule->getTotEnergySupplied() * 1000000000)/(bytesDelivered * 8);	//in nanojoules/bit
		// 	declareOutput("Energy nJ/bit");
		// 	collectOutput("Energy nJ/bit","",energy);
		// }
	}
}
