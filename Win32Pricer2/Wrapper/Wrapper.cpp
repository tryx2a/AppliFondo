// Il s'agit du fichier DLL principal.
/*
#include "stdafx.h"

#include "Wrapper.h"
using namespace Computations;

namespace Wrapper{
	//Constructeur
	WrapperClass::WrapperClass(){
		ic = prix = 0;
		h_ = 0.1;
		H_ = 25;
		samples_ = 50000;
		r_ = 0.05;
		rho_ = 0;
		T_ = 5;
		TimeSteps_ = 15;
		size_ = 20;

		valeurLiquidativeReference_ = 1000;
		delta = gcnew array<double>(size_);
		deltaIC = gcnew array<double>(size_);
		trend_ = gcnew array<double>(size_);

		for (int i = 0; i < size_; i++){
			trend_[i] = 0.0;
		}
		sigma_ = gcnew array<double>(size_);
		for (int i = 0; i < size_; i++){
			sigma_[i] = 0.2;
		}
		spot_ = gcnew array<double>(size_);
		for (int i = 0; i < size_; i++){
			spot_[i] = 1000;
		}
	}//Fin constructeur


	//Fonction de calcul du prix
	void WrapperClass::computePriceWrapper(){
		double prix;
		double ic;
		pin_ptr<double> spot = &spot_[0];
		pin_ptr<double> sigma = &sigma_[0];
		pin_ptr<double> trend = &trend_[0];
		computePrice(prix, ic, size_, r_, trend, rho_, sigma,
			spot, T_, TimeSteps_, valeurLiquidativeReference_, h_, H_, samples_);



		this->prix = prix;
		this->ic = ic;



	}

	//Fonction de calcul de delta
	void WrapperClass::computeDeltaWrapper(){
		pin_ptr<double> deltaW = &delta[0];
		pin_ptr<double> deltaICW = &deltaIC[0];
		pin_ptr<double> spot = &spot_[0];
		pin_ptr<double> sigma = &sigma_[0];
		pin_ptr<double> trend = &trend_[0];
		computeDelta(deltaW, deltaICW, size_, r_, trend, rho_, sigma, spot, T_, TimeSteps_, valeurLiquidativeReference_, h_, H_, samples_);
	}

	void WrapperClass::helloWrapper(){
		Computations::helloToYou();
	}
}
*/
// This is the main DLL file.
#include "stdafx.h"

#include "Wrapper.h"
using namespace Computations;
namespace Wrapper {
	void WrapperClass::computePriceWrapper(){
		double ic = 0, px = 0;
		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pTrend = &trend[0];
		pin_ptr<double> pCoeff = &coeff[0];
		computePrice(ic, px, option_size, pSpot, pSigma, pTrend, r, rho, h, H, maturity, timeSteps, samples,vlr);
		this->confidenceInterval = ic;
		this->prix = px;

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

