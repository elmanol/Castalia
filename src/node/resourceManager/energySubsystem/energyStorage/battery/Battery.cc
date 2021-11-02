//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "Battery.h"
#include <algorithm>       
#include <cmath>       

Define_Module(Battery);

void Battery::initialize() {

	VirtualEnergyStorage::initialize();

	mAmpereHour = par("mAmpereHour");

	// checking input parameters
	if ( mAmpereHour < 0.0 )
		opp_error("[Battery]: Invalid value of parameter \"maxCapacity\", must be positive or zero.");

	// battery type
	string batteryT = par("batteryModel").stdstringValue();
	if ( batteryT.compare("ideal") == 0 )
		bt = BATTERY_IDEAL;
	else if ( batteryT.compare("empirical") != 0 )
		bt = BATTERY_EMPIRICAL;
	else
		opp_error("[Battery]: Invalid value of parameter \"batteryModel\".");

	maxEnergy = (mAmpereHour * 3.6) * maxVoltage;  	// (mAh * 3.6 * V -> J)
	curEnergy = fractionInitialCharge * maxEnergy;
	initialEnergy = curEnergy;

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
				opp_error( "[Battery]: Wrong file format: %s", empiricalDischargeFile);

			if ( prevKnot >= knot ) 
				opp_error( "[Battery]: Wrong file format: %s, file must be sorted.", empiricalDischargeFile);

			// voltage at current knot
			if ( !empiricalDischarge.empty() ) {
				voltage = empiricalDischarge.back().second.first * ( knot - empiricalDischarge.back().first) +
					empiricalDischarge.back().second.second;
			} else {
				voltage = minKnotVoltage = ax * knot + b;
			}

			if ( minVoltage >= prevVoltage && minVoltage <= voltage && ! empiricalDischarge.empty() ) {
				minEnergy = maxEnergy * 1. / 100. * (( empiricalDischarge.back().first +
						( (minVoltage - empiricalDischarge.back().second.second) / empiricalDischarge.back().second.first )));
			}

			prevVoltage = voltage;
			prevKnot = knot;

			empiricalDischarge.push_back ( std::make_pair( knot, std::make_pair( ax, b ) ));
		}

		if ( empiricalDischarge.size() < 1 )
			opp_error( "[Battery]: empirical battery model specified, but file %s is empty or has bad format.",
					empiricalDischargeFile);

		curV = std::make_pair( 100.0, std::make_pair( 0.0, 0.0 ) );

		double maxKnotVoltage = empiricalDischarge.back().second.first * ( prevKnot - empiricalDischarge.back().first) +
			empiricalDischarge.back().second.second;

		if ( minVoltage  < minKnotVoltage )
			minEnergy = 0.0;
		else if (minVoltage > maxKnotVoltage )
			minEnergy = maxEnergy;
	}

	curVoltage = getVoltage();				     	// (V)
	logStorageLevel();
	updateStatus();

	trace() << "Max energy: " << maxEnergy << " J, min energy: " << minEnergy
		<< " J, current energy: " << curEnergy << " J";
	
	/* DEBUG */
	if ( curEnergy > maxEnergy || curEnergy < minEnergy )
		opp_error("[Battery]: curEnergy not in range [%lf - %lf]", minEnergy, maxEnergy );
	if ( curVoltage < 0 || curVoltage > maxVoltage )
		opp_error("[Battery]: curVoltage not in range [0 - %lf]", maxVoltage );

	totEnergyDrawn   = 0.0;
	totEnergyLeaked  = 0.0;
}

double Battery::getVoltage( ) {

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

double Battery::energyLeakageModel()
{
	return 0.0;
}
