//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#ifndef VIRTUALENERGYSTORAGE
#define VIRTUALENERGYSTORAGE

#include "ResourceManager.h"
#include "CastaliaModule.h"

enum BatteryType{
	BATTERY_IDEAL = 1,
	BATTERY_EMPIRICAL = 2,
};

typedef std::pair<double, double> PiecewiseCoefficients;

class Battery;
class Supercapacitor;
class RechargeableBattery;

class VirtualEnergyStorage: public CastaliaModule
{
	public:
		double isDisabled() const        { return disabled; }
		double getMinVoltage() const        { return minVoltage; }
		double getMaxVoltage() const        { return maxVoltage; }
		double getMinEnergy() const         { return minEnergy; }
		double getMaxEnergy() const         { return maxEnergy; }

		double getCurEnergyLevel() const    { return curEnergy; }
		double getCurEnergyFrac() const     { return (getCurEnergyLevel() / getMaxEnergy()); }
		double getCurVoltage() const        { return curVoltage; }
		double getCurVoltageFrac() const    { return (getCurVoltage() / getMaxVoltage()); }
		double getTotEnergyDrawn() const    { return totEnergyDrawn; }
		double getTotEnergyLeaked() const   { return totEnergyLeaked; }
		double getTotEnergyStored() const   { return totEnergyStored; }
		
		// amount of energy the storage can supply
		double getAvailableEnergy() const { return (curEnergy - minEnergy) * dischargingEfficiency; }

		// Return the amount of energy the storage can supply if the storage is enabled, zero otherwise
		double getUsableEnergy() const { 
			double availableEnergy = getAvailableEnergy();

			if ( disabled || availableEnergy <= 0.0 )
				return 0.0;

			return availableEnergy;
		}

		double getChargingEfficiency() const    { return chargingEfficiency; }
		double getDischargingEfficiency() const    { return dischargingEfficiency; }

		// simulate energy leakage
		double computeLeakage();

		// discharge the device of a specific amount of energy
		// returns the amount of energy provided and consumed
		virtual std::pair<double, double> discharge(double amount);

		// charge the device with the given amount of energy
		virtual std::pair<double, double> charge(double amount);

		virtual bool isChargeable() const = 0;

	protected:
		// device minimum voltage (V)
		double minVoltage;
		// device maximum voltage (V)
		double maxVoltage;
		// device current voltage (V)
		double curVoltage;

		bool disabled;

		// initial charge fraction 
		double fractionInitialCharge;

		// device minimum energy (J)
		double minEnergy;
		// device maximum energy (J)
		double maxEnergy;
		// device current energy level (J)
		double curEnergy;
		// initial enegry level (J)
		double initialEnergy;

		// discharge efficiency
		double dischargingEfficiency;
		// charge efficiency
		double chargingEfficiency;

		// nodeId
		unsigned int nodeId;

		// trace log file
		ofstream debugFile;

		// last logged values
		double lastLoggedVoltage;
		double lastLoggedEnergy;

		// total energy drawn from the device (J)
		double totEnergyDrawn;
		// total energy provided the device (J)
		double totEnergyProvided;
		// total energy leaked by the device (J)
		double totEnergyLeaked;
		// energy wasted due to charging/dischargin inefficiencies (J)
		double totEnergyWasted;
		// total energy stored (J)
		double totEnergyStored;

		// time of last energy update (for energy leakage)
		simtime_t timeLastLeakageUpdate;

		virtual void updateStatus();

		// log storage level to file
		void logStorageLevel();

		virtual double getVoltage(void) = 0;
		// return leakad energy in J
		virtual double energyLeakageModel() = 0;

		virtual void initialize();
		virtual void handleMessage(cMessage* msg) {}
		virtual void handleControlCommand(cMessage* msg) {}
		virtual void finishSpecific();
};

#endif
