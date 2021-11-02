/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Yuriy Tselishchev                                            *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *  
 ****************************************************************************/

//********************************************************************************
//*  Modified for GreenCastalia integration: energySource submodule added        *
//*  Modification date: 17/12/2013                                               *
//********************************************************************************
//*  Copyright (C): Dora Spenza, David Benedetti, 2013                           *
//*  Author(s): Dora Spenza, David Benedetti                                     *
//*  Developed at Computer Science Department, Sapienza University of Rome       *
//*  This file is distributed under the terms in the attached LICENSE_GC file.   *
//*******************************************************************************/

#ifndef CASTALIA_TIMER
#define CASTALIA_TIMER

#define TIMER_MIN_SIZE 8
#define TIMER_MAX_SIZE 256

#include <omnetpp.h>
#include <vector>

#include "CastaliaMessages.h"
#include "TimerServiceMessage_m.h"

class TimerService: public virtual cSimpleModule {
 private:
	double timerDrift;
 protected:
	std::vector<TimerServiceMessage*> timerMessages;

	simtime_t getClock();
	void setTimerDrift(double new_drift);
	void setTimer(int index, simtime_t time);
	simtime_t getTimer(int index);
	void cancelTimer(int index);
	void handleTimerMessage(cMessage *, bool disabledNode);
	virtual void timerFiredCallback(int index);
};

#endif
