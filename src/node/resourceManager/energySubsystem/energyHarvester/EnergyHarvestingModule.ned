//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package node.resourceManager.energySubsystem.energyHarvester;

module EnergyHarvestingModule
{
parameters:
	int numEnergyHarvesters = default(0);

gates:
	output toEnergySubsystem[numEnergyHarvesters];

submodules:
	// harvesters vector
	Harvesters[numEnergyHarvesters]: <default("TraceHarvester")> like 
		node.resourceManager.energySubsystem.energyHarvester.iEnergyHarvester if numEnergyHarvesters > 0;

	// Now the submodule type name is expected to be defined via typename pattern assignments

connections:
	// harvesting --> harvesters connections
	for i=0..numEnergyHarvesters-1
	{
		toEnergySubsystem[i] <-- Harvesters[i].toEnergySubsystem;
	}
}
