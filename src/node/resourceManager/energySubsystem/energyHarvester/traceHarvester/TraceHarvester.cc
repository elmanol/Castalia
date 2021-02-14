//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "TraceHarvester.h"

Define_Module(TraceHarvester);

void TraceHarvester::sourceChanged(double sourceValue, double efficiencyValue){

	if ( sourceValue < 0.0 || currentHarvestingPower < 0.0 || efficiencyValue < 0.0 || harvestingEfficiency < 0.0 )
		opp_error("[TraceHarvester] Harvesting power cannot be negative");

	double oldHarvestingPower = currentHarvestingPower;
	currentHarvestingPower = sourceValue * efficiencyValue;
	if ( maxHarvestingPower > 0 )
		currentHarvestingPower = std::min(currentHarvestingPower, maxHarvestingPower);

	trace() << "Harvesting power changed: from " << oldHarvestingPower 
		<< " mW to " << currentHarvestingPower << " mW";

	harvestingChangedMsg = new ResourceManagerHarvestingMessage("Harvesting rate changed message",
			ENERGY_SUBSYSTEM_HARVESTING_RATE_CHANGED);
	harvestingChangedMsg->setHarvestingPower( currentHarvestingPower );
	send(harvestingChangedMsg, "toEnergySubsystem");
}
