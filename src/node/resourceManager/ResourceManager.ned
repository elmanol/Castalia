//********************************************************************************
//*  Copyright: National ICT Australia,  2007 - 2010                             *
//*  Developed at the ATP lab, Networked Systems research theme                  *
//*  Author(s): Athanassios Boulis, Dimosthenis Pediaditakis, Yuriy Tselishchev  *
//*  This file is distributed under the terms in the attached LICENSE file.      *
//*  If you do not find this file, copies can be found by writing to:            *
//*                                                                              *
//*      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                 *
//*      Attention:  License Inquiry.                                            *
//*                                                                              *
//*******************************************************************************/

//********************************************************************************
//*  Modified for GreenCastalia integration					 *
//*  Modification date: 07/01/2013                                               *
//********************************************************************************
//*  Copyright (C): Dora Spenza, David Benedetti, 2013                           *
//*  Author(s): Dora Spenza, David Benedetti                                     *
//*  Developed at Computer Science Department, Sapienza University of Rome       *
//*  This file is distributed under the terms in the attached LICENSE_GC file.   *
//*******************************************************************************/

package node.resourceManager;

module ResourceManager {
	parameters:
		bool collectTraceInfo = default (false);

		// baseline power consumption of the node, in mW
		double baselineNodePower = default (6);	
		
		// maximum interval for periodic energy calculation, in msec
		double periodicEnergyCalculationInterval = default (1000);

		// minimum operating voltage in V
		double cutOffVoltage = default(2.1); // Telos Rev B datasheet

	gates:
		output toSensorDevManager;
		output toApplication;
		output toNetwork;
		output toMac;
		output toRadio;
		input powerConsumption @directIn; 

	submodules:
		// resource manager module
		ResourceManager: node.resourceManager.resourceManager.ResourceManager;

		// energy subsystem module
		EnergySubsystem: node.resourceManager.energySubsystem.EnergySubsytemModule;

	connections:

		 toSensorDevManager <-- EnergySubsystem.toSensorDevManager;
		 toApplication <-- EnergySubsystem.toApplicationModule;
		 toNetwork <-- EnergySubsystem.toNetworkModule;
		 toMac <-- EnergySubsystem.toMacModule;
		 toRadio <-- EnergySubsystem.toRadioModule;
		 powerConsumption --> EnergySubsystem.powerConsumption;
		 ResourceManager.fromEnergyManager <-- EnergySubsystem.toResourceManager;
}

