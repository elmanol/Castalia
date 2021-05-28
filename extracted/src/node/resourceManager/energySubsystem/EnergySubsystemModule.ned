//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem;

// The sensor energySubsystem module. 

module EnergySubsytemModule
{
	parameters:
		bool collectTraceInfo = default (false);

		string EnergyManagerType   = default("DefaultEnergyManager");
		string PredictorType = default("");

	gates:
		output toSensorDevManager;		
		output toApplicationModule;		
		output toNetworkModule;			
		output toMacModule;			
		output toRadioModule;			
		output toResourceManager;
		input powerConsumption @ directIn;	

	submodules:

		// energy harvesting module
	  	EnergyHarvesting: node.resourceManager.energySubsystem.energyHarvester.EnergyHarvestingModule;

		// energy storage module
		EnergyStorage: node.resourceManager.energySubsystem.energyStorage.EnergyStorageModule;

		// energy manager module
	 	EnergyManager: <EnergyManagerType> like node.resourceManager.energySubsystem.energyManager.iEnergyManager;

		// energy prediction model
		EnergyPrediction: <PredictorType> like node.resourceManager.energySubsystem.energyPrediction.iEnergyPredictionModel if PredictorType != "";

	connections:

	// *********************************************************** //
	// HARVESTING CONNECTIONS: EnergyManager --> HARVESTING-DEVICE //
	// *********************************************************** //
	// manager <--> harvesters connections
	for i = 0..EnergyHarvesting.numEnergyHarvesters-1 {
		EnergyHarvesting.toEnergySubsystem[i] --> EnergyManager.fromHarvesterDevice++;
	}

	// ***************************************************** //
	// STORAGE CONNECTIONS: EnergyManager --> STORAGE-DEVICE //
	// ***************************************************** //
	// manager <--> batteries connections
	for i = 0..EnergyStorage.numBatteries-1 {
		EnergyManager.toStorageDevice++ --> EnergyStorage.fromEnergySubsystem2Bat[i];
	}

	// manager <--> supercaps connections
	for i = 0..EnergyStorage.numSupercaps-1 {
		EnergyManager.toStorageDevice++ --> EnergyStorage.fromEnergySubsystem2Sup[i];
	}

	// manager <--> rechargeable-batteries connections
	for i = 0..EnergyStorage.numRechBatteries-1{
		EnergyManager.toStorageDevice++ --> EnergyStorage.fromEnergySubsystem2RBat[i];
	}


	// direct messages connection 
	powerConsumption --> EnergyManager.powerConsumption;

	// manager <--> extern-modules connections
	EnergyManager.toSensorDevManager --> toSensorDevManager;
	EnergyManager.toApplication --> toApplicationModule;
	EnergyManager.toNetwork --> toNetworkModule;
	EnergyManager.toMac --> toMacModule;
	EnergyManager.toRadio --> toRadioModule;
	EnergyManager.toEnergyPredictor --> EnergyPrediction.fromEnergyManager if PredictorType != "";
	EnergyManager.toResourceManager --> toResourceManager;
}

