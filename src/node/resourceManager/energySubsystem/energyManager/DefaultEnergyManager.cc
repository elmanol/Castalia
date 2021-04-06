//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "DefaultEnergyManager.h"

Define_Module(DefaultEnergyManager);

using namespace std;

/* Simulate energy harvesting and consumption over the period of time elapsed from 'timeLastUpdate'
 * harvestingPower and powerConsumption are in Watt
 */
void DefaultEnergyManager::updateEnergy() {

	simtime_t timePassed = simTime() - timeLastUpdate;
	double harvestingPower = harvestingPowerRate;
	double powerConsumption = nodePowerConsumption;

	if ( timePassed < 0.0 || harvestingPower < 0.0 || powerConsumption < 0.0 )
		opp_error("[DefaultEnergyManager] Unexpected error in updateEnergy()"); 

	// disabled nodes do not consume energy
	if ( disabled ) {
		powerConsumption = 0.0;
		disabledTime += timePassed;
	} else {
		if ( nodePowerConsumption < baselineNodePower )
			opp_error("[DefaultEnergyManager] Unexpected error in updateEnergy()"); 

		trace() << "energy consumed in the last " << timePassed
			<< "s is " << (timePassed * powerConsumption) << " mW";
	}

	// debug log file
	if ( debugFile.is_open() ){
		debugFile << simTime().dbl() 
			<< "\t" << std::setprecision(12) << harvestingPower 
			<< "\t" << std::setprecision(12) << powerConsumption 
			<< "\t" << disabled 
			<< std::endl;
	}

	// update the amount of energy harvested
	totEnergyHarvested += SIMTIME_DBL(timePassed * harvestingPower / 1000.);

	double netPower = powerConsumption - harvestingPower;
	double netEnergy = SIMTIME_DBL(timePassed * netPower / 1000.);
	double missingEnergy = 0.0;

	if ( netPower < 0 ) {
		double surplus = -netEnergy;

		// simulate storage devices charging 
		totEnergyWasted += chargeStorages(surplus);

		// update the amount of energy supplied
		totEnergySupplied += SIMTIME_DBL(timePassed * powerConsumption / 1000.);

	} else if (netPower > 0 ) {
		missingEnergy = dischargeStorages( netEnergy );
	}

	if ( missingEnergy > 0.0 ){
		/* DEBUG */
		opp_error("[%lf] energy missing: %lf, powerConsumption: %lf, harvestingPower: %lf, timeLastUpdate: %lf",
				simTime().dbl(), missingEnergy, powerConsumption, harvestingPower, timeLastUpdate.dbl() );
	}

	double energyLeaked = computeEnergyLeakage();
	totEnergyLeaked += energyLeaked;
	remainingEnergy = max(remainingEnergy - energyLeaked, 0.0 );

	timeLastUpdate = simTime();
}	

bool DefaultEnergyManager::checkNodeOnOff(){
	double netNodePower = nodePowerConsumption - harvestingPowerRate;
	bool canSupplyNext = canSupply( periodicEnergyCalculationInterval * netNodePower / 1000. );
	bool stateChanged = false;

	if( disabled && canSupplyNext ) {
		switchOnNode();
		stateChanged = true;
	} else if ( !disabled && !canSupplyNext ) {
		switchOffNode();
		stateChanged = true;
	}

	if ( energyMsg && energyMsg->isScheduled() )
		cancelEvent(energyMsg);

	if ( !disabled || harvestingPowerRate > 0.0 )
		scheduleAt(simTime() + periodicEnergyCalculationInterval, energyMsg);

	return stateChanged;
}

double DefaultEnergyManager::getUsableEnergy() const {
	double energy = 0.0;

	for(vector<VirtualEnergyStorage*>::const_iterator biv = storageDevices.begin();
			biv != storageDevices.end();  ++biv) {
		energy += (*biv)->getUsableEnergy();
	}

	return energy;
}

double DefaultEnergyManager::chargeStorages(double excessEnergy) {

	for(vector<VirtualEnergyStorage*>::const_iterator biv = storageDevices.begin();
			biv != storageDevices.end() && excessEnergy > 0.0; ++biv) {

		if ( !(*biv)->isChargeable() )
			continue;

		pair<double, double> devEnergy = (*biv)->charge(excessEnergy);

		if ( devEnergy.first < 0 || devEnergy.second < 0 || devEnergy.first > excessEnergy )
			opp_error("[DefaultEnergyManager] Unexpected error in updateEnergy()");

		excessEnergy -= devEnergy.first; 	// energy used
		remainingEnergy += devEnergy.second; // new energy available
	}

	return excessEnergy;
}

// energy is in J
double DefaultEnergyManager::dischargeStorages(double energyNeeded) {

	for(vector<VirtualEnergyStorage*>::const_iterator biv = storageDevices.begin();
			biv != storageDevices.end() && energyNeeded > 0.0;  ++biv) {

		if ( (*biv)->isDisabled() ) {
			continue;
		}

		pair<double, double> devEnergy = (*biv)->discharge(energyNeeded);

		if ( devEnergy.first < 0 || devEnergy.second < 0 || devEnergy.first > energyNeeded )
			opp_error("[DefaultEnergyManager] Unexpected error in updateEnergy()");

		energyNeeded -= devEnergy.first;        // energy provided
		totEnergySupplied += devEnergy.second;	// energy consumed
		remainingEnergy = max(remainingEnergy - devEnergy.second, 0.0 ); 
	}

	return energyNeeded;
}

void DefaultEnergyManager::handleMessage(cMessage* msg)
{
	switch (msg->getKind())
	{
		case NODE_STARTUP:
			{
				if ( !startupReceived ) {
					trace() << "NODE_STARTUP";
					updateEnergy();
					startupReceived = true;
				}
				break;
			}

		case PERIODIC_ENERGY_CALCULATION:
			{
				updateEnergy();
				break;
			}

		case ENERGY_SUBSYSTEM_HARVESTING_RATE_CHANGED:
			{
				ResourceManagerHarvestingMessage *resMsg = check_and_cast<ResourceManagerHarvestingMessage*>(msg);
				int id = resMsg->getSenderModuleId();
				double oldHpower = storedHarvestingPowerRates[id];
				if ( oldHpower < 0 )
					opp_error("[DefaultEnergyManager] Unexpected error in updateEnergy()");

				updateEnergy();
				storedHarvestingPowerRates[id] = resMsg->getHarvestingPower();
				harvestingPowerRate = harvestingPowerRate - oldHpower + resMsg->getHarvestingPower();

				/* Rounding errors may lead to negative harvestingPowerRate -- DEBUG! 
				   assert ( harvestingPowerRate >= 0.0 );
				   */
				harvestingPowerRate = max( harvestingPowerRate, 0.0 );

				break;
			}

		case RESOURCE_MANAGER_DRAW_POWER:
			{
				// trace() << "RESOURCE_MANAGER_DRAW_POWER";
				ResourceManagerMessage *resMsg = check_and_cast<ResourceManagerMessage*>(msg);
				int id = resMsg->getSenderModuleId();
				double oldPower = storedPowerConsumptions[id];
				if ( oldPower < 0 )
					opp_error("[DefaultEnergyManager] Unexpected error in updateEnergy()");

				trace() << "New power consumption, id = " << id << ", oldPower = " <<
					nodePowerConsumption << ", newPower = " <<
					nodePowerConsumption - oldPower + resMsg->getPowerConsumed();

				updateEnergy();
				storedPowerConsumptions[id] = resMsg->getPowerConsumed();
				nodePowerConsumption = nodePowerConsumption - oldPower + resMsg->getPowerConsumed();

				break;
			}

		default:
			{
				opp_error("ERROR: Unexpected message");
				break;
			}
	}

	// check if node state has changed
	if ( checkNodeOnOff() ){
		trace() << "Node state changed";
	}

	if ( msg->getKind() != PERIODIC_ENERGY_CALCULATION )	// do not delete PERIODIC_ENERGY_CALCULATION message
		delete msg;
}

void DefaultEnergyManager::finishSpecific() {

	updateEnergy();
	VirtualEnergyManager::finishSpecific();
}
