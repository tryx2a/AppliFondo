#pragma once

#define DLLEXP   __declspec( dllexport )

namespace Computations
{
	DLLEXP void computePrice(double &ic, double &prix, int option_size, double *spot, double *sigma, double* trend,
		double r, double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr);

	DLLEXP void computeDelta(double *deltaVect, double *icVect, int option_size, double *spot, double *sigma, double* trend, double r,
		double rho, double h, int H, double maturity, int timeSteps, int samples,double vlr);

	DLLEXP void computePnL(double &pnl,double &ic, double &prix, int option_size, double *spot, double *sigma, double* trend,
		double r, double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr);

	DLLEXP void helloToYou();
};

