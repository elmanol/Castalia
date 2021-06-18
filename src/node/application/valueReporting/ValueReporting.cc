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
	maxSampleInterval = ((double)par("maxSampleInterval")) / 1000.0;
	minSampleInterval = ((double)par("minSampleInterval")) / 1000.0;
	firstSampleInterval = ((double)par("firstSampleInterval")) / 1000.0;
	currSentSampleSN = 0;
	declareOutput("Packets sensed per node");
	int locX = mobilityModule->getLocation().x;
	int locY = mobilityModule->getLocation().y;
	trace() << "X: "<<locX;
	trace() << "Y: "<<locY;
	numNodes = getParentModule()->getParentModule()->par("numNodes");
	packetsSent.clear();
	packetsReceived.clear();
	bytesReceived.clear();
	packetLatency.clear();


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
	
	declareOutput("Packets reception rate");
	declareOutput("Packets loss rate");
	declareOutput("Avg latency");

	if (isSink) {

		cTopology *topo;	// temp variable to access packets received by other nodes
		topo = new cTopology("topo");
		topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

		long bytesDelivered = 0;
		for (int i = 0; i < numNodes; i++) {
			ValueReporting *appModule = dynamic_cast<ValueReporting*>
				(topo->getNode(i)->getModule()->getSubmodule("Application"));
			if (appModule) {
				int packetsSent = appModule->getPacketsSent(self);
				if (packetsSent > 0) { // this node sent us some packets
					double latency = packetLatency[i]/packetsSent;
					float rate = (float)packetsReceived[i]/packetsSent;
					collectOutput("Avg latency", i, "total", latency);
					collectOutput("Packets reception rate", i, "total", rate);
					collectOutput("Packets loss rate", i, "total", 1-rate);
				}

				bytesDelivered += appModule->getBytesReceived(self);
			}
		}
		delete(topo);

		// if (packet_rate > 0 && bytesDelivered > 0) {
		// 	double energy = (enMgrModule->getTotEnergySupplied() * 1000000000)/(bytesDelivered * 8);	//in nanojoules/bit
		// 	declareOutput("Energy nJ/bit");
		// 	collectOutput("Energy nJ/bit","",energy);
		// }
	}
}