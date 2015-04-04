#pragma once

#define DLLEXP   __declspec( dllexport )

namespace Computations
{
	DLLEXP void computePrice(double &ic, double &prix, int option_size, double *spot, double *sigma, double* trend,
		double *fxUsdEur, double* fxYuanEur, double *tauxActu, double rho, double h, int H, double maturity, int timeSteps,
		int samples, double vlr, double subPeriod, int timeStepSub);

	DLLEXP void computePrice(double &ic, double &prix, int option_size, double *spot, double *sigma, double* trend,
		 double rho, double h, int H, double maturity, int timeSteps,int samples, double vlr, double subPeriod, int timeStepSub);

	/*DLLEXP void computeDelta(double *deltaVect, double *icVect, int option_size, double *spot, double *sigma, double* trend, double r,
		double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr);
*/
	DLLEXP void computePnL(double &ic, double &prix, double &pnl, int option_size, double *spot, double *sigma, double* trend,
		double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr, double subPeriod, int timeStepSub,
		double *tabPayoff, double *tabPartSansRisque ,double *tabValuePfCouv);

};

