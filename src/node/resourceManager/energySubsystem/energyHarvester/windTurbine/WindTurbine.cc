//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "WindTurbine.h"

Define_Module(WindTurbine);

void WindTurbine::initialize() {

	VirtualEnergyHarvester::initialize();

	/* read wind turbine parameters */
	airDensity = (double)par("airDensity");
	rotorDiameter = (double)par("rotorDiameter");
	powerCoefficient = (double)par("powerCoefficient");

	if ( airDensity < 0 )
		opp_error("[WindTurbine] Invalid value of parameter \"airDensity\": must be positive or zero");
	if ( rotorDiameter < 0 )
		opp_error("[WindTurbine] Invalid value of parameter \"rotorDiameter\": must be positive or zero");
	if ( powerCoefficient < 0.0 || powerCoefficient > BetzLimit )
		opp_error("[WindTurbine] Invalid value of parameter \"powerCoefficient\": must be in range [0,0.5926]");

	// compute area in m^2
	double area = pow(rotorDiameter * 0.005, 2) * M_PI;
	multFact = area * 0.5 * airDensity * powerCoefficient;
}

void WindTurbine::sourceChanged(double sourceValue, double efficiencyValue){

	if ( sourceValue < 0.0 || currentHarvestingPower < 0.0 || efficiencyValue < 0.0 || harvestingEfficiency < 0.0 )
		opp_error("[WindTurbine] Harvesting power cannot be negative");

	double oldHarvestingPower = currentHarvestingPower;
	currentHarvestingPower = efficiencyValue * multFact * pow(sourceValue, 3) * 1000; // W -> mW
	if ( maxHarvestingPower > 0 )
		currentHarvestingPower = std::min(currentHarvestingPower, maxHarvestingPower);

	trace() << "Harvesting power changed: from " << oldHarvestingPower
		<< " mW to " << currentHarvestingPower << " mW";

	harvestingChangedMsg = new ResourceManagerHarvestingMessage("Harvesting rate changed message",
			ENERGY_SUBSYSTEM_HARVESTING_RATE_CHANGED);
	harvestingChangedMsg->setHarvestingPower( currentHarvestingPower );
	send(harvestingChangedMsg, "toEnergySubsystem");
}
