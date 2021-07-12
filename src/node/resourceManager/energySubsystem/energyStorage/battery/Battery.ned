//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyStorage.battery;

simple Battery like node.resourceManager.energySubsystem.energyStorage.iEnergyStorage
{
parameters:
	bool collectTraceInfo = default(false);

	// device maximum voltage (V)
	double maxVoltage = default(3.0);

	// initial charge fraction
	double fractionInitialCharge = default(1.0);

	// battery model ("ideal" or "empirical")
	string batteryModel = default("ideal");

	// Debug log file path
	string traceFile = default("");

	string empiricalDischargeFile = default("");

	// ---------- Battery parameters ---------- //

	// mAh
	double mAmpereHour = default(1735); // default(1800);
	
	// battery discharging efficiency
	double dischargingEfficiency = default(1.0);
	
	// battery charging efficiency
	double chargingEfficiency = 0.0;

gates:
	input fromEnergySubsystem;
}

