//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyStorage;

module EnergyStorageModule
{
parameters:
	int numBatteries     = default(1);
	int numSupercaps     = default(0);
	int numRechBatteries = default(0);

	string batteryType     = default("Battery");
	string supercapType    = default("Supercapacitor");
	string rechBatteryType = default("RechargeableBattery");


gates:
	input fromEnergySubsystem2Bat[numBatteries];
	input fromEnergySubsystem2Sup[numSupercaps];
	input fromEnergySubsystem2RBat[numRechBatteries];


submodules:
	// batteries vector
	Batteries[numBatteries]: <batteryType> like node.resourceManager.energySubsystem.energyStorage.iEnergyStorage if numBatteries > 0;

	// supercaps vector
	Supercapacitors[numSupercaps]: <supercapType> like node.resourceManager.energySubsystem.energyStorage.iEnergyStorage if numSupercaps > 0;

	// rechargeable batteries vector
	RechBatteries[numRechBatteries]: <rechBatteryType> like node.resourceManager.energySubsystem.energyStorage.iEnergyStorage if numRechBatteries > 0;

connections:
	// storage --> batteries connections
	for i=0..numBatteries-1
	{
		fromEnergySubsystem2Bat[i] --> Batteries[i].fromEnergySubsystem;
	}

	// storage --> supercaps connections
	for i=0..numSupercaps-1
	{
		fromEnergySubsystem2Sup[i] --> Supercapacitors[i].fromEnergySubsystem;
	}

	// storage --> rechargeable-batteries connections
	for i=0..numRechBatteries-1
	{
		fromEnergySubsystem2RBat[i] --> RechBatteries[i].fromEnergySubsystem;
	}
}
