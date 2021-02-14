//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef VIRTUAL_ENERGY_SOURCE
#define VIRTUAL_ENERGY_SOURCE

#include <string>
#include "CastaliaModule.h"

class VirtualEnergySource : public CastaliaModule {
	public:
		virtual void initialize();				

	protected:
		string description;

		virtual void handleMessage(cMessage* msg) {};
		virtual void handleControlCommand(cMessage* msg) {};
		virtual void finishSpecific() {};	
};

#endif
