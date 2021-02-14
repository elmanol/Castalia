/*******************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                            *
 *  Developed at the ATP lab, Networked Systems research theme                 *
 *  Author(s): Athanassios Boulis, Dimosthenis Pediaditakis, Yuriy Tselishchev *
 *  This file is distributed under the terms in the attached LICENSE file.     *
 *  If you do not find this file, copies can be found by writing to:           *
 *                                                                             *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                *
 *      Attention:  License Inquiry.                                           *
 *                                                                             *  
 *******************************************************************************/

//********************************************************************************
//*  Modified for GreenCastalia integration                                      *
//*  Modification date: 07/01/2013                                               *
//********************************************************************************
//*  Copyright (C): Dora Spenza, David Benedetti, 2013                           *
//*  Author(s): Dora Spenza, David Benedetti                                     *
//*  Developed at Computer Science Department, Sapienza University of Rome       *
//*  This file is distributed under the terms in the attached LICENSE_2 file.    *
//*******************************************************************************/

#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <map>
#include "CastaliaModule.h"
#include "ResourceManagerMessage_m.h"

using namespace std;

class ResourceManager: public CastaliaModule {
 private:
	// parameters and variables
	/*--- The .ned file's parameters ---*/
	double sigmaCPUClockDrift;
	double cpuClockDrift;
	double initialEnergy;
	double ramSize;

	/*--- Custom class parameters ---*/
	double totalRamData;
	bool disabled;

 protected:
	void initialize();
	void handleMessage(cMessage * msg);
	void finishSpecific();

 public:
	double getCPUClockDrift(void);
	void destroyNode(void);
	int RamStore(int numBytes);
	void RamFree(int numBytes);
};

#endif				// _RESOURCEGENERICMANAGER_H_
