//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "Supercapacitor.h"
Define_Module(Supercapacitor);

void Supercapacitor::initialize() {

	VirtualEnergyStorage::initialize();

	string lm = par("leakageModel").stdstringValue();
	if ( lm.compare("none") == 0 ) {
		leakageModel = LEAKAGE_NONE;
	} else if ( lm.compare("constant") == 0 ){
		leakageModel = LEAKAGE_CONSTANT;
		constLeakageCurrent = par("constLeakageCurrent");
		if ( constLeakageCurrent < 0.0 ) 
			opp_error("\n[Supercapacitor]:\n Invalid value of parameter \"constLeakageCurrent\", must be positive or zero.");
	} else if ( lm.compare("exponential") == 0 ){
		
		// Beta release
		opp_error("[Supercapacitor]: exponential leakage model not supported yet");
		
		leakageModel = LEAKAGE_EXPONENTIAL;
		alpha = par("alpha");	
		
		P_0 = par("P_0");
		if(P_0 == 0.0)
			opp_error("\n[Supercapacitor]:\n Invalid value of parameter \"P_0\", must be not zero.");

	} else if ( lm.compare("piecewise") == 0 ){
		
		// Beta release
		opp_error("[Supercapacitor]: piecewise leakage model not supported yet");
		
		leakageModel = LEAKAGE_PIECEWISE;
	} else {
		opp_error("\n[Supercapacitor]:\n Invalid value of parameter \"leakageModel\", must be \"none\", \"constant\", \"exponential\" or \"piecewise\".");
	}

	capacitance = (double) par("capacitance");

	if ( capacitance < 0.0 )
		opp_error("\n[Supercapacitor]:\n Invalid value of parameter \"capacitance\", must be positive or zero.");

	minEnergy = 0.5 * capacitance * pow(minVoltage, 2);
	maxEnergy = 0.5 * capacitance * pow(maxVoltage, 2);
	curEnergy  = fractionInitialCharge * maxEnergy;
	initialEnergy = curEnergy;

	curVoltage = getVoltage();
	logStorageLevel();
	updateStatus();

	trace() << "Max energy: " << maxEnergy << " J, min energy: " << minEnergy 
		<< " J, current energy: " << curEnergy << " J";
	
	/* DEBUG */
	if ( curEnergy > maxEnergy || curEnergy < minEnergy )
		opp_error("[Supercapacitor]: curEnergy not in range [%lf - %lf]", minEnergy, maxEnergy );
	if ( curVoltage < 0 || curVoltage > maxVoltage )
		opp_error("[Supercapacitor]: curVoltage not in range [0 - %lf]", maxVoltage );
}

double Supercapacitor::energyLeakageModel() {
	double leakedEnergy = 0.0;

	switch ( leakageModel ){
		case LEAKAGE_CONSTANT: {
			// amount of energy leaked in J
			leakedEnergy = SIMTIME_DBL(constLeakageCurrent / 1000. * curVoltage * (simTime() - timeLastLeakageUpdate));
			break;
		} 
		case LEAKAGE_EXPONENTIAL: {
			break;
		} 
		case LEAKAGE_PIECEWISE: {
			break;
		} 
		default: {
			break;
		} 
	}

	return leakedEnergy;
}
