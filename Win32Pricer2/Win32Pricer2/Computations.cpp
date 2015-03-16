#include "Computations.h"
#include "mc.h"
#include "iostream"
#include "pnl\pnl_random.h"
#include "ctime"


void Computations::computePrice(double &ic, double &prix, int option_size, double *spot, double *sigma, double* trend,
	double r, double rho, double h, int H, double maturity, int timeSteps, int samples,double vlr)
{
	Method *mc = new MonteCarlo(option_size, spot, sigma, trend, r, rho, h, H, maturity, timeSteps, samples, vlr);

	mc->price(prix, ic);
}

void Computations::computeDelta(double *delta, double *ic, int option_size, double *spot, double *sigma, double* trend, double r,
	double rho, double h, int H, double maturity, int timeSteps, int samples,double vlr)
{
	Method *mc = new MonteCarlo(option_size, spot, sigma, trend, r, rho, h, H, maturity, timeSteps, samples, vlr);
	PnlVect* deltaVect = pnl_vect_new();
	deltaVect = pnl_vect_create(option_size);
	PnlVect* icVect = pnl_vect_new();
	icVect = pnl_vect_create(option_size);
	mc->delta(NULL, 0, deltaVect, icVect);
	for (int i = 0; i < option_size; i++){
		delta[i] = GET(deltaVect, i);
		ic[i] = GET(icVect, i);
	}

}

void Computations::computePnL(double &pnl,double &ic, double &prix, int option_size, double *spot, double *sigma, double* trend,
	double r, double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr){

	//Creation if the method
	Method *mc = new MonteCarlo(option_size, spot, sigma, trend, r, rho, h, H, maturity, timeSteps, samples, vlr);

	//Create the vector of delta
	PnlVect* V = pnl_vect_create(H + 1);

	//Compute the Profit n Lost
	mc->freeRiskInvestedPart(V, maturity, pnl);

}

void Computations::helloToYou(){
	std::cout << "Salut Yannick c'est NOEL ! " << std::endl;

}
