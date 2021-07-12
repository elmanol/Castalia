//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef SOLAR_CELL_H
#define SOLAR_CELL_H

/* A solar cell connected to a TraceEnergySource reading irradiance levels from file */

#include "VirtualEnergyHarvester.h"

class SolarCell : public VirtualEnergyHarvester {

	protected:
		double size;
		double cellEfficiency;

		void initialize();
		void sourceChanged(double _newPower, double _newEfficiency);
};

#endif	// SOLAR_CELL_H
