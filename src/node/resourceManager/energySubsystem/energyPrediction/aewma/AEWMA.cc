//*************************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti, Alessandro Cammarano
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti, Alessandro Cammarano
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//*************************************************************************/

#include "AEWMA.h"

Define_Module(AEWMA);

void AEWMA::initialize() {

	VirtualEnergyPredictor::initialize();

	alpha = par("alpha");

	if( alpha < 0.0 || alpha > 1.0 )
		opp_error("[AEWMA]: Invalid value of parameter \"alpha\", out of range [0,1].");

	advancedModel = par("useAdvancedModel");

	mean = vector<double>(nSlotPerDay);
}

void AEWMA::updatePredictions() {

	if ( lastSlot < 0 || lastSlot >= nSlotPerDay ){
		opp_warning("Warning: invalid slot index");
		return;
	}

	/* Update predictions
	 * as the current slot has just been updated, 'lastEI' value refers to the last timeslot
	 */
	if (nDay == 0) {
		mean[lastSlot] = lastEI;
	} else {
		mean[lastSlot] = alpha * lastEI + (1 - alpha) * mean[lastSlot];
	}
	
	double W = 1.0;

	if ( advancedModel && mean[lastSlot] > 0.0 )
		W = lastEI / mean[lastSlot];

	/* Compute prediction for 'predictionHorizon' slots in the future */
	for (int h = 0; h < predictionHorizon; h++) {
		int s = nextSlotIndex(currentSlot, h);
		slotPredictions[s] = mean[s] * (W + (1. - W) / nSlotPerDay * h);
	}
}
