#include "MyApp.h"

Define_Module(MyApp);

/**********************************************************************************************************/
/**********************************************************************************************************/

void MyApp::startup()
{
	packet_rate = par("packet_rate"); // packets per second 
    sampleInterval = (double)par("sampleInterval") / 1000; //interval between taken samples
	recipientAddress = par("recipientAddress").stringValue(); // Destination for packets received in this node. - Static routing
	recipientId = atoi(recipientAddress.c_str());
	startupDelay = par("startupDelay");// time till the node starts
	getNeighboursDelay = par("getNeighboursDelay");// time till the node gets its neighbours info
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

	/* At startup the node starts a timer, which when fired sends a GET_NEIGHBOURS message to its neighbours 
	to its neighbours to get to know its neighbours. After it's done it starts getting samples*/

	setTimer(GET_NEIGHBOURS, startupDelay);

	if (packet_spacing > 0){ // if this node is supposed to send messages
	    if (isSink) {
	        trace() << "I am the sink. I don't send packets";

	    } else {
	        setTimer(REQUEST_SAMPLE, startupDelay + getNeighboursDelay);
	    }
	}else{
		
		trace() << "Not sending packets";
	}

	declareOutput("Packets received per node");
}

/**********************************************************************************************************/
/**********************************************************************************************************/

// this function is used for messages coming from other nodes through the routing/network layer
void MyApp::fromNetworkLayer(ApplicationPacket * rcvPacket,
		const char *source, double rssi, double lqi)  // rssi - Received signal strength indication
                                                      // lqi - Locational Quality Indicator
{
	int sequenceNumber = rcvPacket->getSequenceNumber(); //get the seq number of the received packet

	int sourceId = atoi(source); //get the id of the source node for this packet
	
    string packetName(rcvPacket->getName());

    if (packetName.compare(SEND_DATA_NAME) == 0) {
        
        // This node is the final recipient for the packet
        if (recipientAddress.compare(SELF_NETWORK_ADDRESS) == 0) { //if the message's destination was this node

            if (delayLimit == 0 || (simTime() - rcvPacket->getCreationTime()) <= delayLimit) { //if time limit is not exceeded
                trace() << "Received packet #" << sequenceNumber << " from node " << source;
                collectOutput("Packets received per node", sourceId);
                packetsReceived[sourceId]++;
                bytesReceived[sourceId] += rcvPacket->getByteLength();

            } else {

                trace() << "Packet #" << sequenceNumber << " from node " << source << //if time limit is exceeded
                    " exceeded delay limit of " << delayLimit << "s";
            }
        // if the destination is another node, the packet has to be forwarded to the next hop recipient
        } else {

            ApplicationPacket* fwdPacket = rcvPacket->dup();
            // Reset the size of the packet, otherwise the app overhead will keep adding on
            fwdPacket->setByteLength(0);
            toNetworkLayer(fwdPacket, recipientAddress.c_str()); // send the packet to the network layer for forwarding
        }

    }else if (packetName.compare(GIMMIE_NEIGHBOURS_NAME) == 0){
        ApplicationPacket *neighPkt = createGenericDataPacket((double)self, pushNeighSN++);
        neighPkt->setName(PUSH_NEIGHBOUR_NAME);

        toNetworkLayer(neighPkt, source);
        
    }else if (packetName.compare(PUSH_NEIGHBOUR_NAME) == 0){
        
        peers.push_back(sourceId);
        trace() << "Pushed to peers";
        
    }
        
}


/**********************************************************************************************************/
/**********************************************************************************************************/

void MyApp::timerFiredCallback(int index)
{
	switch (index) {

	    case REQUEST_SAMPLE:{
	        setTimer(REQUEST_SAMPLE, sampleInterval);
	        requestSensorReading();
	        break;
	    }

		case GET_NEIGHBOURS:{
			ApplicationPacket *newPkt = createGenericDataPacket((double)self, dataSN++);
			newPkt->setName(GIMMIE_NEIGHBOURS_NAME);
            toNetworkLayer(newPkt, BROADCAST_NETWORK_ADDRESS);
			break;
		}
	}
}

/**********************************************************************************************************/
/**********************************************************************************************************/

void MyApp::handleSensorReading(SensorReadingMessage * sensorMsg)
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

void MyApp::finishSpecific()
{
	trace() << "Simulation ended";
}

/**********************************************************************************************************/
/**********************************************************************************************************/
