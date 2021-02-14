//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyHarvester.traceHarvester;

simple TraceHarvester like node.resourceManager.energySubsystem.energyHarvester.iEnergyHarvester
{
 parameters:
	bool collectTraceInfo = default(false);	

	// data source type for the device
	string sourceType = default("");

	// max harvesting power (hw limit)
	double maxHarvestingPower = default(-1);	// mW

	string efficiencyFile = default("");

	// if defined, ignore energy source and read values directly from file
	// useful to feed an harvester with a specific trace collected in real-life deployments
	string harvesterTraceFile = default("");

 gates:
	output toEnergySubsystem;
}

