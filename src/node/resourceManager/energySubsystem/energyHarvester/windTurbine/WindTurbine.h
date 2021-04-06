//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef WIND_TURBINE_H
#define WIND_TURBINE_H

/* A wind turbine receiving signals from a TraceEnergySource reading wind speed from file */

#include "VirtualEnergyHarvester.h"

class WindTurbine : public VirtualEnergyHarvester {
#if __cplusplus > 199711L
	static constexpr double BetzLimit = .5925925925;
#else
	static const double BetzLimit = .5925925925;
#endif

	protected:
		double airDensity;
		double rotorDiameter;
		double powerCoefficient;
		double multFact;

		void initialize();
		void sourceChanged(double _newPower, double _newEfficiency);
};

#endif	// WIND_TURBINE_H
