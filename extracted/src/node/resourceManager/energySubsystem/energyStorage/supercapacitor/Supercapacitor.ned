//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyStorage.supercapacitor;

simple Supercapacitor like node.resourceManager.energySubsystem.energyStorage.iEnergyStorage
{
parameters:
	// ---------- EnergyStorage parameters ---------- //

	bool collectTraceInfo = default(false);

	// device maximum voltage (V)
	double maxVoltage = default(2.3);

    // initial charge fraction
    double fractionInitialCharge = default(1.0);

	// debug log file path
	string traceFile = default("");

	// ---------- Supercapacitor parameters ---------- //
	// device maximum capacity (F)
	double capacitance = default(50.0);
	
	// battery discharge efficiency
	double dischargingEfficiency = default(1.0);

	// supercapacitor charge efficiency 
	double chargingEfficiency = default(1.0);

	// supercapacitor leakage models
	// valid values: none, constant, exponential, piecewise
	string leakageModel = default("none");

	// [only if constant leakage model is used] constant leakage current in mA
	double constLeakageCurrent = default(0.0);

	// [only if exponential leakage model is used]
	double P_0 = default(0);
	double alpha = default(0);

gates:
	input fromEnergySubsystem;
}

