//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyHarvester.solarCell;

// Simple model for a solar cell harvesting energy from a TraceEnergySource
// IMPORTANT: assume that the corresponding TraceEnergySource emits irradiance value in unit W/m^2

simple SolarCell like node.resourceManager.energySubsystem.energyHarvester.iEnergyHarvester
{
 parameters:
	bool collectTraceInfo = default(false);	

	// data source type for the device
	string sourceType = "Solar";

	// max harvesting power (hardware limit)
	//double maxHarvestingPower = default(18);	// in mW IXOLAR XOB17-04x3
	//double maxHarvestingPower = default(24.5);	// in mW IXOLAR KXOB25-12X1F-TR
	double maxHarvestingPower = default(98);	// in mW ANYSOLAR Ltd SM111K04L
	// solar cell size (in cm^2)
	// double size = default(1.54);			// IXOLAR XOB17-04x3
	// double size = default(1.54);			// IXOLAR KXOB25-12X1F-TR
	double size = default(6.02);			// ANYSOLAR Ltd SM111K04L

	// solar cell efficiency -- depends on solar cell hardware
	//double cellEfficiency = default(0.17);	// IXOLAR XOB17-04x3
	//double cellEfficiency = default(0.25);	// IXOLAR KXOB25-12X1F-TR
	double cellEfficiency = default(0.25);	// ANYSOLAR Ltd SM111K04L
		
	// time-varying harvesting efficiency -- depends on shadows, dust, ecc
	string efficiencyFile = default("");

	// if defined, ignore energy source and read values directly from file
	// useful to feed an harvester with a specific trace collected in real-life deployments
	string harvesterTraceFile = default("");

 gates:
	output toEnergySubsystem;
}

