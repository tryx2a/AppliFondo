// Il s'agit du fichier DLL principal.

#include "stdafx.h"

#include "Wrapper2.h"
using namespace Computations;
namespace Wrapper2 {
	void WrapperClass2::computePriceWrapper(){
		double ic = 1, px = 10;
		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pTrend = &trend[0];

		
		double subPeriod = 0.3;
		int timeStepSub = 4;
		
		computePrice(ic, px, option_size, pSpot, pSigma, pTrend, rho, h, H, maturity, timeSteps, samples, vlr, subPeriod, timeStepSub);
		this->confidenceInterval = ic;
		this->prix = px;
	}

	void WrapperClass2::computePriceWrapper2(){
		double ic = 1, px = 10;
		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pTrend = &trend[0];

		pin_ptr<double> pTauxActu = &tauxActu[0];
		pin_ptr<double> pfxUE = &fxUsdEur[0];
		pin_ptr<double> pfxYE = &fxYuanEur[0];
		
		double subPeriod = 0.3;
		int timeStepSub = 4;

		computePrice(ic, px, option_size, pSpot, pSigma, pTrend, pfxUE, pfxYE, pTauxActu, rho, h, H, maturity, timeSteps, samples, vlr, subPeriod, timeStepSub);
		this->confidenceInterval = ic;
		this->prix = px;
	}


	void WrapperClass2::computePnlWrapper(){
		double ic = 1, px = 10, pnl=10;
		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pTrend = &trend[0];

		pin_ptr<double> pPayoff = &payoff[0];
		pin_ptr<double> pPartSansRisque = &partSansRisque[0];
		pin_ptr<double> pValeurPortfolio = &valeurPfCouverture[0];
		
		double subPeriod = 0.3;
		int timeStepSub = 4;

		computePnL(ic, px, pnl ,option_size, pSpot, pSigma, pTrend, rho, h, H, maturity, timeSteps, samples, vlr, subPeriod, timeStepSub,
			pPayoff, pPartSansRisque, pValeurPortfolio);

		this->confidenceInterval = ic;
		this->prix = px;
		this->pnl = pnl;
	}

	void WrapperClass2::setSpot(double valeur, int indice){
		spot[indice] = valeur;
	}

	void WrapperClass2::setTauxActu(double valeur, int indice){
		tauxActu[indice] = valeur;
	}

	void WrapperClass2::setTauxUsdEur(double valeur, int indice){
		fxUsdEur[indice] = valeur;
	}

	void WrapperClass2::setTauxCnyEur(double valeur, int indice){
		fxYuanEur[indice] = valeur;
	}

}