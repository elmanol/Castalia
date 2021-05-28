//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyStorage;

moduleinterface iEnergyStorage
{
parameters:
	bool collectTraceInfo;

	// maximum voltage (V)
	double maxVoltage;

    // initial charge fraction
    double fractionInitialCharge;

	// discharge efficiency
	double dischargingEfficiency;

   // supercapacitor charge efficiency
   double chargingEfficiency;

	// Debug log file path 
	string traceFile;

gates:
	input fromEnergySubsystem;
}

