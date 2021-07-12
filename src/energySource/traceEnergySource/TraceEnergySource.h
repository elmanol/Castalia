//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef TRACE_ENERGY_SOURCE
#define TRACE_ENERGY_SOURCE

#include "VirtualEnergySource.h"

enum TraceEnergySourceTimers {
	TRACE_VALUE_CHANGED = 1,
};

class TraceEnergySource : public VirtualEnergySource
{
	public:
		void initialize();

	protected:
		const char* traceFileName;
		vector< pair <double, double> > traceValues;
		vector< pair <double, double> >::iterator currentEntry;
		double timeOffset;

		string signalName;

		void timerFiredCallback(int index);
		void handleMessage(cMessage* msg);
		void finishSpecific();	

	private:
		void parseTraceFile();		
};



#endif
