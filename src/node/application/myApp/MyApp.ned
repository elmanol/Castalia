package node.application.myApp;

// The sensor node module. Connects to the wireless channel in order to communicate 
// with other nodes. Connects to psysical processes so it can sample them.

simple MyApp like node.application.iApplication {
 parameters:
 	string applicationID = default ("myApp");
	bool collectTraceInfo = default (true);
	int priority = default (1);
	int packetHeaderOverhead = default (8);	// in bytes
	int constantDataPayload = default (2);	// in bytes
	int sampleInterval = default (1000);	// in ms
	int packetSpacing = default (100);	// in ms

	double delayLimit = default (0); 			// application delay limit (0 - no limit)
	double packet_rate = 5;	// packets per second, by default we transmit no packets
	double startupDelay = default (1);	// delay in seconds before the app starts producing packets
	double getNeighboursDelay = default (1);	// / time till the node gets its neighbours info

	bool isSink = default (false);
	string recipientAddress = default ("0");	//this can also be set to "-1" for broadcast
	

 gates:
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}

