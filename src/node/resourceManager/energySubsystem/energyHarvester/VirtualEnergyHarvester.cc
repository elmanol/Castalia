//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "VirtualEnergyHarvester.h"

void VirtualEnergyHarvester::initialize() {

	sourceType = par("sourceType").stringValue();		
	maxHarvestingPower = (double)par("maxHarvestingPower");

	// parameters check
	if( ! sourceType.length() )
		opp_error("[VirtualEnergyHarvester] Invalid value of parameter \"sourceType\", must be not empty");

	// get node id
	cModule* node = check_and_cast<cModule*>(getParentModule()->getParentModule()->getParentModule()->getParentModule());
	nodeId = (unsigned)(node->getIndex());

	sourceValue = 0.0;
	currentHarvestingPower = 0.0;
	harvestingEfficiency = 1.0;

	efficiencyChangedMsg = NULL;
	efficiencyFileName = par("efficiencyFile").stdstringValue();
	if ( !efficiencyFileName.empty() )
		parseEfficiencyFile();
	
	traceChangedMsg = NULL;
	traceFileName = par("harvesterTraceFile").stdstringValue();
	if ( !traceFileName.empty() )
		parseTraceFile();
	else {
		/* receive updates from energy source */
		signalName = "sourceChanged-" + sourceType;
		simulation.getSystemModule()->subscribe(signalName.c_str(), this) ;
	}
}

void VirtualEnergyHarvester::receiveSignal(cComponent *src, simsignal_t id, double _newValue){

	Enter_Method("VirtualEnergyHarvester::receiveSignal"); 

	if( (registerSignal(signalName.c_str()) == id) || ( registerSignal(signalNameFileES.str().c_str()) == id ) ){
		sourceChanged(_newValue, harvestingEfficiency);
	}
	else 
		opp_error("Unknown signal") ;	
}

void VirtualEnergyHarvester::handleMessage(cMessage* msg) {

	switch (msg->getKind()) {

		case EFFICIENCY_CHANGED:
			{
				trace() << "Harvesting efficiency changed to " << currentEfficiencyEntry->second;
				sourceChanged( sourceValue, currentEfficiencyEntry->second );
				harvestingEfficiency = currentEfficiencyEntry->second;

				if ( ++currentEfficiencyEntry != efficiencyValues.end()  ) {
					scheduleAt( currentEfficiencyEntry->first, efficiencyChangedMsg);
				}

				return; // do not delete efficiencyChanged message
			}

		case TRACE_CHANGED:
			{
				trace() << "Harvesting trace value changed to " << currentTraceEntry->second;
				sourceChanged( currentTraceEntry->second, harvestingEfficiency );
				sourceValue = currentTraceEntry->second;

				if ( ++currentTraceEntry != traceValues.end()  ) {
					scheduleAt( currentTraceEntry->first, traceChangedMsg);
				}

				return; // do not delete traceChanged message
			}

		default:
			{
				opp_error("Unknown message received");
				break;
			}
	}

	delete msg;
}

void parseFile(string fileName, vector< pair <double, double> >& values, bool parsingEfficiency){

	// open file
	ifstream srcFile(fileName.c_str(), ios::in);
	if ( !srcFile.is_open() )
		opp_error("[VirtualEnergyHarvester]: Unable to open file %s", fileName.c_str() );

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
			opp_error("[VirtualEnergyHarvester]: Bad file format %s", fileName.c_str());

		if ( currentTimestamp > simTimeLimit )
			// sim-time-limit reached, stop parsing
			break;

		if ( currentTimestamp < 0 || currentValue < 0 )
			opp_error("[VirtualEnergyHarvester]: Bad file format %s, negative values at line %d",
					fileName.c_str(), currentLine );

		if ( parsingEfficiency && currentValue > 1.0 )
			opp_error("[VirtualEnergyHarvester]: Bad file format %s, efficiency greater than 1.0 at line %d",
					fileName.c_str(), currentLine );

		if ( currentTimestamp <= prevTimestamp )
			opp_error("[VirtualEnergyHarvester]: Bad file format %s, timestamp values must be increasing",
					fileName.c_str() );

		// Add new value
		if ( values.empty() || currentValue != values.back().second )
			values.push_back( make_pair(currentTimestamp, currentValue ) );

		prevTimestamp = currentTimestamp;
	}

	srcFile.close ();
}

void VirtualEnergyHarvester::parseEfficiencyFile() {

	parseFile(efficiencyFileName, efficiencyValues, true);

	currentEfficiencyEntry = efficiencyValues.begin();
	if ( !efficiencyValues.empty() ) {
		efficiencyChangedMsg = new cMessage("Efficiency changed message", EFFICIENCY_CHANGED );
		scheduleAt( currentEfficiencyEntry->first, efficiencyChangedMsg );
	}
}

void VirtualEnergyHarvester::parseTraceFile() {

	parseFile(traceFileName, traceValues, false);

	currentTraceEntry = traceValues.begin();
	if ( !traceValues.empty() ) {
		traceChangedMsg = new cMessage("Trace changed message", TRACE_CHANGED );
		scheduleAt( currentTraceEntry->first, traceChangedMsg );
	}
}

void VirtualEnergyHarvester::finishSpecific() {
	efficiencyValues.clear();

	if ( efficiencyChangedMsg != NULL )
		cancelAndDelete( efficiencyChangedMsg );
	if ( traceChangedMsg != NULL )
		cancelAndDelete( traceChangedMsg );
}
