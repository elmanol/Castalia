//*************************************************************************/
//*  Copyright (C) 2013 Dora Spenza, David Benedetti, Alessandro Cammarano
//*  Developed at SENSES Lab: http://senseslab.di.uniroma1.it
//*  Computer Science Department, Sapienza University of Rome
//*  Author(s): Dora Spenza, David Benedetti, Alessandro Cammarano
//*  This file is distributed under the terms in the attached
//*  LICENSE_GC file.
//*************************************************************************/

#ifndef __AEWMA__
#define	__AEWMA__

#include "VirtualEnergyPredictor.h"

/* 
 * Implementation of the "advanced expectation model of the amount of harvested 
 * energy" described in the paper:
 *
 * D. K. Noh and K. Kang, Balanced energy allocation scheme for a solar-powered 
 * sensor system and its effects on networkwide performance, Journal of Computer 
 * and System Sciences, vol. 77, no. 5, pp. 917, September 2011.
 */
class AEWMA : public VirtualEnergyPredictor {

	protected:
		void initialize();
		void updatePredictions();

	private:
		double alpha;
		vector<double> mean;
		bool advancedModel;
};

#endif	/* AEWMA_H */

