//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package energySource.traceEnergySource;

simple TraceEnergySource like energySource.iEnergySource
{
parameters:
	bool collectTraceInfo = default(false);
	string description = default("");

	string traceFile = default("");

	// trace file time offset
	// this value will be addedd/subtracted from trace timestamps
	// resulting negative timestamps and corresponding values will be discarded
	double timeOffset = default(0.0);
}

