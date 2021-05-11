#include "MultiRingsApp.h"

Define_Module(MultiRingsApp);

/**********************************************************************************************************/
/**********************************************************************************************************/

void MultiRingsApp::startup()
{
	packet_rate = par("packet_rate"); // packets per second 
    sampleInterval = (double)par("sampleInterval");// / 1000; //interval between taken samples
	recipientAddress = par("recipientAddress").stringValue(); // Destination for packets received in this node. - Static routing
	startupDelay = par("startupDelay");// time till the node starts
	delayLimit = par("delayLimit"); // application delay limit (0 - no limit)
	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1; // time between two packet transmissions

	dataSN = 0;
	currSampleSN = 0;
	
	//numNodes = getParentModule()->getParentModule()->par("numNodes"); //number of nodes in the network
	declareOutput("Packets sensed per node");
}

/**********************************************************************************************************/
/**********************************************************************************************************/

// this function is used for messages coming from other nodes through the routing/network layer
void MultiRingsApp::fromNetworkLayer(ApplicationPacket * rcvPacket,
		const char *source, double rssi, double lqi)  // rssi - Received signal strength indication
                                                      // lqi - Locational Quality Indicator
{
	double theData = rcvPacket->getData();

	int sequenceNumber = rcvPacket->getSequenceNumber(); //get the seq number of the received packet

	int sourceId = atoi(source); //get the id of the source node for this packet

	trace() << "Got a data packet from " << sourceId << ", with data: " << theData << " and seq num: " << sequenceNumber;

}


/**********************************************************************************************************/
/**********************************************************************************************************/

void MultiRingsApp::timerFiredCallback(int index)
{
	// trace() << "Timer fired";
	switch (index) {
	    case REQUEST_SAMPLE:{

	        setTimer(REQUEST_SAMPLE, sampleInterval);
	        requestSensorReading();
	        
	        break;
	    }
	}
}

/**********************************************************************************************************/
/**********************************************************************************************************/

void MultiRingsApp::handleSensorReading(SensorReadingMessage * sensorMsg)
{
	// trace() << "Sensor measured: "<< recipientAddress.c_str();
	// string sensType(sensorMsg->getSensorType());
	// double sensValue = sensorMsg->getSensedValue();

	double sensValue = sensorMsg->getSensedValue();

	// schedule the TX of the value
	trace() << "Sensed = " << sensValue;

	collectOutput("Packets sensed per node");

	if (isSink) {
		trace() << "Sink received SENSOR_READING (while it shouldnt) "
		    << sensValue << " (int)" << (int)sensValue;
		return;
	}

	// trace() << "Sending packet, with conent: " << sensValue;
	// ApplicationPacket *newPkt = createGenericDataPacket(sensValue, currSampleSN++,1024);
	// newPkt->setName(DATA_PACKET_NAME);
	// toNetworkLayer(newPkt, BROADCAST_NETWORK_ADDRESS);




	MultiRingData tmpData;
	tmpData.nodeID = (unsigned short)self;
	tmpData.locX = mobilityModule->getLocation().x;
	tmpData.locY = mobilityModule->getLocation().y;

	MultiRingDataPacket *packet2Net =
	    new MultiRingDataPacket("VMultiRingDataPacket pck", APPLICATION_PACKET);
	packet2Net->setExtraData(tmpData);
	packet2Net->setData(sensValue);
	packet2Net->setSequenceNumber(currSampleSN);
	currSampleSN++;

	toNetworkLayer(packet2Net, SINK_NETWORK_ADDRESS);
}

/**********************************************************************************************************/
/**********************************************************************************************************/

void MultiRingsApp::handleNetworkControlMessage(cMessage * msg)
{			
  //   switch(msg->getKind()) {
    
		// case MPRINGS_TREE_LEVEL_UPDATED: {
		    // this message notifies the application of routing state (level)
		    // for certain routing protocols.
		    // Network_ControlMessage *levelMsg = check_and_cast<Network_ControlMessage *>(msg);
		    // routingLevel = levelMsg->getLevel();

		    // trace() << "Routing level " << routingLevel;

    if (packet_spacing > 0){ // if this node is supposed to send messages
	    if (isSink) {
	        trace() << "I am the sink. I don't send packets";

	    } else {
	        setTimer(REQUEST_SAMPLE, sampleInterval);
	    }
	}else{
		
		trace() << "Not sending packets";
	}
		    // break;
		// }

		// case MPRINGS_CONNECTED_TO_TREE: {
		    // Network_ControlMessage *connectedMsg = check_and_cast<Network_ControlMessage *>(msg);

		    // int treeLevel = connectedMsg->getLevel();
		    // string parents;
		    // parents.assign(connectedMsg->getParents());

		    // trace() << "Tree level " << treeLevel;

		    // routingLevel = treeLevel;

		//     if (packet_spacing > 0){ // if this node is supposed to send messages
		// 	    if (isSink) {
		// 	        trace() << "I am the sink. I don't send packets";

		// 	    } else {
		// 	        setTimer(REQUEST_SAMPLE, startupDelay);
		// 	    }
		// 	}else{
				
		// 		trace() << "Not sending packets";
		// 	}

		//     break;
		// }
    // }

}

/**********************************************************************************************************/
/**********************************************************************************************************/

void MultiRingsApp::finishSpecific()
{
	trace() << "Simulation ended";
}

/**********************************************************************************************************/
/**********************************************************************************************************/
