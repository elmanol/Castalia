//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyManager;

moduleinterface iEnergyManager
{
 parameters:
	bool collectTraceInfo;
	string traceFile;

 gates:
	output toStorageDevice[];
	output toSensorDevManager;
	output toApplication;
	output toNetwork;
	output toMac;
	output toRadio;
	input powerConsumption @ directIn;
	input fromHarvesterDevice[];
	output toResourceManager;
	output toEnergyPredictor @loose;    // unconnected if energy prediction is not used
}
