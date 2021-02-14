//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyHarvester;

moduleinterface iEnergyHarvester
{
 parameters:
	bool collectTraceInfo;

	// source type 
	string sourceType;

	// max harvesting power (hw limit)
	double maxHarvestingPower;	// mW

	string efficiencyFile;

	// if defined, ignore energy source and read values directly from file
	// useful to feed an harvester with a specific trace collected in real-life deployments
	string harvesterTraceFile;

 gates:
	output toEnergySubsystem;
}

