//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef VIRTUALENERGYHARVESTER
#define VIRTUALENERGYHARVESTER

#include "CastaliaModule.h"

enum {
	ENERGY_SUBSYSTEM_HARVESTING_RATE_CHANGED = 60,
	EFFICIENCY_CHANGED,
	TRACE_CHANGED,
};

class VirtualEnergyHarvester : public CastaliaModule, cListener {

	public:
		string getDataSourceType() const     { return sourceType; }
		double getCurHarvestingPower() const { return currentHarvestingPower; } // mW
		double getMaxHarvestingPower() const { return maxHarvestingPower > 0 ? maxHarvestingPower : 0.0; }
		double getHarvestingFrac() const { return maxHarvestingPower > 0 ? currentHarvestingPower / maxHarvestingPower : 0; }

	protected:
		string sourceType;

		double currentHarvestingPower;	// mW
		double maxHarvestingPower;
		double harvestingEfficiency;

		double sourceValue;
		
		unsigned nodeId;
		cMessage* efficiencyChangedMsg;
		cMessage* traceChangedMsg;

		ResourceManagerHarvestingMessage *harvestingChangedMsg;

		string signalName;
		ostringstream signalNameFileES;

		string traceFileName;
		vector< pair <double, double> > traceValues;
		vector< pair <double, double> >::iterator currentTraceEntry;

		string efficiencyFileName;
		vector< pair <double, double> > efficiencyValues;
		vector< pair <double, double> >::iterator currentEfficiencyEntry;

		void parseEfficiencyFile();
		void parseTraceFile();
		void receiveSignal(cComponent *src, simsignal_t id, double l);

		virtual void sourceChanged(double _newPower, double _newEfficiency) = 0;

		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void handleControlMessage(cMessage* msg) {};
		virtual void finishSpecific();
};

#endif
