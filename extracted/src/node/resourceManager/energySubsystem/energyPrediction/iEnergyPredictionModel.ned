//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyPrediction;

moduleinterface iEnergyPredictionModel
{
 parameters:
	bool collectTraceInfo;

	// slot duration (in seconds)
	int slotSize;
	
	// number of samples per slot 
	int samplesPerSlot;

	// prediction horizon (number of slots)
	int predictionHorizon;

 gates:
	input fromEnergyManager;
}

