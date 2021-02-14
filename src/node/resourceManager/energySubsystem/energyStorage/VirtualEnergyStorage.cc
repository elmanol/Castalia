//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/
#include "VirtualEnergyStorage.h"

void VirtualEnergyStorage::initialize() {

	maxVoltage = par("maxVoltage");
	minVoltage = (getParentModule()->getParentModule()->getParentModule()->par("cutOffVoltage"));
	fractionInitialCharge = par("fractionInitialCharge");
	dischargingEfficiency = par("dischargingEfficiency");
	chargingEfficiency = par("chargingEfficiency");

	// input parameters check
	if ( maxVoltage < 0.0 )
		opp_error("[VirtualEnergyStorage]: Invalid value of parameter \"maxVoltage\", must be positive or zero.");

	if( maxVoltage < minVoltage )
		trace() << "WARNING: maxVoltage < minVoltage, storage device will be never used";

	if( fractionInitialCharge < 0.0 || fractionInitialCharge > maxVoltage )
		opp_error("[VirtualEnergyStorage]: Invalid value of parameter \"fractionInitialCharge\", must be positive or zero and not greater than \"maxVoltage\".");

	if ( dischargingEfficiency < 0.0 || dischargingEfficiency > 1.0 )
		opp_error("[VirtualEnergyStorage]: Invalid value of parameter \"dischargingEfficiency\", must be in [0,1].");

	if ( chargingEfficiency < 0.0 || chargingEfficiency > 1.0 )
		opp_error("[VirtualEnergyStorage]: Invalid value of parameter \"chargingEfficiency\", must be in [0,1].");

	// default device is ideal
	minEnergy = 0.0;

	// statistics
	totEnergyProvided  = 0.0;
	totEnergyDrawn  = 0.0;
	totEnergyWasted = 0.0;
	totEnergyStored = 0.0;
	totEnergyLeaked = 0.0;

	// node id
	cModule* node = check_and_cast<cModule*>(getParentModule()->getParentModule()->getParentModule()->
			getParentModule());
	nodeId = node->getIndex();

	// open trace file
	lastLoggedVoltage = -1;
	lastLoggedEnergy = -1;
	if ( par("traceFile").stdstringValue().size() > 0 ) {
		ostringstream debugFileName;
		debugFileName << par("traceFile").stdstringValue() << "-node" << nodeId;
		trace() << "Logging to: " <<  debugFileName.str();

		debugFile.open(debugFileName.str().c_str(), ios_base::trunc);

		if(!debugFile.is_open())
			opp_error("[VirtualEnergyStorage]: Could not open log file %s", debugFileName.str().c_str() );
	}
}

void VirtualEnergyStorage::logStorageLevel(){
	if ( debugFile.is_open() && (curVoltage != lastLoggedVoltage || curEnergy != lastLoggedEnergy) ){
		debugFile << simTime().dbl() << "\t" 
			<< curVoltage << "\t" // in V
			<< curEnergy	// in J
			<< std::endl;
		lastLoggedVoltage = curVoltage;
		lastLoggedEnergy = curEnergy;
	}
}

void VirtualEnergyStorage::updateStatus(){

	if ( curVoltage >= minVoltage && getAvailableEnergy() > 0.0 )
		disabled = false;
	else
		disabled = true;
}

pair<double, double> VirtualEnergyStorage::discharge(double amount) {

	double energyNeeded = (amount * (1.0 / dischargingEfficiency));
	double availableEnergy = curEnergy - minEnergy;
	double prevLevel = curEnergy;
	double energyProvided = 0.0;
	double energyConsumed = 0.0;

	if ( curVoltage >= minVoltage ) { // no energy is supplied if the storage voltage is below cutoff
		if ( availableEnergy >= energyNeeded ) {
			curEnergy -= energyNeeded; 
			energyProvided = amount;
		} else {
			curEnergy = minEnergy;
			energyProvided = availableEnergy * dischargingEfficiency;
		}

		// update current voltage
		curVoltage = getVoltage();

		logStorageLevel();

		energyConsumed = prevLevel - curEnergy;
		totEnergyProvided += energyProvided;
		totEnergyDrawn += energyConsumed;
		totEnergyWasted += energyProvided * (1.0 - dischargingEfficiency);

		updateStatus();
	} else {
		/* DEBUG */
		opp_error("[VirtualEnergyStorage] Attempt to discharge a disabled storage");
	}

	// return energy provided and consumed
	return make_pair(energyProvided, energyConsumed);
}

/* Charge the device with the given amount of energy
 * Returns the amount of energy used and the new amount of energy available
 */
pair<double, double> VirtualEnergyStorage::charge(double amount) {

	double prevLevel = curEnergy;
	double actualAmount = amount * chargingEfficiency;
	double used = amount;

	if(curEnergy + actualAmount > maxEnergy ){
		curEnergy = maxEnergy;
		used = (maxEnergy - prevLevel) * ( 1 / chargingEfficiency);
	} else {
		curEnergy += actualAmount;
	}

	// update voltage level
	curVoltage = getVoltage();

	logStorageLevel();

	// update statistics
	totEnergyStored += curEnergy - prevLevel;
	totEnergyWasted += used * (1.0 - chargingEfficiency);

	// update energy storage status
	updateStatus();

	// return energy used and new amount of energy available
	return make_pair(used, (curEnergy - prevLevel) * dischargingEfficiency);
}

double VirtualEnergyStorage::computeLeakage() {

	double prevLevel = curEnergy;
	double leakedEnergy = energyLeakageModel();
	double actualLeakedEnergy = leakedEnergy;

	if ( leakedEnergy > 0.0 ) {
		curEnergy = std::max(curEnergy - leakedEnergy, 0.0);
		actualLeakedEnergy = prevLevel - curEnergy;

		// update current voltage and log new storage level
		curVoltage = getVoltage();
		logStorageLevel();

		// update statistics
		totEnergyLeaked += actualLeakedEnergy;
	
		updateStatus();
	}

	timeLastLeakageUpdate = simTime();

	return actualLeakedEnergy;
}

void VirtualEnergyStorage::finishSpecific() {

	logStorageLevel();

	declareOutput("Device Energy");
	collectOutput("Device Energy", "Maximum", maxEnergy);
	collectOutput("Device Energy", "Minimum", minEnergy);
	collectOutput("Device Energy", "Initial", initialEnergy);
	collectOutput("Device Energy", "Final", curEnergy);
	collectOutput("Device Energy", "Charged", totEnergyStored);
	collectOutput("Device Energy", "Provided", totEnergyProvided);
	collectOutput("Device Energy", "Drawn", totEnergyDrawn);
	collectOutput("Device Energy", "Wasted", totEnergyWasted);

	if(debugFile.is_open())
		debugFile.close();
}
