#include "MyAppRouting.h"

Define_Module(MyAppRouting);

void MyAppRouting::startup()
{

	startupDelay = par("startupDelay");// time till the node starts

	// check that the Application module used has the boolean parameter "isSink"
	cModule *appModule = getParentModule()->getParentModule()->getSubmodule("Application");
	if (appModule->hasPar("isSink"))
		isSink = appModule->par("isSink");
	else
		opp_error("\nMyAppRouting routing has to be used with an application that defines the parameter isSink");

	currentSequenceNumber = 0;
	setTimer(GIMMIE_NEIGHBOURS_TIMER, startupDelay);


	//if (isSink)
}

void MyAppRouting::timerFiredCallback(int index)
{

}

void MyAppRouting::processBufferedPacket()
{
	while (!TXBuffer.empty()) {
		toMacLayer(TXBuffer.front(), BROADCAST_MAC_ADDRESS);
		TXBuffer.pop();
	}
}

void MyAppRouting::fromApplicationLayer(cPacket * pkt, const char *destination)
{
	string dst(destination);

    string packetName(pkt->getName());

	netPacket->setMultipathRingsRoutingPacketKind(MPRINGS_DATA_PACKET);

	MyAppRoutingPacket *netPacket =
	    new MyAppRoutingPacket("mMyApp routing data packet", NETWORK_LAYER_PACKET);
	netPacket->setSource(SELF_NETWORK_ADDRESS);
	netPacket->setSinkID(currentSinkID);
	netPacket->setDestination(destination);

    if (packetName.compare(SEND_DATA_NAME) == 0) {

		netPacket->setMyAppRoutingPacketKind(DATA_PACKET);
		encapsulatePacket(netPacket, pkt);

		if (dst.compare(SINK_NETWORK_ADDRESS) == 0 || dst.compare(PARENT_NETWORK_ADDRESS) == 0) {
			netPacket->setSequenceNumber(currentSequenceNumber);
			currentSequenceNumber++;
			if (bufferPacket(netPacket)) {
				if (isConnected)
					processBufferedPacket();
			} else {
				//Here we could send a control message to upper layer informing that our buffer is full
			}
		} else {		//++++ need to control flooding

			toMacLayer(netPacket, BROADCAST_MAC_ADDRESS);
		}
	}else if(packetName.compare(GIMMIE_NEIGHBOURS_NAME) == 0){

		netPacket->setMyAppRoutingPacketKind(GIMMIE_NEIGHBOURS);
		encapsulatePacket(netPacket, pkt);
		toMacLayer(netPacket, BROADCAST_MAC_ADDRESS);

	}else if(packetName.compare(PUSH_NEIGHBOUR_NAME) == 0){

		netPacket->setMyAppRoutingPacketKind(PUSH_NEIGHBOUR);
		encapsulatePacket(netPacket, pkt);
		toMacLayer(netPacket, BROADCAST_MAC_ADDRESS);

	}
}

void MyAppRouting::fromMacLayer(cPacket * pkt, int macAddress, double rssi, double lqi)
{
	MyAppRoutingPacket *netPacket = dynamic_cast <MyAppRoutingPacket*>(pkt);
	if (!netPacket)
		return;

	switch (netPacket->getMyAppRoutingPacketKind()) {

		case MPRINGS_TOPOLOGY_SETUP_PACKET:{
			if (isSink)
				break;
			if (!isScheduledNetSetupTimeout) {

			}
			break;
		}

		case DATA_PACKET:{
			string dst(netPacket->getDestination());
			string src(netPacket->getSource());
			int sinkID = netPacket->getSinkID();

			if (dst.compare(BROADCAST_NETWORK_ADDRESS) == 0 ||
					dst.compare(SELF_NETWORK_ADDRESS) == 0) {
				// We are not filtering packets that are sent to this node directly or to 
				// broadcast network address, making application layer responsible for them
				toApplicationLayer(pkt->decapsulate());

			} else if (dst.compare(SINK_NETWORK_ADDRESS) == 0) {
				if (senderLevel == currentLevel + 1) {
					if (self == sinkID) {
						// Packet is for this node, if filter passes, forward it to application
						if (isNotDuplicatePacket(pkt))
							toApplicationLayer(decapsulatePacket(pkt));
						else
							trace() << "Discarding duplicate packet from node " << src;
					} else if (sinkID == currentSinkID) {
						// We want to rebroadcast this packet since we are not its destination
						// For this, a copy of the packet is created and sender level field is 
						// updated before calling toMacLayer() function
						MyAppRoutingPacket *dupPacket = netPacket->dup();
						dupPacket->setSenderLevel(currentLevel);
						toMacLayer(dupPacket, BROADCAST_MAC_ADDRESS);
					}
				}

			} else if (dst.compare(PARENT_NETWORK_ADDRESS) == 0) {
				if (senderLevel == currentLevel + 1 && sinkID == currentSinkID) {
					// Packet is for this node, if filter passes, forward it to application
					if (isNotDuplicatePacket(pkt))
						toApplicationLayer(decapsulatePacket(pkt));
					else
						trace() << "Discarding duplicate packet from node " << src;
				}
			}
			break;
		}
	}
}
