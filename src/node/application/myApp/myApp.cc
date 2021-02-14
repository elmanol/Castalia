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

/**********************************************************************************************************/
/**********************************************************************************************************/

void myApp::startup()
{
	packet_rate = par("packet_rate"); // packets per second
    sampleInterval = (double)par("sampleInterval") / 1000;
	recipientAddress = par("recipientAddress").stringValue(); // Destination for packets received in this node. - Static routing
	recipientId = atoi(recipientAddress.c_str());
	startupDelay = par("startupDelay");// time till the node starts
	delayLimit = par("delayLimit"); // application delay limit (0 - no limit)
	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1; // time between two packet transmissions

	dataSN = 0;
	currSampleSN = 1;
	pushNeighSN = 0;

	
	numNodes = getParentModule()->getParentModule()->par("numNodes"); //number of nodes in the network
	packetsSent.clear();
	packetsReceived.clear();
	bytesReceived.clear();
	peers.clear();

	setTimer(GET_NEIGHBOURS, startupDelay);

	if (packet_spacing > 0){ // if this node is supposed to send messages
	    if (isSink) {
	        trace() << "I am the sink. I don't send packets";

	    } else {
	        setTimer(REQUEST_SAMPLE, sampleInterval);
	    }
	}else{
		
		trace() << "Not sending packets";
	}

	declareOutput("Packets received per node");
}

/**********************************************************************************************************/
/**********************************************************************************************************/

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

    }else if (packetName.compare(GET_NEIGHBOURS_NAME) == 0){
        ApplicationPacket *neighPkt = createGenericDataPacket(PUSH_NEIGHBOUR, pushNeighSN++);
        neighPkt->setName(PUSH_NEIGHBOUR_NAME);

        toNetworkLayer(neighPkt, sourceId);
        
    }else if (packetName.compare(PUSH_NEIGHBOUR_NAME) == 0){
        
        peers.push_back(sourceId);
        
    }
        
}

/**********************************************************************************************************/
/**********************************************************************************************************/

void myApp::timerFiredCallback(int index)
{
	switch (index) {

	    case REQUEST_SAMPLE:{
	        setTimer(REQUEST_SAMPLE, sampleInterval);
	        requestSensorReading();
	        break;
	    }

		case GET_NEIGHBOURS:{
			ApplicationPacket *newPkt = createGenericDataPacket(GET_NEIGHBOURS, dataSN++);
			newPkt->setName(GET_NEIGHBOURS_NAME);
            toNetworkLayer(newPkt, BROADCAST_NETWORK_ADDRESS);
			break;
		}
	}
}

/**********************************************************************************************************/
/**********************************************************************************************************/

void myApp::handleSensorReading(SensorReadingMessage * sensorMsg)
{
	string sensType(sensorMsg->getSensorType());
	double sensValue = sensorMsg->getSensedValue();

	if (isSink) {
		trace() << "Sink received SENSOR_READING (while it shouldnt) "
		    << sensValue << " (int)" << (int)sensValue;
		return;
	}

	trace() << "Sending report packet, sequence number " << currSampleSN;
	ApplicationPacket *newPkt = createGenericDataPacket((double)self, currSampleSN++);
	newPkt->setName(SEND_DATA_NAME);
	toNetworkLayer(newPkt, recipientAddress.c_str());
}

/**********************************************************************************************************/
/**********************************************************************************************************/

void myApp::finishSpecific()
{
	trace() << "Simulation ended";
}

/**********************************************************************************************************/
/**********************************************************************************************************/
