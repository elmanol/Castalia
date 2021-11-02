//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "SolarCell.h"

Define_Module(SolarCell);

void SolarCell::initialize() {

	VirtualEnergyHarvester::initialize();

	/* read solar cell parameters */
	size = (double)par("size");
	cellEfficiency = (double)par("cellEfficiency");

	if ( size < 0 )
		opp_error("[SolarCell] Invalid value of parameter \"size\": must be positive or zero");
	if ( cellEfficiency < 0.0 || cellEfficiency > 1.0 )
		opp_error("[SolarCell] Invalid value of parameter \"cellEfficiency\": must be in range [0,1]");

	// convert size from cm^2 to m^2
	size *= .0001;
}

void SolarCell::sourceChanged(double sourceValue, double efficiencyValue){

	if ( sourceValue < 0.0 || currentHarvestingPower < 0.0 || efficiencyValue < 0.0 || harvestingEfficiency < 0.0 )
		opp_error("[SolarCeall] Harvesting power cannot be negative");

	double oldHarvestingPower = currentHarvestingPower;
	currentHarvestingPower = sourceValue * efficiencyValue * size * cellEfficiency * 1000.;	// W -> mW
	if ( maxHarvestingPower > 0 )
		currentHarvestingPower = std::min(currentHarvestingPower, maxHarvestingPower);

	trace() << "Harvesting power changed: from " << oldHarvestingPower
		<< " mW to " << currentHarvestingPower << " mW";

	harvestingChangedMsg = new ResourceManagerHarvestingMessage("Harvesting rate changed message",
			ENERGY_SUBSYSTEM_HARVESTING_RATE_CHANGED);
	harvestingChangedMsg->setHarvestingPower( currentHarvestingPower );
	send(harvestingChangedMsg, "toEnergySubsystem");
}
