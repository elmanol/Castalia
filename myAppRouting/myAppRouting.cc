/*******************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2011                            *
 *  Developed at the ATP lab, Networked Systems research theme                 *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                           *
 *  This file is distributed under the terms in the attached LICENSE file.     *
 *  If you do not find this file, copies can be found by writing to:           *
 *                                                                             *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                *
 *      Attention:  License Inquiry.                                           *
 *                                                                             *  
 *******************************************************************************/

#include "myAppRouting.h"

Define_Module(myAppRouting);

void myAppRouting::startup()
{
	// check that the Application module used has the boolean parameter "isSink"
	cModule *appModule = getParentModule()->getParentModule()->getSubmodule("Application");
	if (appModule->hasPar("isSink"))
		isSink = appModule->par("isSink");
	else
		opp_error("\nmyAppRouting routing has to be used with an application that defines the parameter isSink");

	currentSequenceNumber = 0;
	setTimer(GET_NEIGHBOURS_TIMER, startupDelay);


	//if (isSink)

}

void myAppRouting::timerFiredCallback(int index)
{

}

void myAppRouting::processBufferedPacket()
{
	while (!TXBuffer.empty()) {
		toMacLayer(TXBuffer.front(), BROADCAST_MAC_ADDRESS);
		TXBuffer.pop();
	}
}

void myAppRouting::fromApplicationLayer(cPacket * pkt, const char *destination)
{
	string dst(destination);

    string packetName(cPacket->getName());

    if (packetName.compare(SEND_DATA_NAME) == 0) {

		myAppRoutingPacket *netPacket =
		    new myAppRoutingPacket("mMyApp routing data packet", NETWORK_LAYER_PACKET);
		netPacket->setMyAppRoutingPacketKind(DATA_PACKET);
		netPacket->setSource(SELF_NETWORK_ADDRESS);
		netPacket->setDestination(destination);
		netPacket->setSinkID(currentSinkID);
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
	}else if(packetName.compare(SEND_DATA_NAME) == 0){

	}
}

void myAppRouting::fromMacLayer(cPacket * pkt, int macAddress, double rssi, double lqi)
{
	myAppRoutingPacket *netPacket = dynamic_cast <myAppRoutingPacket*>(pkt);
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

		case MPRINGS_DATA_PACKET:{
			string dst(netPacket->getDestination());
			string src(netPacket->getSource());
			int senderLevel = netPacket->getSenderLevel();
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
						myAppRoutingPacket *dupPacket = netPacket->dup();
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
