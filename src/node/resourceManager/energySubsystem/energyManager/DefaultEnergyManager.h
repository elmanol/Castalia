//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef ENERGY_MANAGER
#define ENERGY_MANAGER

#include "VirtualEnergyManager.h"

class DefaultEnergyManager : public VirtualEnergyManager {

	public:
		void updateEnergy();

	protected:
		void handleMessage(cMessage* msg);	
		void handleControlCommand(cMessage* msg) {};		

		double chargeStorages(double amount);
		double dischargeStorages(double amount);
		double getUsableEnergy() const;
		bool checkNodeOnOff();

		void finishSpecific();
};

#endif
