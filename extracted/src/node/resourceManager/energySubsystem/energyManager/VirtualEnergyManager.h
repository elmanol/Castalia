//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef VIRTUALENERGYMANAGER
#define VIRTUALENERGYMANAGER

#include <limits>      
#include <string>
#include <map>

#include "CastaliaModule.h"

#include "VirtualEnergyHarvester.h"
#include "VirtualEnergyStorage.h"

enum VirtualVirtualEnergyStorageTimers
{
	PERIODIC_ENERGY_CALCULATION = 16,
};

class VirtualEnergyManager: public CastaliaModule {
	public:
		// total amount of harvested energy in Joules 
		double getTotEnergyHarvested() const { return totEnergyHarvested; }	
		// total amount of supplied energy in Joules
		double getTotEnergySupplied() const  { return totEnergySupplied; }
		// total amount of leaked energy in Joules
		double getTotEnergyLeaked() const    { return totEnergyLeaked; }

		double getCurrentEnergyRatio() const { return remainingEnergy / maximumEnergy; }
		double getMaxHarvestingPower() const { return maxHarvestingPower; }
		double getCurrentHarvestingPower() const { return harvestingPowerRate; }

		// true if the node is experiencing an energy peak
		bool isAtPeak(double energyThreshold) const { 
			return ( harvestingPowerRate >= nodePowerConsumption) && 
				( getUsableEnergyRatio() >= energyThreshold);
		}

		double estimateLifetime(void){
			return ((initialEnergy * simTime().dbl()) / ((initialEnergy - remainingEnergy) * 86400.0));
		}

	protected:
		// storage devices
		std::vector<VirtualEnergyStorage*> storageDevices;

		std::map<long, double> storedPowerConsumptions;
		std::map<long, double> storedHarvestingPowerRates;

		// harvesting/storage frequency updates
		double periodicEnergyCalculationInterval;
		// time of last energy update
		simtime_t timeLastUpdate;
		// simulation end time	
		simtime_t simulationEnd;

		double maxHarvestingPower;

		// remaining energy (sum of energy stored in storage devices) 
		double remainingEnergy;	// J

		// maximum amount of energy that the node can store 
		double maximumEnergy; // J

		simtime_t disabledTime;

		double totEnergyHarvested;
		double totEnergySupplied;
		double totEnergyLeaked;
		// energy wasted due to storages being full during energy-harvesting periods
		double totEnergyWasted;

		cMessage* energyMsg;

		// current harvesting power (mW)
		double harvestingPowerRate;

		// periodic energy consumption of node (mW)
		double baselineNodePower;

		// amount of current node power (mW)
		double nodePowerConsumption;

		// initial node energy (J)
		double initialEnergy;

		unsigned nodeId;
		ofstream debugFile;
		bool disabled;

		// true if a NODE_STARTUP message has been received from application layer
		bool startupReceived;

		bool useEnergyPredictor;

		virtual double getUsableEnergy() const = 0;
		double getUsableEnergyRatio() const { return getUsableEnergy() / maximumEnergy; }
		// check if storage devices can supply the amount of energy 'energyNeeded'
		bool canSupply(double energyNeeded) { return getUsableEnergy() >= energyNeeded; }

		virtual double chargeStorages(double amount) = 0;
		virtual double dischargeStorages(double amount) = 0;

		// energy leakage of storage devices
		double computeEnergyLeakage();

		void switchOnNode();
		void switchOffNode();
		void destroyNode();

		virtual void initialize();
		virtual void handleMessage(cMessage* msg) {};
		virtual void handleControlCommand(cMessage* msg) {};	
		virtual void finishSpecific();

};

#endif
