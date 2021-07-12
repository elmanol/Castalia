//*************************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti, Alessandro Cammarano
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti, Alessandro Cammarano
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//*************************************************************************/

#include "VirtualEnergyPredictor.h"
#include <numeric>      // std::accumulate

void VirtualEnergyPredictor::initialize() {

	nSamplePerSlot = par("samplesPerSlot");
	slotSize = par("slotSize");
	predictionHorizon = par("predictionHorizon");

	energyMngr = check_and_cast<VirtualEnergyManager*>(getParentModule()->getSubmodule("EnergyManager"));

	if( nSamplePerSlot <= 0 )
		opp_error("[VirtualEnergyPredictor]: Invalid value for parameter \"sampleGranularity\", must be greater than zero");

	if( slotSize <= 0 )
		opp_error("[VirtualEnergyPredictor]: Invalid value for parameter \"slotSize\", must be greater than zero");

	if( SECONDS_PER_DAY % slotSize != 0 )
		opp_error("[VirtualEnergyPredictor]: Invalid value for parameter \"slotSize\", must divide %d.", SECONDS_PER_DAY);

	sampleGranularity = slotSize / nSamplePerSlot;
	nSlotPerDay       = SECONDS_PER_DAY / slotSize;

	if( predictionHorizon <= 0 || predictionHorizon > nSlotPerDay )
		opp_error("[VirtualEnergyPredictor]: Invalid value for parameter \"predictionHorizon\", must be in [1,nSlotPerDay]");

	slotPredictions = vector<double>(nSlotPerDay, 0.0);

	disabled = true;
	nDay  = 0;
	lastSlot = 0;
	currentSlot = 0;
	nextSlot = 0;

	ResourceManager* resMgrModule = check_and_cast <ResourceManager*>(getParentModule()
			->getParentModule()->getSubmodule("ResourceManager"));
	setTimerDrift(resMgrModule->getCPUClockDrift());
}


void VirtualEnergyPredictor::handleMessage(cMessage* msg) {

	if (disabled && msg->getKind() != NODE_STARTUP) {
		trace() << "EnergyPredictor disabled, msg " << msg->getKind() << " deleted";
		delete msg;
		return;
	}

	switch(msg->getKind()) {

		case NODE_STARTUP: {
			disabled = false;

			/* reset */
			slotSamples.clear();
			lastSlot = currentSlot = nextSlot = 0;
			
			setTimer(TIMER_SAMPLE_HARVESTING_POWER, sampleGranularity);
			
			break;
		}

		case OUT_OF_ENERGY: {
			disabled = true;
			cancelTimer( TIMER_SAMPLE_HARVESTING_POWER );
			break;
		}

		case TIMER_SERVICE: {
			handleTimerMessage(msg, disabled);
			break;
		}

		default: {
			opp_error("ERROR: Unexpected message");
			break;
		}
	}

	delete msg;
}


void VirtualEnergyPredictor::timerFiredCallback(int index)
{
	switch(index) {
		case TIMER_SAMPLE_HARVESTING_POWER:
			double currentTime = getClock().dbl(); // clock drift is taken into account

			// read and store current harvesting power
			slotSamples.push_back( getSample() );
					
			// change current day if needed
			if( currentTime >= (nDay + 1) * SECONDS_PER_DAY ){
				nDay = currentTime / SECONDS_PER_DAY;
			}

			// current slot
			int slot = (int)(currentTime / slotSize) % nSlotPerDay;

			// update current slot if needed
			if( currentSlot != slot ){
				
				currentSlot = slot;
				lastSlot = prevSlotIndex(currentSlot);
				nextSlot = nextSlotIndex(currentSlot);

				// update predictions only if at least a sample has been collected
				if ( !slotSamples.empty() ){
					lastEI = mergeSamples();
					slotSamples.clear();
					updatePredictions();
				}
			} 
			
			setTimer(TIMER_SAMPLE_HARVESTING_POWER, sampleGranularity);
			break;
	}
}

double VirtualEnergyPredictor::mergeSamples() {
	return std::accumulate(slotSamples.begin(), slotSamples.end(), 0.0) / slotSamples.size();
}
