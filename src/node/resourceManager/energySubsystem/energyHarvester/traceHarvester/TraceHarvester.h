//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef TRACE_HARVESTER_H
#define TRACE_HARVESTER_H

/* An harvester receiving signals from a TraceEnergySource */

#include "VirtualEnergyHarvester.h"

class TraceHarvester : public VirtualEnergyHarvester {

	protected:
		void sourceChanged(double _newPower, double _newEfficiency);
};



#endif
