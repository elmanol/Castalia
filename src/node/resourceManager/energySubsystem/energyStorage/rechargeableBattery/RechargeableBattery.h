//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef RECHARGEABLEBATTERY
#define RECHARGEABLEBATTERY 

#include "VirtualEnergyStorage.h"

using namespace std;

typedef enum
{
	RBATTERY_NULL = 0,
	RBATTERY_CHARGE,
	RBATTERY_DISCHARGE
}OpType;

class RechargeableBattery : public VirtualEnergyStorage
{
	public:
		double getMAmpereHour() const		{ return mAmpereHour; }
		double getChargeEfficiency() const 	{ return chargingEfficiency; }
		unsigned getCycleLife() const 		{ return cycleLife; }
		unsigned getCurNChDischCycles() const 	{ return numCycles; }

		std::pair<double, double> discharge(double amount);
		std::pair<double, double> charge(double amount);
	
		bool isChargeable() const { return true; }

	protected:
		// milli Ampere / hour for the battery
		double mAmpereHour;
		// last operation 
		OpType lastOperation;
		// battery maximum number of charge/discharge cycles 
		unsigned cycleLife;
		// battery current number of charge/discharge cycles 
		unsigned numCycles;

		// battery is dead after the maximum number of charge/discharge cycles has been reached
		bool deadBattery;

		// model by means of which storage device leak energy (it can be overwritten with a different leakage model!)
		double energyLeakageModel();

		BatteryType bt;

		// frozen set, vector faster than a map
		std::vector < std::pair <double, PiecewiseCoefficients > > empiricalDischarge;
		std::pair <double, PiecewiseCoefficients > curV;

		double getVoltage();
		void updateStatus();

		void initialize();
		void handleMessage(cMessage* msg) {}
		void handleControlCommand(cMessage* msg) {}
};

#endif
