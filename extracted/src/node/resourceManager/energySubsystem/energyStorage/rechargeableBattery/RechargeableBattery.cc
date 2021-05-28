//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "RechargeableBattery.h"
#include <algorithm>       
#include <cmath>       

Define_Module(RechargeableBattery);

void RechargeableBattery::initialize() {

	VirtualEnergyStorage::initialize();

	// getting input parameters 
	mAmpereHour = par("mAmpereHour");
	cycleLife = (unsigned)par("cycleLife");

	// checking input parameters
	if ( mAmpereHour < 0.0 )
		opp_error("[RechargeableBattery]: Invalid value of parameter \"maxCapacity\", must be positive or zero.");

	if ( cycleLife < 0.0 )
		opp_error("[RechargeableBattery]: Invalid value of parameter \"cycleLife\", must be positive or zero.");

	const char* batteryT = par("batteryModel").stringValue();
	if ( !strcmp( batteryT, "ideal" ) )
		bt = BATTERY_IDEAL;
	else if ( !strcmp( batteryT, "empirical" ) )
		bt = BATTERY_EMPIRICAL;
	else
		opp_error("[RechargeableBattery]: Invalid value of parameter \"batteryModel\".");

	maxEnergy = (mAmpereHour * 3.6) * maxVoltage;   // (mAh * 3.6 * V -> J)
	curEnergy = fractionInitialCharge * maxEnergy;
	initialEnergy = curEnergy;
	numCycles = 0;

	if ( bt == BATTERY_EMPIRICAL ) {
		const char* empiricalDischargeFile = par("empiricalDischargeFile").stringValue();
		double knot, ax, b;
		ifstream srcFile;

		// temp variables to compute minimum energy level
		double minKnotVoltage = 0.0;
		double prevKnot = -1;
		double prevVoltage = -1;
		double voltage = 0.0;

		srcFile.open (empiricalDischargeFile);

		while (srcFile.good()) {
			srcFile >> knot >> ax >> b >> ws;

			if ( knot < 0.0 || knot > 100.0 )
				opp_error( "[RechargeableBattery]: Wrong file format: %s", empiricalDischargeFile);

			if ( prevKnot >= knot )
				opp_error( "[RechargeableBattery]: Wrong file format: %s, file must be sorted.", empiricalDischargeFile);

			// voltage at current knot
			if ( !empiricalDischarge.empty() ) {
				voltage = empiricalDischarge.back().second.first * ( knot - empiricalDischarge.back().first) +
					empiricalDischarge.back().second.second;
			} else {
				voltage = minKnotVoltage = ax * knot + b;
			}

			if ( minVoltage >= prevVoltage && minVoltage <= voltage && ! empiricalDischarge.empty() ) {
				minEnergy = maxEnergy * 1. / 100. * ( ( empiricalDischarge.back().first +
							( (minVoltage - empiricalDischarge.back().second.second) / empiricalDischarge.back().second.first )));
			}

			prevVoltage = voltage;
			prevKnot = knot;

			empiricalDischarge.push_back ( std::make_pair( knot, std::make_pair( ax, b ) ));
		}

		if ( empiricalDischarge.size() < 1 )
			opp_error( "[RechargeableBattery]: empirical battery model specified, but file %s is empty or has bad format.",
					empiricalDischargeFile);

		curV = std::make_pair( 100.0, std::make_pair( 0.0, 0.0 ) );

		double maxKnotVoltage = empiricalDischarge.back().second.first * ( prevKnot - empiricalDischarge.back().first) +
			empiricalDischarge.back().second.second;

		if ( minVoltage  < minKnotVoltage )
			minEnergy = 0.0;
		else if (minVoltage > maxKnotVoltage )
			minEnergy = maxEnergy;
	}

	curVoltage = getVoltage();                      // (V)
	logStorageLevel();
	deadBattery = false;
	lastOperation = RBATTERY_NULL;
	updateStatus();

	/* DEBUG */
	trace() << "Max energy: " << maxEnergy << " J, min energy: " << minEnergy  
		<< " J, current energy: " << curEnergy << " J";
	if ( curEnergy > maxEnergy || curEnergy < minEnergy )
		opp_error("[RechargeableBattery]: curEnergy not in range [%lf - %lf]", minEnergy, maxEnergy );
	if ( curVoltage < 0 || curVoltage > maxVoltage )
		opp_error("[RechargeableBattery]: curVoltage not in range [0 - %lf]", maxVoltage );
}

double RechargeableBattery::getVoltage( ) {

	if ( bt == BATTERY_IDEAL ) {

		if ( curEnergy > minEnergy )
			return maxVoltage;

		return 0.0;
	}

	/* Compute % current charge */
	curV.first = 100.0 * curEnergy / maxEnergy;

	std::vector< std::pair< double, PiecewiseCoefficients > >::iterator v =
		std::lower_bound (empiricalDischarge.begin(), empiricalDischarge.end(), curV);

	if ( v != empiricalDischarge.begin() )
		--v;

	return (*v).second.first * ( curV.first - (*v).first ) + (*v).second.second;
}

void RechargeableBattery::updateStatus(){
	VirtualEnergyStorage::updateStatus();
	disabled = disabled || deadBattery;
}

pair<double, double> RechargeableBattery::discharge(double amount) {

	if ( deadBattery )
		return make_pair(0.0, 0.0);

	pair<double, double> devEnergy = VirtualEnergyStorage::discharge(amount);

	if ( devEnergy.first > 0 && cycleLife > 0 ){
		if ( lastOperation == RBATTERY_CHARGE ) {
			if ( ++numCycles > cycleLife ) {
				deadBattery = true;
				// DEBUG: trace() << "numCycles exceeded cycleLife: rechargeable battery is now dead";
				updateStatus();
			}
		}

		lastOperation = RBATTERY_DISCHARGE;
	}

	return devEnergy;
}

/* charge the supercapacitor with the given amount of energy
 * Returns the amount of energy used and the new amount of energy available
 */
pair<double, double> RechargeableBattery::charge(double amount) {

	if ( deadBattery )
		return make_pair(0.0, 0.0);

	pair<double, double> devEnergy = VirtualEnergyStorage::charge(amount);

	if ( devEnergy.second > 0 && cycleLife > 0 ){
		if(lastOperation == RBATTERY_DISCHARGE) {
			if ( ++numCycles > cycleLife ) {
				deadBattery = true;
				// DEBUG: trace() << "numCycles exceeded cycleLife: rechargeable battery is now dead";
				updateStatus();
			}
		}

		lastOperation = RBATTERY_CHARGE;
	}

	return devEnergy;
}

double RechargeableBattery::energyLeakageModel()
{
	return 0.0;
}
