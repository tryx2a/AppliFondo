#include "Computations.h"
#include "method\mc.h"
#include "method\method.h"
#include "model\bs.h"
#include "model\model.h"
#include "iostream"
#include "pnl\pnl_random.h"
#include "ctime"


void Computations::computePrice(double &ic, double &prix, int option_size, double *spot, double *sigma, double* trend,
	double *fxUsdEur, double* fxYuanEur, double *tauxActu,
	 double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr, double subPeriod, int timeStepSub)
{

	Taux *r = new TauxLPM();
	TauxDeChange *fx = new TauxDeChange();

	Produit *p = new FondoGarantito(maturity, timeSteps, option_size, vlr, subPeriod, timeStepSub);
	Model *mod = new BS(spot,sigma,rho,r,option_size,trend,fx,10,5,5,NULL);
	Method *mc = new  MonteCarlo(mod, p, h, H, samples);

	mc->price(prix, ic);

}

void Computations::computePrice(double &ic, double &prix, int option_size, double *spot, double *sigma, double* trend,
	double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr, double subPeriod, int timeStepSub)
{
	//PnlVect *u = pnl_vect_create_from_file("C:/Users/Yannick/Desktop/AppliFondo/Win32Pricer2/data/TauxZC.csv");

	Taux *r = new TauxLPM();
	TauxDeChange *fx = new TauxDeChange();

	/*Produit *p = new FondoGarantito(maturity, timeSteps, option_size, vlr, subPeriod, timeStepSub);
	Model *mod = new BS(spot, sigma, rho, r, option_size, trend, fx, 13, 4, 3, NULL);
	Method *mc = new  MonteCarlo(mod, p, h, H, samples);*/
	Method *mc = new MonteCarlo(spot, sigma, rho, r, option_size, trend, fx, 10, 5, 5, NULL, maturity, timeSteps, vlr, subPeriod, timeStepSub, h, H, samples);

	mc->price(prix, ic);

}

void Computations::computePnL(double &ic, double &prix, double &pnl, int option_size, double *spot, double *sigma, double* trend,
	double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr, double subPeriod, int timeStepSub,
	double *tabPayoff, double *tabPartSansRisque, double *tabaPfCouv){

	Taux *r = new TauxLPM();
	TauxDeChange *fx = new TauxDeChange();

	/*Produit *p = new FondoGarantito(maturity, timeSteps, option_size, vlr, subPeriod, timeStepSub);
	Model *mod = new BS(spot, sigma, rho, r, option_size, trend, fx, 13, 4, 3, NULL);
	Method *mc = new  MonteCarlo(mod, p, h, H, samples);
	*/
	Method *mc=new MonteCarlo(spot,sigma,rho, r,option_size,trend,fx,10,5,5,NULL,maturity,timeSteps,vlr,subPeriod,timeStepSub,h,H,samples);

	double V = 0.0;
	double portfolio = 0.0;
	double payoff = 0.0;

	PnlVect *delta = pnl_vect_create(mc->opt_->size_);
	double tho = 0.0;

	PnlMat *simulMarketResult, *tempMarketResult;
	simulMarketResult = pnl_mat_create(mc->H_ + 1, mc->mod_->size_);
	mc->mod_->simul_market(simulMarketResult, maturity, mc->H_, mc->rng);
	
	tempMarketResult = pnl_mat_copy(simulMarketResult);
	

	for (int i = 0; i<H + 1; i++){
		mc->freeRiskInvestedPart(V, maturity + subPeriod, portfolio, payoff, delta, tho, tempMarketResult);

		tabPayoff[i] = payoff;
		tabaPfCouv[i] = portfolio;
		tabPartSansRisque[i] = V;

		tho += (maturity + subPeriod) / ((double)mc->H_);
		//Extraction des données de la matrice past pour la date de rebalancement
		pnl_mat_free(&tempMarketResult);
		if (i<H){
			tempMarketResult = pnl_mat_create((i + 1) + 1, mc->mod_->size_);
			pnl_mat_extract_subblock(tempMarketResult, simulMarketResult, 0, (i + 1) + 1, 0, mc->mod_->size_);
		}
	}
	
	pnl_mat_free(&simulMarketResult);

	prix = portfolio;
	ic = payoff;
	pnl = portfolio - payoff;
	
}

void Computations::computeCompoPf(double &partSansRisque, int option_size, double *spot, double *sigma, double* trend,
	double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr, double subPeriod, int timeStepSub,
	double *tabDelta, double tho){

	Taux *r = new TauxLPM();
	TauxDeChange *fx = new TauxDeChange();

	Method *mc = new MonteCarlo(spot, sigma, rho, r, option_size, trend, fx, 10, 5, 5, NULL, maturity, timeSteps, vlr, subPeriod, timeStepSub, h, H, samples);

	double V = 0.0;
	PnlVect *delta = pnl_vect_create(mc->opt_->size_);

	/*************
	* ATTENTION : le tho doit être celui d'aujourd'hui et non une valeur arbitraire
	**************/
	//double tho = 3.4;

	PnlMat *past;
	past = pnl_mat_create(mc->H_ + 1, mc->mod_->size_);
	mc->mod_->simul_market(past, tho, mc->H_, mc->rng);

	mc->portfolioCompositionAtTho(V, maturity, delta, tho, past);

	for (int i = 0; i < delta->size; i++){
		tabDelta[i] = GET(delta, i);
	}

	partSansRisque = V;

	pnl_mat_free(&past);
	pnl_vect_free(&delta);
	delete mc;

}