// Il s'agit du fichier DLL principal.

#include "stdafx.h"

#include "Wrapper.h"
using namespace Computations;
namespace Wrapper2 {
	
	WrapperClass2::WrapperClass2() {

		confidenceInterval = 0;
		prix = 0;
		option_size = 22;
		maturity = 5;
		rho = 0;
		timeSteps = 1;
		h = 0.1;
		H = 70;
		samples = 1000;
		vlr = 1000;
		pnl = 0;
		timeStepSubscription = 4;

		spot = gcnew array<double>(option_size);
		spot[0] = 1.0745;
		spot[1] = 6.7307;
		spot[2] = 53.49;
		spot[3] = 214.01;
		spot[4] = 16.92;
		spot[5] = 4.04;
		spot[6] = 99600;
		spot[7] = 6.39;
		spot[8] = 47.1;
		spot[9] = 18.1;
		spot[10] = 69.15;
		spot[11] = 30.22;
		spot[12] = 6.25;
		spot[13] = 78.7;
		spot[14] = 30.95;
		spot[15] = 122.45;
		spot[16] = 56.75;
		spot[17] = 63.44;
		spot[18] = 85.65;
		spot[19] = 65.88;
		spot[20] = 32.93;
		spot[21] = 54.23;

		sigma = gcnew array<double>(option_size);
		for (int i = 0; i < option_size; i++){
			sigma[i] = 0.3;
		}
		trend = gcnew array<double>(option_size);
		for (int i = 0; i < option_size; i++){
			trend[i] = 0.03;
		}

		fxUsdEur = gcnew array<double>{ 1.353, 1.2369, 1.3095, 1.3973, 1.3171, 1.4141, 1.4287, 1.4242, 1.3672, 1.293, 1.3171, 1.2518,
			1.2422, 1.3106, 1.3195, 1.3076, 1.292, 1.3296, 1.3664, 1.3779, 1.3924, 1.3628, 1.3366, 1.2812, 1.2101, 1.0575 };


		fxYuanEur = gcnew array<double>{ 9.2362545, 8.44864545, 8.867934, 9.29232446, 8.6731035, 9.28908149, 9.2751204, 9.15817568, 8.726154,
			8.1382713, 8.32696962, 7.94129402, 7.90834208, 8.19138106, 8.22061695, 8.12451108, 7.9213812, 8.1391464,
			8.3323072, 8.34139323, 8.56326, 8.49882964, 8.2474903, 7.8447876, 7.50818646, 6.622065 };
		payoff = gcnew array<double>(H);
		tauxActu = gcnew array<double>{ 0.00024, 0.00044, 0.00063, 0.00129, 0.00164, 0.0026, 0.00374,
			0.00457, 0.00584, 0.00634, 0.00756, 0.0088, 0.00974, 0.01034,
			0.01149, 0.01198, 0.01356, 0.01402, 0.01451, 0.01503, 0.01604,
			0.01567, 0.01654 };


		payoff = gcnew array<double>(H);
		valeurPfCouverture = gcnew array<double>(H);
		partSansRisque = gcnew array<double>(H);

		delta = gcnew array<double>(option_size);
	};
	
	WrapperClass2::WrapperClass2(int timeStepsSub_, int H_, int sample_) {
		confidenceInterval = 0;
		prix = 0;
		option_size = 22;
		maturity = 5;
		rho = 0;
		timeSteps = 1;
		h = 0.1;
		H = H_;
		samples = sample_;
		vlr = 1000;
		pnl = 0;
		timeStepSubscription = timeStepsSub_;

		spot = gcnew array<double>(option_size);
		spot[0] = 1.0745;
		spot[1] = 6.7307;
		spot[2] = 53.49;
		spot[3] = 214.01;
		spot[4] = 16.92;
		spot[5] = 4.04;
		spot[6] = 99600;
		spot[7] = 6.39;
		spot[8] = 47.1;
		spot[9] = 18.1;
		spot[10] = 69.15;
		spot[11] = 30.22;
		spot[12] = 6.25;
		spot[13] = 78.7;
		spot[14] = 30.95;
		spot[15] = 122.45;
		spot[16] = 56.75;
		spot[17] = 63.44;
		spot[18] = 85.65;
		spot[19] = 65.88;
		spot[20] = 32.93;
		spot[21] = 54.23;

		sigma = gcnew array<double>(option_size);
		for (int i = 0; i < option_size; i++){
			sigma[i] = 0.3;
		}
		trend = gcnew array<double>(option_size);
		for (int i = 0; i < option_size; i++){
			trend[i] = 0.03;
		}
		fxUsdEur = gcnew array<double>{ 1.353, 1.2369, 1.3095, 1.3973, 1.3171, 1.4141, 1.4287, 1.4242, 1.3672, 1.293, 1.3171, 1.2518,
			1.2422, 1.3106, 1.3195, 1.3076, 1.292, 1.3296, 1.3664, 1.3779, 1.3924, 1.3628, 1.3366, 1.2812, 1.2101, 1.0575 };


		fxYuanEur = gcnew array<double>{ 9.2362545, 8.44864545, 8.867934, 9.29232446, 8.6731035, 9.28908149, 9.2751204, 9.15817568, 8.726154,
			8.1382713, 8.32696962, 7.94129402, 7.90834208, 8.19138106, 8.22061695, 8.12451108, 7.9213812, 8.1391464,
			8.3323072, 8.34139323, 8.56326, 8.49882964, 8.2474903, 7.8447876, 7.50818646, 6.622065 };
		payoff = gcnew array<double>(H);
		tauxActu = gcnew array<double>{ 0.00024, 0.00044, 0.00063, 0.00129, 0.00164, 0.0026, 0.00374,
			0.00457, 0.00584, 0.00634, 0.00756, 0.0088, 0.00974, 0.01034,
			0.01149, 0.01198, 0.01356, 0.01402, 0.01451, 0.01503, 0.01604,
			0.01567, 0.01654 };
		payoff = gcnew array<double>(H);
		valeurPfCouverture = gcnew array<double>(H);
		partSansRisque = gcnew array<double>(H);

		delta = gcnew array<double>(option_size);
	};

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

	void WrapperClass2::computeCompoPfWrapper(double tho){
		double V;
		pin_ptr<double> pSpot = &spot[0];
		pin_ptr<double> pSigma = &sigma[0];
		pin_ptr<double> pTrend = &trend[0];

		pin_ptr<double> pPayoff = &payoff[0];
		pin_ptr<double> pPartSansRisque = &partSansRisque[0];
		pin_ptr<double> pValeurPortfolio = &valeurPfCouverture[0];

		pin_ptr<double> pDelta = &delta[0];

		double subPeriod = 0.3;
		int timeStepSub = 4;

		computeCompoPf(V, option_size, pSpot, pSigma, pTrend,
			rho, h, H, maturity, timeSteps, samples, vlr, subPeriod, timeStepSub,
			pDelta,tho);

		this->partTauxSansRisque = V;
		for (int i = 0; i < delta->Length; i++){
			delta[i] = pDelta[i];
		}

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