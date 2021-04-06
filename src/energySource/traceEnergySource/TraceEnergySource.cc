//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "TraceEnergySource.h"

Define_Module(TraceEnergySource);

void TraceEnergySource::initialize() {

	VirtualEnergySource::initialize();

	timeOffset = (double) par("timeOffset");

	traceFileName  = par("traceFile").stringValue();
	if( !strcmp(traceFileName, "") )
		opp_error("[TraceEnergySource] Invalid value of parameter 'traceFileName', must be not empty.");
	
	signalName = "sourceChanged-" + description;

	parseTraceFile();
}

void TraceEnergySource::handleMessage(cMessage* msg) {
	switch (msg->getKind()) {

		case TRACE_VALUE_CHANGED:
			{
				/* Notify change to listening harvesters */	
				emit(registerSignal(signalName.c_str()), currentEntry->second );
				++currentEntry;

				if ( currentEntry != traceValues.end()  ) {
					scheduleAt( currentEntry->first, new cMessage("Trace value changed message", TRACE_VALUE_CHANGED) );
				}

				break;
			}

		default:
			opp_error("Unknown message received");
			break;
	}
				
	delete msg;
}

void TraceEnergySource::parseTraceFile() {

	// open trace file 
	ifstream srcFile(traceFileName, ios::in);
	if ( !srcFile.is_open() )
		opp_error("[TraceEnergySource] Unable to open trace file %s", traceFileName );

	trace() << "Using trace file '" << traceFileName << "' with time offset: " << timeOffset;

	// Get simulation time limit in seconds
	double simTimeLimit = SIMTIME_DBL( SimTime::parse( ev.getConfig()->getConfigValue("sim-time-limit") ) );
	int currentLine = 0;
	string line;
	
	double prevTimestamp = -1;
	double currentValue = -1;
	double currentTimestamp = -1;

	while ( std::getline(srcFile, line) ) {
		++currentLine;

		// Skip comments and empty lines
		if ( line.empty() || *(line.begin()) == '#' )
			continue;

		std::istringstream ss(line);
		if ( ! ( ss >> currentTimestamp >> currentValue >> ws ) )
			opp_error("[TraceEnergySource] Bad file format %s: trace file format must be <timestamp> <value>", 
					traceFileName);

		currentTimestamp += timeOffset;

		if ( currentTimestamp < 0.0 )
			// negative timestamps and corresponding values are discarded
			continue;

		if ( currentTimestamp > simTimeLimit )
			// sim-time-limit reached, stop parsing 
			break;

		if ( currentTimestamp < 0 || currentValue < 0 )
			opp_error("[TraceEnergySource] Bad file format %s at line %d: negative value found", 
					traceFileName, currentLine );

		if ( currentTimestamp <= prevTimestamp ) 
			opp_error("[TraceEnergySource] Bad file format %s at line %d: timestamp values must be monotonically increasing", 
					traceFileName, currentLine );

		// Add new value
		if ( traceValues.empty() || currentValue != traceValues.back().second )
			traceValues.push_back( make_pair(currentTimestamp, currentValue ) );

		prevTimestamp = currentTimestamp;
	}

	srcFile.close ();

	currentEntry = traceValues.begin();
	if ( !traceValues.empty() )
		scheduleAt( currentEntry->first, new cMessage("Trace value changed message", TRACE_VALUE_CHANGED ) );
	else {
		trace() << "Trace value is always zero, no event scheduled";
	}
}

void TraceEnergySource::finishSpecific() {
	traceValues.clear();
}

