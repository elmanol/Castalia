//****************************************************************************
//*  Copyright: National ICT Australia,  2007 - 2010                         *
//*  Developed at the ATP lab, Networked Systems research theme              *
//*  Author(s): Athanassios Boulis, Dimosthenis Pediaditakis                 *
//*  This file is distributed under the terms in the attached LICENSE file.  *
//*  If you do not find this file, copies can be found by writing to:        *
//*                                                                          *
//*      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
//*      Attention:  License Inquiry.                                        *
//*                                                                          *  
//****************************************************************************/

package node.application.myApp;

// The sensor node module. Connects to the wireless channel in order to communicate 
// with other nodes. Connects to psysical processes so it can sample them.

simple myApp like node.application.iApplication {
 parameters:
 	string applicationID = default ("myApp");
	bool collectTraceInfo = default (true);
	int priority = default (1);
	int packetHeaderOverhead = default (8);	// in bytes
	int constantDataPayload = default (2);	// in bytes
	int sampleInterval = default (1000);	// in ms
	int packetSpacing = default (100);	// in ms

	double packet_rate = default (0);	// packets per second, by default we transmit no packets
	double delayLimit = default (0); 			// application delay limit (0 - no limit)
	double packet_rate = default (0);	// packets per second, by default we transmit no packets
	double startupDelay = default (0);	// delay in seconds before the app starts producing packets

	bool isSink = default (false);
	string recipientAddress = default ("0");	//this can also be set to "-1" for broadcast
	

 gates:
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}

