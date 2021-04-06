//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef BATTERY
#define BATTERY

#include "VirtualEnergyStorage.h"

class Battery : public VirtualEnergyStorage {
	public:
		double getMAmpereHour() const		{ return mAmpereHour; }
		std::pair<double, double> charge(double amount) {
			opp_error("Primary batteries can not be charged");
			return std::make_pair(0.0, 0.0);
		}
		bool isChargeable() const { return false; };

	protected:

		// mAh for the battery
		double mAmpereHour;

		// leakage model
		double energyLeakageModel();
		
		// battery type: ideal or empirical
		BatteryType bt;

		string empiricalDischargeFile;
		// frozen set, vector faster than a map
		std::vector < std::pair <double, PiecewiseCoefficients > > empiricalDischarge;
		std::pair <double, PiecewiseCoefficients > curV;

		double getVoltage();

		void initialize();
		void handleMessage(cMessage* msg) {};
		void handleControlCommand(cMessage* msg) {};
};



#endif
