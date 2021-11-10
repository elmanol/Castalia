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

package node.communication.routing.eamultipathRingsRouting;

simple EAmultipathRingsRouting like node.communication.routing.iRouting {
 parameters:

 	double energyMetricPercentage = default(80);
 	double rssiMetricPercentage = default(20);
	bool collectTraceInfo = default (false);
	int distanceThreshold = default (8);
	int maxNetFrameSize = default (0);					// bytes, 0 means no limit
	int netBufferSize = default (32);					// number of messages
	int netDataFrameOverhead = default (14);			// bytes
	int mpathRingsSetupFrameOverhead = default (13);	// bytes
	double startupDelay = default (0);					// sec
	double netSetupTimeout = default (0.5);					// sec
	int collectBatteryTimer = default (1800);					// sec
	int sendEnergyTimer = default (120);					// sec
	int rssiThreshold = default(-120);

 gates:
	output toCommunicationModule;
	output toMacModule;
	input fromCommunicationModule;
	input fromMacModule;
	input fromCommModuleResourceMgr;
}

