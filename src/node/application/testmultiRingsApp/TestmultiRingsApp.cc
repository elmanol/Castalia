#include "TestmultiRingsApp.h"

Define_Module(TestmultiRingsApp);

/**********************************************************************************************************/
/**********************************************************************************************************/

void TestmultiRingsApp::startup()
{
	packet_rate = par("packet_rate"); // packets per second 
    sampleInterval = (double)par("sampleInterval");// / 1000; //interval between taken samples
	recipientAddress = par("recipientAddress").stringValue(); // Destination for packets received in this node. - Static routing
	startupDelay = par("startupDelay");// time till the node starts
	delayLimit = par("delayLimit"); // application delay limit (0 - no limit)
	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1; // time between two packet transmissions

	dataSN = 0;
	currSampleSN = 0;
	
	numNodes = getParentModule()->getParentModule()->par("numNodes"); //number of nodes in the network
	declareOutput("Packets sensed per node");
}

/**********************************************************************************************************/
/**********************************************************************************************************/

// this function is used for messages coming from other nodes through the routing/network layer
void TestmultiRingsApp::fromNetworkLayer(ApplicationPacket * rcvPacket,
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

void TestmultiRingsApp::timerFiredCallback(int index)
{
	if (isSink) {
		trace() << "Sink received SENSOR_READING (while it shouldnt) ";
		return;
	}
	// trace() << "Timer fired";
	switch (index) {
	    case SEND_DATA:{

	        setTimer(SEND_DATA, sampleInterval);
			ApplicationPacket *newPkt = createGenericDataPacket((double)self, currSampleSN++,1024);
					trace() << "Self "<<(double)self;

			toNetworkLayer(newPkt, SINK_NETWORK_ADDRESS);
	    }
	}
}

/**********************************************************************************************************/
/**********************************************************************************************************/

// void TestmultiRingsApp::handleSensorReading(SensorReadingMessage * sensorMsg)
// {
// 	trace() << "Sensor measured: "<< recipientAddress.c_str();
// 	string sensType(sensorMsg->getSensorType());
// 	double sensValue = sensorMsg->getSensedValue();

// 	collectOutput("Packets sensed per node");

// 	if (isSink) {
// 		trace() << "Sink received SENSOR_READING (while it shouldnt) "
// 		    << sensValue << " (int)" << (int)sensValue;
// 		return;
// 	}

// 	// trace() << "Sending packet, sequence number " << currSampleSN;
// 	ApplicationPacket *newPkt = createGenericDataPacket((double)self, currSampleSN++,1024);
// 	toNetworkLayer(newPkt, SINK_NETWORK_ADDRESS);
// }

/**********************************************************************************************************/
/**********************************************************************************************************/

void TestmultiRingsApp::handleNetworkControlMessage(cMessage * msg)
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
	        setTimer(SEND_DATA, sampleInterval);
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

void TestmultiRingsApp::finishSpecific()
{
	trace() << "Simulation ended";
}

/**********************************************************************************************************/
/**********************************************************************************************************/
