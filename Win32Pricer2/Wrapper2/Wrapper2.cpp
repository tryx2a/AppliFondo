// Il s'agit du fichier DLL principal.

#include "stdafx.h"

#include "Wrapper2.h"
using namespace Computations;
namespace Wrapper2 {
	void WrapperClass2::computePriceWrapper(){
		double ic = 0, px = 0;
		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pTrend = &trend[0];
		//pin_ptr<double> pCoeff = &coeff[0];
		computePrice(ic, px, option_size, pSpot, pSigma, pTrend, r, rho, h, H, maturity, timeSteps, samples, vlr);
		this->confidenceInterval = ic;
		this->prix = px;

	}

	void WrapperClass2::computePnLWrapper(){
		double prix=0,ic = 0, pnl = 0;
		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pTrend = &trend[0];
		computePnL(pnl, ic, prix, option_size, pSpot, pSigma, pTrend, r, rho, h, H, maturity, timeSteps, samples, vlr);
		this->confidenceInterval = ic;
		this->prix = prix;
		this->pnl = pnl;
	}


	/*void WrapperClass::computeDeltaWrapper(){
	pin_ptr<double> pDeltaIc = &ic[0];
	pin_ptr<double> pDelta = &delta[0];
	pin_ptr<double> pSpot = &spot[0];
	pin_ptr<double> pSigma = &sigma[0];
	pin_ptr<double> pTrend = &trend[0];
	pin_ptr<double> pCoeff = &coeff[0];
	computeDelta(pDelta, pDeltaIc, option_size, pSpot, pSigma, pTrend, r, rho, h, H, maturity, timeSteps,samples,vlr);

	}*/
}