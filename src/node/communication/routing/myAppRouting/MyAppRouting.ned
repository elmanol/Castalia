package node.communication.routing.myAppRouting;

simple MyAppRouting like node.communication.routing.iRouting {
 parameters:
	bool collectTraceInfo = default (false);
	int netBufferSize = default (32);					// number of messages
	int netDataFrameOverhead = default (14);			// bytes
	int netSetupTimeout = default (50);					// msec
	int startupDelay = default (50);	
	int maxNetFrameSize = default (0);					// bytes, 0 means no limit

 gates:
	output toCommunicationModule;
	output toMacModule;
	input fromCommunicationModule;
	input fromMacModule;
	input fromCommModuleResourceMgr;
}

