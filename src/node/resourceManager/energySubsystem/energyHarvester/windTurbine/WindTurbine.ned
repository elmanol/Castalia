//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyHarvester.windTurbine;

// Very simple model for a micro wind turbine harvesting energy from a TraceEnergySource
// IMPORTANT: assume that the corresponding TraceEnergySource emits wind speed value in unit m/s

// NOTE: this implementation does not take power conversion efficiency into account

simple WindTurbine like node.resourceManager.energySubsystem.energyHarvester.iEnergyHarvester
{
 parameters:
	bool collectTraceInfo = default(false);	

	// data source type for the device
	string sourceType = "Wind";

	// max harvesting power (hardware limit)
	double maxHarvestingPower = default(-1);	// mW

	// air density (in kg / m^3)
	double airDensity = default(1.225); // kg / m^3

	// rotor diameter (in cm)
	double rotorDiameter = default(5); // cm

	// powerCoefficient: ratio of the electrical energy over the kinetic energy of the wind 
	// crossing the area swept by the wind turbine
	//
	// The theoretical maximum power coefficient for a micro wind turbine having a rotor-tip-diameter 
	// of less than 10 cm and a direct drive generator without a gearbox are limited to 0.148
	// (from: "Feasibility Study of Micro-Wind Turbines for Powering Wireless Sensors on a Cable-Stayed Bridge", 2012)
    double powerCoefficient = default(0.1); 
	
	// time-varying harvesting efficiency -- depends on dust, aging, obstructions, ecc 
	string efficiencyFile = default("");

	// if defined, ignore energy source and read values directly from file
	// useful to feed an harvester with a specific trace collected in real-life deployments
	string harvesterTraceFile = default("");

 gates:
	output toEnergySubsystem;
}

