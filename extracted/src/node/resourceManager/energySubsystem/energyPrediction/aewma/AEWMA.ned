//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyPrediction.aewma;

simple AEWMA like node.resourceManager.energySubsystem.energyPrediction.iEnergyPredictionModel
{
 parameters:
	bool collectTraceInfo = default(false);

	// number of seconds per slot
	int slotSize = default(3600);

	// number of samples per slot 
	int samplesPerSlot = default(1);

	// weighting factor in [0,1]
	double alpha = default(0.5);

	// prediction horizon (in number of slots)
	int predictionHorizon = default(1);

	// true if using the advanced prediction model; default setting is EWMA
	bool useAdvancedModel = default(false);

 gates:
	input fromEnergyManager;
}
