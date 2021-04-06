//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef SUPERCAPACITOR
#define SUPERCAPACITOR

#include "VirtualEnergyStorage.h"

typedef enum {
	LEAKAGE_NONE,
	LEAKAGE_CONSTANT,
	LEAKAGE_EXPONENTIAL,
	LEAKAGE_PIECEWISE
} leakageModel_t;

class Supercapacitor : public VirtualEnergyStorage {

	public:
		double getCapacitance() const 		{ return capacitance; }
		bool isChargeable() const { return true; }

		double getConstantLeakageCurrent() const { 
			return constLeakageCurrent; 
		}    

	protected:
		// supercapacitor maximum capacitance (F)
		double capacitance;

		// supercapacitor constant leakage (mA)
		double constLeakageCurrent;
		double P_0;
		double alpha;

		// model by means of which storage device leak energy (it can be overwritten with a different leakage model!)
		double energyLeakageModel();

		leakageModel_t leakageModel;

		double getVoltage(){
			return sqrt(2 * curEnergy / capacitance);
		}

		void initialize();
		void handleMessage(cMessage* msg) {};
		void handleControlCommand(cMessage* msg) {};
};



#endif
