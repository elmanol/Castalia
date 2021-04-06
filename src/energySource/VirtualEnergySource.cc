//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "VirtualEnergySource.h"

void VirtualEnergySource::initialize() {

	description = par("description").stdstringValue();

	if ( description.empty() )
		opp_error("[Energy Source]: Invalid value of parameter 'description', must be not empty.");
}

