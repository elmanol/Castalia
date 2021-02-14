//*************************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti, Alessandro Cammarano
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti, Alessandro Cammarano
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//*************************************************************************/

#ifndef __VIRTUALENERGYPREDICTIONMODEL__
#define	__VIRTUALENERGYPREDICTIONMODEL__

#include "VirtualEnergyManager.h"
#include "TimerService.h"
#include <vector>
#include <typeinfo>

// timer
enum {
	TIMER_SAMPLE_HARVESTING_POWER = 0
};

#define SECONDS_PER_DAY (3600 * 24)

class VirtualEnergyPredictor : public CastaliaModule, TimerService {

	public:
		// harvesting power prediction for time t 
		double getPrediction(simtime_t t) {
			int slot = (int)(t.dbl() / slotSize) % nSlotPerDay;
			return slotPredictions[slot];
		}

	protected:
		VirtualEnergyManager* energyMngr;

		double sampleGranularity;
		int slotSize;
		int nSamplePerSlot;
		int nSlotPerDay;
		int nDay; 			/* Day index */
		int lastSlot; 		
		int currentSlot; 	/* Daily slot number, currentSlot in [0, .., DAY_SLOT-1] */
		int nextSlot;
		double lastEI; 		/* last slot sample */
		
		vector<double> slotSamples;
		vector<double> slotPredictions;
		int predictionHorizon;

		bool disabled;

		double getSample() {
			return energyMngr->getCurrentHarvestingPower();
		}

		int nextSlotIndex(int slot, int futureSlots = 1) {
			int s = (slot + futureSlots) % nSlotPerDay;
			if ( s < 0 )
				s += nSlotPerDay;
			return s;
		}

		int prevSlotIndex(int slot, int pastSlots = 1) {
			int s = (slot - pastSlots) % nSlotPerDay;
			if ( s < 0 )
				s += nSlotPerDay;
			return s;
		}

		// compute prediction for future slots
		virtual void updatePredictions() = 0;
		virtual double mergeSamples();

		virtual void initialize();
		virtual void handleMessage(cMessage* msg);
		virtual void timerFiredCallback(int index);
};


#endif	/* VIRTUALENERGYPREDICTIONMODEL */

