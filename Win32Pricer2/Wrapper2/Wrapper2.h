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
		array<double> ^delta;
		array<double> ^ic;
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
		array<double> ^spot;
		array<double> ^sigma;
		array<double> ^trend;
		array<double> ^coeff;
	public:
		//Temp constructor for a basket option
		WrapperClass2() {
			confidenceInterval = prix = 0;
			option_size = 20;
			//strike = 100;
			maturity = 5;
			r = 0.03;
			rho = 0;
			timeSteps = 1;
			h = 0.1;
			H = 60;
			samples = 10000;
			vlr = 1000;
			pnl = 0;
			spot = gcnew array<double>(option_size);
			for (int i = 0; i < option_size; i++){
				spot[i] = 100;
			}
			sigma = gcnew array<double>(option_size);
			for (int i = 0; i < option_size; i++){
				sigma[i] = 0.3;
			}
			trend = gcnew array<double>(option_size);
			for (int i = 0; i < option_size; i++){
				trend[i] = 0.03;
			}

			/*coeff = gcnew array<double>(option_size);
			for (int i = 0; i < option_size; i++){
				coeff[i] = 0.025;
			}*/

			delta = gcnew array<double>(option_size);
			ic = gcnew array<double>(option_size);


		};
		void computePriceWrapper();
		//void computeDeltaWrapper();
		double getPriceWrapper() { return prix; };
		double getICWrapper() { return confidenceInterval; };
		double getPnLWrapper(){ return pnl; };

		array<double> ^getDeltaWrapper(){ return delta; };
		array<double> ^getDeltaICWrapper(){ return ic; };
		
		void computePnLWrapper();
	};
}