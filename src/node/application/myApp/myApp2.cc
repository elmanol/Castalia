/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2011                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                        *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *
 ****************************************************************************/

#include "myApp.h"

Define_Module(myApp);

void myApp::startup()
{
    currSampleSN = 1;
    currentSampleAccumulated = 0;
    getNeighSN = 0;
    pushNeighSN = 0;
	packet_rate = par("packet_rate"); // packets per second
    sampleInterval = (double)par("sampleInterval") / 1000;
	recipientAddress = par("reportDestination").stringValue(); // Destination for packets received in this node. - Static routing
	recipientId = atoi(recipientAddress.c_str());
	startupDelay = par("startupDelay");// time till the node starts
	delayLimit = par("delayLimit"); // application delay limit (0 - no limit)
	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1; // time between two packet transmissions
	dataSN = 0;
	
	numNodes = getParentModule()->getParentModule()->par("numNodes"); //number of nodes in the network
	packetsSent.clear();
	packetsReceived.clear();
	bytesReceived.clear();

	setTimer(GET_NEIGHBOURS, startupDelay);

	if (packet_spacing > 0) // if this node is supposed to send messages
	    if (isSink) {
	        trace() << "I am the sink. I don't send packets";

	    } else {
	        setTimer(REQUEST_SAMPLE, sampleInterval);
	    }
	else
		trace() << "Not sending packets";

    //setTimer(SEND_DATA_PACKET, packet_spacing + startupDelay); //start timer to send message after the node starts and the packet spacing time has passed

	declareOutput("Packets received per node");
}

// this function is used for messages coming from other nodes through the routing/network layer
void myApp::fromNetworkLayer(ApplicationPacket * rcvPacket,
		const char *source, double rssi, double lqi)  // rssi - Received signal strength indication
                                                      // lqi - Locational Quality Indicator
{
	int sequenceNumber = rcvPacket->getSequenceNumber(); //get the seq number of the received packet

	int sourceId = atoi(source); //get the id of the source node for this packet
	
    string packetName(rcvPacket->getName());

    if (packetName.compare(SEND_PACKET_NAME) == 0) {
        
        // This node is the final recipient for the packet
        if (recipientAddress.compare(SELF_NETWORK_ADDRESS) == 0) { //if the message's destination was this node

            if (delayLimit == 0 || (simTime() - rcvPacket->getCreationTime()) <= delayLimit) { 
                trace() << "Received packet #" << sequenceNumber << " from node " << source;
                collectOutput("Packets received per node", sourceId);
                packetsReceived[sourceId]++;
                bytesReceived[sourceId] += rcvPacket->getByteLength();

            } else {

                trace() << "Packet #" << sequenceNumber << " from node " << source <<
                    " exceeded delay limit of " << delayLimit << "s";
            }
        // if the destination is another node, the packet has to be forwarded to the next hop recipient
        } else {

            ApplicationPacket* fwdPacket = rcvPacket->dup();
            // Reset the size of the packet, otherwise the app overhead will keep adding on
            fwdPacket->setByteLength(0);
            toNetworkLayer(fwdPacket, recipientAddress.c_str()); // send the packet to the network layer for forwarding
        }

    }else if (packetName.compare(PULL_NEIGHBOUR_NAME) == 0){
        ApplicationPacket *neighPkt = createGenericDataPacket(PUSH_NEIGHBOUR, pushNeighSN++);
        neighPkt->setName(PUSH_NEIGHBOUR_NAME);

        toNetworkLayer(neighPkt, sourceId);
        
    }else if (packetName.compare(PUSH_NEIGHBOUR_NAME) == 0){
        
        peers.push_back(sourceId);
        
    }
        
}

void myApp::timerFiredCallback(int index)
{
	switch (index) {
	
        case REQUEST_SAMPLE:{
            setTimer(REQUEST_SAMPLE, sampleInterval);
            requestSensorReading();
            break;
        }
	    //new sensor value has to be sent, timer fired
//		case SEND_DATA_PACKET:{
//			trace() << "Sending packet #" << dataSN;
//			toNetworkLayer(createGenericDataPacket(SEND_DATA, dataSN), recipientAddress.c_str());
//			packetsSent[recipientId]++;
//			dataSN++;
//			setTimer(SEND_PACKET, packet_spacing); //in packet_spacing time send another packet
//			break;
//		}
		case GET_NEIGHBOURS:{
            ApplicationPacket *neighPkt = createGenericDataPacket(PULL_NEIGHBOUR, getNeighSN++);
            neighPkt->setName(PULL_NEIGHBOUR_NAME);
            toNetworkLayer(neighPkt, BROADCAST_NETWORK_ADDRESS);
			break;
		}
	}
}

void myApp::handleSensorReading(SensorReadingMessage * sensorMsg)
{
    string sensType(sensorMsg->getSensorType());
    double sensValue = sensorMsg->getSensedValue();

    if (isSink) {
        trace() << "Sink recieved SENSOR_READING (while it shouldnt) "
            << sensValue << " (int)" << (int)sensValue;
        return;
    }
    
    currentSampleAccumulated += sampleSize;
    
    trace() << "Sending report packet, sequence number " << currSampleSN;
    ApplicationPacket *newPkt = createGenericDataPacket((double)self, currSampleSN, currentSampleAccumulated);
    newPkt->setName(SEND_PACKET_NAME);
    toNetworkLayer(newPkt, recipientAddress.c_str());
    currentSampleAccumulated = 0;
    currSampleSN++;
}

void myApp::finishSpecific()
{
    if (isSink) {
        declareOutput("Report reception");
        for (int i = 0; i < (int)report_info_table.size(); i++) {
            collectOutput("Report reception", report_info_table[i].source,
                    "Success", report_info_table[i].parts.size());
            collectOutput("Report reception", report_info_table[i].source,
                    "Fail", report_info_table[i].seq - report_info_table[i].parts.size());
        }
    } else {
        declareOutput("Reprogram reception");
        for (int i = 0; i < (int)version_info_table.size(); i++) {
            collectOutput("Reprogram reception", "Success",
                      version_info_table[i].parts.size());
            collectOutput("Reprogram reception", "Fail",
                      version_info_table[i].seq - version_info_table[i].parts.size());
        }
    }
}
