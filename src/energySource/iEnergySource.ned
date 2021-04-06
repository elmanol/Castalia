//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

package energySource;

// The energy source module simulates a physical power source from which harvester devices 
// on the nodes gather energy.

moduleinterface iEnergySource
{
	parameters:
		
		bool collectTraceInfo;
		string description;
}

