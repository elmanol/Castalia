//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyStorage.rechargeableBattery;

simple RechargeableBattery like node.resourceManager.energySubsystem.energyStorage.iEnergyStorage
{
parameters:
	bool collectTraceInfo = default(false);

	// device maximum voltage (expressed in V)
	double maxVoltage = default(3.0);

    // initial charge fraction
	double fractionInitialCharge = default(1.0);

	// debug log file path
	string traceFile = default("");

	// discharging efficiency
	double dischargingEfficiency = default(1.0);
	
	// charging efficiency
	double chargingEfficiency = default(1.0);

	// ---------- RechargeableBattery parameters ---------- //
	double mAmpereHour = default(2450);
	
	// battery maximum number of charge/discharge cycles
	int cycleLife = default(0);
	
	// battery model
	string batteryModel = default("ideal");

	// file with empirical discharge pattern - only used if batteryModel != ideal 
	string empiricalDischargeFile = default("");

gates:
	input fromEnergySubsystem;
}

