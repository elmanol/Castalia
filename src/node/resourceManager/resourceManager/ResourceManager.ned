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
//*  Modified for GreenCastalia integration									     *
//*  Modification date: 07/01/2013                                               *
//********************************************************************************
//*  Copyright (C): Dora Spenza, David Benedetti, 2013                           *
//*  Author(s): Dora Spenza, David Benedetti                                     *
//*  Developed at Computer Science Department, Sapienza University of Rome       *
//*  This file is distributed under the terms in the attached LICENSE_2 file.    *
//*******************************************************************************/

package node.resourceManager.resourceManager;

simple ResourceManager {
parameters:
	bool collectTraceInfo = default (false);
	double ramSize = default (0.0);			//in kB
	double flashSize = default (0.0);		//in kB
	double flashWriteCost = default (0.0);	//per kB
	double flashReadCost = default (0.0);	//per kB
	double imageSize = default (0.0);		//the space that the OS (e.g. Contiki or TinyOS) occupies in the flash

	string cpuPowerSpeedLevelNames = default ("");
	string cpuPowerPerLevel = default ("");	//spent energy per time unit
	string cpuSpeedPerLevel = default ("");
	int cpuInitialPowerLevel = default (-1);	// index for the cpuPowerLevels array
	double sigmaCPUClockDrift = default (0.00003);	// the standard deviation of the Drift of the CPU

gates:
	input fromEnergyManager;
}

