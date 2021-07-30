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

#include "EAmultipathRingsRouting.h"
#include "VirtualEnergyManager.h"

Define_Module(EAmultipathRingsRouting);

void EAmultipathRingsRouting::startup()
{

      if (!hasDied){  
	collectBatterySN =0;
	rssiThreshold = par("rssiThreshold");
	netSetupTimeout = (double)par("netSetupTimeout") / 1000.0;
	collectBatteryTimer = par("collectBatteryTimer");
	sendEnergyTimer = par("sendEnergyTimer");
	mpathRingsSetupFrameOverhead = par("mpathRingsSetupFrameOverhead");

	// check that the Application module used has the boolean parameter "isSink"
	cModule *appModule = getParentModule()->getParentModule()->getSubmodule("Application");
	if (appModule->hasPar("isSink"))
		isSink = appModule->par("isSink");
	else
		opp_error("\nEAmultipathRings routing has to be used with an application that defines the parameter isSink");

	currentLevel = tmpLevel = isSink ? 0 : NO_LEVEL;
	currentSinkID = tmpSinkID = isSink ? self : NO_SINK;

	isConnected = (isSink) ? true : false;
	isScheduledNetSetupTimeout = false;
	currentSequenceNumber = 0;

	setTimer(COLLECT_BATTERY, collectBatteryTimer);
	setTimer(ENERGY_MSG, 1);
	if (isSink){
		sendTopologySetupPacket();
	}
	declareOutput("Propagated_data");
	declareOutput("Battery level");
     }
     hasDied = true;
}

void EAmultipathRingsRouting::sendTopologySetupPacket()
{
	EAmultipathRingsRoutingPacket *setupPkt =
	    new EAmultipathRingsRoutingPacket("Multipath rings routing setup packet", NETWORK_LAYER_PACKET);
	setupPkt->setEamultipathRingsRoutingPacketKind(MPRINGS_TOPOLOGY_SETUP_PACKET);
	setupPkt->setSource(SELF_NETWORK_ADDRESS);
	setupPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
	setupPkt->setSinkID(currentSinkID);
	setupPkt->setSenderLevel(currentLevel);
	toMacLayer(setupPkt, BROADCAST_MAC_ADDRESS);
	trace()<<"Sent topology setup";
}

void EAmultipathRingsRouting::sendControlMessage(eamultipathRingsRoutingControlDef kind)
{
	EAmultipathRingsRoutingControlMessage *ctrlMsg =
	    new EAmultipathRingsRoutingControlMessage("Multipath routing control message",NETWORK_CONTROL_MESSAGE);
	ctrlMsg->setEamultipathRingsRoutingControlMessageKind(kind);
	ctrlMsg->setLevel(currentLevel);
	ctrlMsg->setSinkID(currentSinkID);
	toApplicationLayer(ctrlMsg);
}

void EAmultipathRingsRouting::timerFiredCallback(int index)
{
	
	if (index == COLLECT_BATTERY){

		  /* Obtain a pointer to the energy manager module */
	  	VirtualEnergyManager* engyMgr =
		check_and_cast<VirtualEnergyManager*>(getParentModule()->getParentModule()->
		getSubmodule("ResourceManager")->getSubmodule("EnergySubsystem")->getSubmodule("EnergyManager"));

		double currentEnergyRatio = engyMgr->getCurrentEnergyRatio();
		trace() << "Current energy ratio: " << currentEnergyRatio;
		collectBatterySN++;
		collectOutput("Battery level", collectBatterySN, "BatteryOverTime", currentEnergyRatio);
		setTimer(COLLECT_BATTERY, collectBatteryTimer);

	}else if (index == ENERGY_MSG){			
		
		setTimer(ENERGY_MSG, sendEnergyTimer);
		VirtualEnergyManager* engyMgr2 =
			check_and_cast<VirtualEnergyManager*>(getParentModule()->getParentModule()->
			getSubmodule("ResourceManager")->getSubmodule("EnergySubsystem")->getSubmodule("EnergyManager"));

		double currentHarvestingPower = engyMgr2->getCurrentHarvestingPower();
		double currentEnergyRatio = engyMgr2->getCurrentEnergyRatio();
		double MaxHarvestingPower = engyMgr2->getMaxHarvestingPower();
		double EnergyLevel;
		double HarvestingRate=0;
		
		if (MaxHarvestingPower > 0){
		
			HarvestingRate = currentHarvestingPower/MaxHarvestingPower;
			EnergyLevel = currentEnergyRatio+HarvestingRate;
			
		}else{
			EnergyLevel = currentEnergyRatio;
		}
		
		trace()<<"Harvesting Rate: "<< HarvestingRate << ", Remaining Energy: "<<currentEnergyRatio << ", MaxHarvestingPower: "<< MaxHarvestingPower;
		
		EAmultipathRingsRoutingPacket *energyPacket =
		    new EAmultipathRingsRoutingPacket("Multipath rings energy packet", NETWORK_LAYER_PACKET);
		energyPacket->setEamultipathRingsRoutingPacketKind(MPRINGS_ENERGY_PACKET);
		energyPacket->setSource(SELF_NETWORK_ADDRESS);
		energyPacket->setEnergyStatus(EnergyLevel);
		toMacLayer(energyPacket, BROADCAST_MAC_ADDRESS);
		


	}else if (index == TOPOLOGY_SETUP_TIMEOUT){

		isScheduledNetSetupTimeout = false;
		if (tmpLevel == NO_LEVEL) {
			setTimer(TOPOLOGY_SETUP_TIMEOUT, netSetupTimeout);
			isScheduledNetSetupTimeout = true;
		} else if (currentLevel == NO_LEVEL) {
			//Broadcast to all nodes of currentLevel-1
			currentLevel = tmpLevel + 1;
			currentSinkID = tmpSinkID;

			if (!isConnected) {
				isConnected = true;
				sendControlMessage(MPRINGS_CONNECTED_TO_TREE);
				trace() << "Connected to " << currentSinkID << " at level " << currentLevel;
				if (!TXBuffer.empty())
					processBufferedPacket();
			} else {
				sendControlMessage(MPRINGS_TREE_LEVEL_UPDATED);
				trace() << "Reconnected to " << currentSinkID << " at level " << currentLevel;
			}
			sendTopologySetupPacket();
		}

		tmpLevel = isSink ? 0 : NO_LEVEL;
		tmpSinkID = isSink ? self : NO_SINK;
	}
}

void EAmultipathRingsRouting::processBufferedPacket()
{
	while (!TXBuffer.empty()) {
		toMacLayer(TXBuffer.front(), BROADCAST_MAC_ADDRESS);
		TXBuffer.pop();
	}
}

void EAmultipathRingsRouting::fromApplicationLayer(cPacket * pkt, const char *destination)
{
	string dst(destination);
	
	EAmultipathRingsRoutingPacket *netPacket =
	    new EAmultipathRingsRoutingPacket("Multipath rings routing data packet", NETWORK_LAYER_PACKET);
	netPacket->setEamultipathRingsRoutingPacketKind(MPRINGS_DATA_PACKET);
	netPacket->setSource(SELF_NETWORK_ADDRESS);
	netPacket->setDestination(destination);
	netPacket->setSinkID(currentSinkID);
	netPacket->setSenderLevel(currentLevel);
	encapsulatePacket(netPacket, pkt);

	int nextHop = findNextHop();
	trace() << "Destination for "<< self << " is: " << nextHop;

	if (dst.compare(SINK_NETWORK_ADDRESS) == 0 || dst.compare(PARENT_NETWORK_ADDRESS) == 0) {
		netPacket->setSequenceNumber(currentSequenceNumber);
		currentSequenceNumber++;
		if (bufferPacket(netPacket)) {
			if (isConnected)
				processBufferedPacket();
			else
				sendControlMessage(MPRINGS_NOT_CONNECTED);
		} else {
			//Here we could send a control message to upper layer informing that our buffer is full
		}
	} else {		//++++ need to control flooding
		toMacLayer(netPacket, nextHop);
	}
}

void EAmultipathRingsRouting::fromMacLayer(cPacket * pkt, int macAddress, double rssi, double lqi)
{

	trace() << "RSSI of packet: "<<rssi << " from "<< macAddress;
	EAmultipathRingsRoutingPacket *netPacket = dynamic_cast <EAmultipathRingsRoutingPacket*>(pkt);
	string src(netPacket->getSource());
	if (!netPacket)
		return;

	switch (netPacket->getEamultipathRingsRoutingPacketKind()) {
		
		case MPRINGS_ENERGY_PACKET:{
			double energyLevel = netPacket->getEnergyStatus();
			neighboursMap[src].EnergyLevel = energyLevel;
			break;
		}
		case MPRINGS_TOPOLOGY_SETUP_PACKET:{
		
			neighbour neigh;
		
			//if (rssi < rssiThreshold)
			//	return;

			if (isSink)
				break;
			if (!isScheduledNetSetupTimeout) {
				isScheduledNetSetupTimeout = true;
				setTimer(TOPOLOGY_SETUP_TIMEOUT, netSetupTimeout);
				tmpLevel = NO_LEVEL;
				tmpSinkID = NO_SINK;
			}
			if (tmpLevel == NO_LEVEL || tmpLevel > netPacket->getSenderLevel()) {
			      	
				tmpLevel = netPacket->getSenderLevel();
				tmpSinkID = netPacket->getSinkID();
				neigh.RingLevel = tmpLevel;
			}
			trace()<<"Self: "<< SELF_NETWORK_ADDRESS<<", MAC address: "<<macAddress<<", "<<"MPRINGS_TOPOLOGY_SETUP_PACKET from: "<<netPacket->getSource();
			
			neighboursMap[src] = neigh;
			
			break;
		}

		case MPRINGS_DATA_PACKET:{
		

			int nextHop = findNextHop();
		
			collectOutput("Propagated_data");
			string dst(netPacket->getDestination());
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
						EAmultipathRingsRoutingPacket *dupPacket = netPacket->dup();
						dupPacket->setSenderLevel(currentLevel);
						toMacLayer(dupPacket, nextHop);
						trace()<<"ENERGY AWARE: Self net address: "<<SELF_NETWORK_ADDRESS<<", Receiver Address: "<<nextHop;
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
			trace()<<"Self net address: "<<SELF_NETWORK_ADDRESS<<", MAC Address: "<<macAddress<<" "<<"MPRINGS_DATA_PACKET from: "<<netPacket->getSource();
			break;
		}
	}
}

int EAmultipathRingsRouting::findNextHop(){
	double maxEnergy = -1;
	int nextHop;
	for(map<string,neighbour>::const_iterator it = neighboursMap.begin(); it != neighboursMap.end(); ++it)
	{
	    trace() << "Map of Neighbours of "<<self<<": "<< it->first <<", Energy: "<< (it->second).EnergyLevel << "\n";
	    double energy = (it->second).EnergyLevel;
	    if (energy > maxEnergy){
	    	nextHop = std::stoi(it->first);
	    	maxEnergy = energy;
	    }
	}
	
	return nextHop;
}

