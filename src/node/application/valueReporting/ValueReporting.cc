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

      if (!hasDied){  
	maxSampleInterval = par("maxSampleInterval");
	sampleInterval = par("sampleInterval");
	firstSampleInterval = par("firstSampleInterval");
	metricsInterval = par("metricsInterval");
	countFinal = par("countFinal");
	randomBackoffIntervalFraction = genk_dblrand(0);
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
	declareOutput("Packets Reception Rate");
	declareOutput("Packets Loss Rate");
	declareOutput("Avg Latency");
	declareOutput("Packets Sent");
	declareOutput("Packets Received");
	//declareOutput("Packets ssum");
	//declareOutput("Packets packetsSentSum");
	declareOutput("Simulation duration");
	

	if (isSink) {
	  setTimer(METRICS, metricsInterval);
	}
     }
     hasDied = true;
}

void ValueReporting::timerFiredCallback(int index)
{
	switch (index) {
		case REQUEST_SAMPLE:{
			requestSensorReading();
			setTimer(REQUEST_SAMPLE, sampleInterval);
			break;
		}
		case METRICS:{
			trace() << "test metrics";
			metricsSN++;
			setTimer(METRICS, metricsInterval);
			long bytesDelivered = 0;
			cTopology *topo;	// temp variable to access packets received by other nodes
			topo = new cTopology("topo");
			topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());
			float total_latency=0;
			float total_received=0;
			packetsSentSum=0;
			for (int i = 0; i < numNodes; i++) {
				ValueReporting *appModule = dynamic_cast<ValueReporting*>(topo->getNode(i)->getModule()->getSubmodule("Application"));
				if (appModule) {
					int packetsSent = appModule->getPacketsSent(self);
					packetsSentSum += packetsSent;
					if (packetsSent > 0) { // this node sent us some packets
						total_latency += (float)packetLatency[i];
						total_received += (float)packetsReceived[i];
						
					}

					bytesDelivered += appModule->getBytesReceived(self);
					
				}
				
			}		

			collectOutput("Avg Latency", metricsSN, "total", total_latency/packetsSentSum);
			//collectOutput("Packets Rate", metricsSN, "total", total_received/packetsSentSum);

			float prr = (float)(packetsReceivedSum-rsum)/(packetsSentSum - ssum);
			float plr = (float)(1-prr);

			if (packetsSentSum>0){
			  collectOutput("Packets Reception Rate", metricsSN, "total", prr);
			  collectOutput("Packets Loss Rate", metricsSN, "total", plr );
			
			}else{
			  collectOutput("Packets Reception Rate", metricsSN, "total", 0);
                         collectOutput("Packets Loss Rate", metricsSN, "total", 0);
			}
			
			
			//collectOutput("Packets ssum", metricsSN, "total", ssum);
			collectOutput("Packets Sent", metricsSN, "total", (packetsSentSum-ssum));
			//collectOutput("Packets packetsSentSum", metricsSN, "total", packetsSentSum);
			collectOutput("Packets Received", metricsSN, "total", (packetsReceivedSum-rsum));
			
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

	//ValueReportData tmpData;
	//tmpData.nodeID = (unsigned short)self;
	//tmpData.locX = mobilityModule->getLocation().x;
	//tmpData.locY = mobilityModule->getLocation().y;

	ValueReportingDataPacket *packet2Net =
	    new ValueReportingDataPacket("Value reporting pck", APPLICATION_PACKET);
	//packet2Net->setExtraData(tmpData);
	packet2Net->setData(sensValue);
	packet2Net->setSequenceNumber(currSentSampleSN);
	currSentSampleSN++;

	toNetworkLayer(packet2Net, SINK_NETWORK_ADDRESS);
	packetsSent[atoi(SINK_NETWORK_ADDRESS)]++;
	declareOutput("Simulation duration");
	collectOutput("Simulation duration","",simTime().dbl());

    trace() << "Sent data packet to network layer";
}

void ValueReporting::handleNetworkControlMessage(cMessage * msg){

    if (isSink) {
        trace() << "I am the sink. I don't send packets";

    } else {
    	//if (self==(unsigned short)34){
        setTimer(REQUEST_SAMPLE, firstSampleInterval);
        //}
    }

}

void ValueReporting::finishSpecific() {
	

	if (isSink&&countFinal) {

		// if (packet_rate > 0 && bytesDelivered > 0) {
		// 	double energy = (enMgrModule->getTotEnergySupplied() * 1000000000)/(bytesDelivered * 8);	//in nanojoules/bit
		// 	declareOutput("Energy nJ/bit");
		// 	collectOutput("Energy nJ/bit","",energy);
		// }
		metricsSN++;
		long bytesDelivered = 0;
		cTopology *topo;	// temp variable to access packets received by other nodes
		topo = new cTopology("topo");
		topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());
		float total_latency=0;
		float total_received=0;
		packetsSentSum=0;
		for (int i = 0; i < numNodes; i++) {
			ValueReporting *appModule = dynamic_cast<ValueReporting*>(topo->getNode(i)->getModule()->getSubmodule("Application"));
			if (appModule) {
				int packetsSent = appModule->getPacketsSent(self);
				packetsSentSum += packetsSent;
				if (packetsSent > 0) { // this node sent us some packets
					total_latency += (float)packetLatency[i];
					total_received += (float)packetsReceived[i];
					
				}

				bytesDelivered += appModule->getBytesReceived(self);
				
			}
			
		}		

		collectOutput("Avg Latency", metricsSN, "total", total_latency/packetsSentSum);
		//collectOutput("Packets Rate", metricsSN, "total", total_received/packetsSentSum);
		//collectOutput("Packets Loss Rate", metricsSN, "total", 1-total_received/packetsSentSum);
		float prr = (float)(packetsReceivedSum-rsum)/(packetsSentSum - ssum);
		float plr = (float)(1-prr);
		if (packetsSentSum>0){
		  collectOutput("Packets Reception Rate", metricsSN, "total", prr);
		  collectOutput("Packets Loss Rate", metricsSN, "total", plr);
		}else{
		  collectOutput("Packets Reception Rate", metricsSN, "total", 0);
		  collectOutput("Packets Loss Rate", metricsSN, "total", 0);
		}
		
		//collectOutput("Packets ssum", metricsSN, "total", ssum);
		//collectOutput("Packets packetsSentSum", metricsSN, "total", packetsSentSum);
		collectOutput("Packets Sent", metricsSN, "total", (packetsSentSum-ssum));
		collectOutput("Packets Received", metricsSN, "total", (packetsReceivedSum-rsum));
		

		delete(topo);
	}
}
