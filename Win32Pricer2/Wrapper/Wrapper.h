
#pragma once
#include "src\Computations.h"
using namespace System;

namespace Wrapper2 {

	public ref class WrapperClass2
	{
	private:
		double confidenceInterval;
		double prix;
		double pnl;
		int option_size;
		double rho;
		double h;
		int H;
		double maturity;
		int timeSteps;
		double strike;
		int samples;
		double vlr;
		int timeStepSubscription;

		array<double> ^spot;
		array<double> ^sigma;
		array<double> ^trend;
		array<double> ^fxUsdEur;
		array<double> ^fxYuanEur;
		array<double> ^tauxActu;
		array<double> ^payoff;
		array<double> ^partSansRisque;
		array<double> ^valeurPfCouverture;

	public:
		WrapperClass2();
		WrapperClass2(int timeStepsSub_, int H_, int sample_);
		void computePriceWrapper();
		void computePriceWrapper2();
		void computePnlWrapper();

		double getPriceWrapper() { return prix; };
		double getICWrapper() { return confidenceInterval; };
		double getPnLWrapper(){ return pnl; };

		array<double> ^getPayoff(){ return payoff; };
		array<double> ^getPartSansRisque(){ return partSansRisque; };
		array<double> ^getPfCouverture(){ return valeurPfCouverture; };

		void setSpot(double valeur, int indice);
		void setTauxActu(double valeur, int indice);
		void setTauxUsdEur(double valeur, int indice);
		void setTauxCnyEur(double valeur, int indice);

		/*array<double> ^getDeltaWrapper(){ return delta; };
		array<double> ^getDeltaICWrapper(){ return ic; };*/

	};
}
