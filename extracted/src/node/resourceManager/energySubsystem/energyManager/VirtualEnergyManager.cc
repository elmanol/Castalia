//******************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//******************************************************************/

#include "VirtualEnergyManager.h"
#include "RechargeableBattery.h"
#include "Supercapacitor.h"
#include "Battery.h"

using namespace std;

void VirtualEnergyManager::initialize() {

	// convert in seconds
	periodicEnergyCalculationInterval = (double)(getParentModule()->getParentModule()->
			par("periodicEnergyCalculationInterval")) / 1000.;
	baselineNodePower = (double)(getParentModule()->getParentModule()->par("baselineNodePower"));     // mW

	if ( periodicEnergyCalculationInterval < 0.0 )
		opp_error("[VirtualEnergyManager] Invalid value of parameter \"periodicEnergyCalculationInterval\": must be greater than zero.");
	if( baselineNodePower < 0.0 )
		opp_error("[VirtualEnergyManager] Invalid value of parameter \"baselineNodePower\": must be non negative.");

	// get node id
	cModule* node = check_and_cast<cModule*>(getParentModule()->getParentModule()->getParentModule());
	nodeId = (unsigned)(node->getIndex());

	if ( par("traceFile").stdstringValue().size() > 0 ) {
		std::ostringstream debugFileName;
		debugFileName << par("traceFile").stringValue() << "-node" << nodeId;

		trace() << "Logging to: " << debugFileName.str();

		// debug log file
		debugFile.open(debugFileName.str().c_str(), ios_base::trunc);

		if(!debugFile.is_open()){
			opp_error("[VirtualEnergyManager]:\n Could not open log file: %s",
					debugFileName.str().c_str());
		}
	}

	nodePowerConsumption = baselineNodePower;

	useEnergyPredictor = !((getParentModule()->par("PredictorType").stdstringValue()).empty());

	// statistics
	totEnergyHarvested = 0.0;
	totEnergySupplied = 0.0;
	totEnergyLeaked	= 0.0;
	totEnergyWasted = 0.0;

	timeLastUpdate = simTime();
	startupReceived = false;

	disabledTime = 0.0;
	remainingEnergy = 0.0;
	maximumEnergy = 0.0;
	harvestingPowerRate = 0.0;

	maxHarvestingPower = 0.0;
	// Harvesting devices
	unsigned nHarvesters = (unsigned)(getParentModule()->getSubmodule("EnergyHarvesting")
			->par("numEnergyHarvesters"));
	for(unsigned i = 0; i < nHarvesters; i++) {
		VirtualEnergyHarvester* v = check_and_cast<VirtualEnergyHarvester*>(getParentModule()
				->getSubmodule("EnergyHarvesting")->getSubmodule("Harvesters", i));
		maxHarvestingPower += v->getMaxHarvestingPower();
	}

	// storage devices
	unsigned nSupercaps  = (unsigned)(getParentModule()->getSubmodule("EnergyStorage")->par("numSupercaps"));
	unsigned nRBatteries = (unsigned)(getParentModule()->getSubmodule("EnergyStorage")->par("numRechBatteries"));
	unsigned nBatteries  = (unsigned)(getParentModule()->getSubmodule("EnergyStorage")->par("numBatteries"));

	// The order in which 'storageDevices' is filled determines the order in which
	// storage devices are charged and discharged

	// supercapacitors
	for(unsigned i = 0; i < nSupercaps; ++i) {
		Supercapacitor * stmod = check_and_cast<Supercapacitor*>(getParentModule()->getSubmodule("EnergyStorage")
				->getSubmodule("Supercapacitors", i));
		remainingEnergy += stmod->getCurEnergyLevel();
		maximumEnergy   += stmod->getMaxEnergy();
		storageDevices.push_back(stmod);
	}

	// rechargeable batteries
	for(unsigned i = 0; i < nRBatteries; ++i) {
		RechargeableBattery * stmod = check_and_cast<RechargeableBattery*>(getParentModule()
				->getSubmodule("EnergyStorage")->getSubmodule("RechBatteries", i));
		remainingEnergy += stmod->getCurEnergyLevel();
		maximumEnergy += stmod->getMaxEnergy();
		storageDevices.push_back( stmod );
	}

	// batteries
	for(unsigned i = 0; i < nBatteries; ++i) {
		Battery * stmod = check_and_cast<Battery*>(getParentModule()->getSubmodule("EnergyStorage")
				->getSubmodule("Batteries", i));
		remainingEnergy += stmod->getCurEnergyLevel();
		maximumEnergy += stmod->getMaxEnergy();
		storageDevices.push_back(stmod);
	}

	initialEnergy = remainingEnergy;
	disabled = true;

	// schedule periodic energy updates
	energyMsg = new cMessage("Periodic energy calculation", PERIODIC_ENERGY_CALCULATION);
	scheduleAt(simTime() + periodicEnergyCalculationInterval, energyMsg);

	simulationEnd = SimTime::parse( ev.getConfig()->getConfigValue("sim-time-limit") );
	declareOutput("Energy breakdown");

	// updating times
    timeLastUpdate = simTime();
}

double VirtualEnergyManager::computeEnergyLeakage() {

	double energyLeaked = 0.0;

	// simulate energy leakage 
	for(vector<VirtualEnergyStorage*>::const_iterator biv = storageDevices.begin();
			biv != storageDevices.end(); ++biv) {
		energyLeaked += (*biv)->computeLeakage();
	}

	return energyLeaked;
}

void VirtualEnergyManager::switchOnNode() {

	if ( disabled && startupReceived ) {
		collectOutput("Energy breakdown", "Node switched on");
		trace() << "Node switched on";

		send(new cMessage("Energy available message", NODE_STARTUP), "toSensorDevManager");
		send(new cMessage("Energy available message", NODE_STARTUP), "toNetwork");
		send(new cMessage("Energy available message", NODE_STARTUP), "toApplication");
		if ( useEnergyPredictor )
			send(new cMessage("Energy available message", NODE_STARTUP), "toEnergyPredictor");
		disabled = false;
	}
}

void VirtualEnergyManager::switchOffNode() {

	if( !disabled) {

		collectOutput("Energy breakdown", "Node switched off");
		trace() << "Node switched off";

		send(new cMessage("Out of energy message", OUT_OF_ENERGY), "toSensorDevManager");
		send(new cMessage("Out of energy message", OUT_OF_ENERGY), "toApplication");
		send(new cMessage("Out of energy message", OUT_OF_ENERGY), "toNetwork");
		send(new cMessage("Out of energy message", OUT_OF_ENERGY), "toMac");
		send(new cMessage("Out of energy message", OUT_OF_ENERGY), "toRadio");
		if ( useEnergyPredictor )
			send(new cMessage("Out of energy message", OUT_OF_ENERGY), "toEnergyPredictor");

		disabled = true;
	}
}

void VirtualEnergyManager::destroyNode(void)
{
	Enter_Method("destroyNode(void)");

	send(new cMessage("Destroy node message", DESTROY_NODE), "toSensorDevManager");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toApplication");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toNetwork");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toMac");
	send(new cMessage("Destroy node message", DESTROY_NODE), "toRadio");
	if ( useEnergyPredictor )
		send(new cMessage("Destroy node message", DESTROY_NODE), "toEnergyPredictor");
}

void VirtualEnergyManager::finishSpecific() {
	cancelAndDelete(energyMsg);

	// energy statistic output are in Joules
	collectOutput("Energy breakdown", "Initial", initialEnergy);
	collectOutput("Energy breakdown", "Remaining", remainingEnergy);
	collectOutput("Energy breakdown", "Harvested", totEnergyHarvested);
	collectOutput("Energy breakdown", "Supplied", totEnergySupplied);
	collectOutput("Energy breakdown", "Leaked", totEnergyLeaked);
	collectOutput("Energy breakdown", "Maximum", maximumEnergy);
	collectOutput("Energy breakdown", "Wasted", totEnergyWasted);
	declareOutput("Disabled time %");
	collectOutput("Disabled time %", "", 100. * (disabledTime / simTime()));

	// If no energy was harvested, use Castalia code to estimate network lifetime
	if(totEnergyHarvested <= 0.001){
		if (getParentModule()->getIndex() == 0) {
			cTopology *topo;	// temp variable to access energy spent by other nodes
			topo = new cTopology("topo");
			topo->extractByNedTypeName(cStringTokenizer("node.Node").asVector());

			double minLifetime = estimateLifetime();
			for (int i = 1; i < topo->getNumNodes(); i++) {
				VirtualEnergyManager *resMng = dynamic_cast<VirtualEnergyManager*>
					(topo->getNode(i)->getModule()->getSubmodule("ResourceManager")->getSubmodule("EnergySubsystem")->getSubmodule("EnergyManager"));
				if (minLifetime > resMng->estimateLifetime()) 
					minLifetime = resMng->estimateLifetime();
			}

			declareOutput("Estimated network lifetime (days)");
			collectOutput("Estimated network lifetime (days)", "", minLifetime);
			delete(topo);
		}
	}

	if ( debugFile.is_open() )
		debugFile.close();
}
