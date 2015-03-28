// Wrapper2.h

#pragma once
#include "Computations.h"
using namespace System;

namespace Wrapper2 {

	public ref class WrapperClass2
	{
	private:
		double confidenceInterval;
		double prix;
		double pnl;

		int option_size;
		double r;
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
		
		WrapperClass2() {
			
			confidenceInterval = prix = 0;
			option_size = 22;
			maturity = 5;
			rho = 0;
			timeSteps = 1;
			h = 0.1;
			H = 70;
			samples = 5000;
			vlr = 1000;
			pnl = 0;

			spot = gcnew array<double>(option_size);

			for (int i = 0; i < option_size; i++){
				spot[i] = 100;
			}
			spot[0] = 1.0745;
			spot[1] = 6.7307;

			sigma = gcnew array<double>(option_size);
			for (int i = 0; i < option_size; i++){
				sigma[i] = 0.3;
			}
			trend = gcnew array<double>(option_size);
			for (int i = 0; i < option_size; i++){
				trend[i] = 0.03;
			}
	
			payoff = gcnew array<double>(H);

		};

		WrapperClass2(int timeStepsSub_, int H_, int sample_) {
			confidenceInterval = prix = 0;
			
			option_size = 22;
			maturity = 5;
			rho = 0;
			timeSteps = 1;
			h = 0.1;
			vlr = 1000;
			pnl = 0;

			H = H_;
			samples = sample_;

			timeStepSubscription = timeStepsSub_;

			spot = gcnew array<double>(option_size);

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
			

			tauxActu = gcnew array<double>{ 0.00024, 0.00044, 0.00063, 0.00129, 0.00164, 0.0026, 0.00374,
				0.00457, 0.00584, 0.00634, 0.00756, 0.0088, 0.00974, 0.01034,
				0.01149, 0.01198, 0.01356, 0.01402, 0.01451, 0.01503, 0.01604,
				0.01567, 0.01654 };

			payoff = gcnew array<double>(H_);
			valeurPfCouverture = gcnew array<double>(H_);
			partSansRisque = gcnew array<double>(H_);
		};

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
