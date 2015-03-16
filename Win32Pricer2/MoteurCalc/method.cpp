#include "method.h"
#include "bs.h"
#include <math.h>
#include <iostream>
#include <ctime>



using namespace std;

Method::Method(Model *mod, Produit *opt, double h, int H, int samples){
	this->mod_ = mod;
	this->opt_ = opt;
	this->rng = rng;
	this->h_ = h;
	this->H_ = H;
	this->samples_ = samples;

	this->rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(this->rng, std::time(NULL));
}
/*Method::Method(Param* P)
{
	int option_size;
	PnlVect *spot;
	PnlVect *sigma;
	PnlVect *trend;
	double rho, r;

	P->extract("option size", option_size);
	P->extract("spot", spot, option_size);
	P->extract("volatility", sigma, option_size);
	P->extract("interest rate", r);
	P->extract("correlation", rho);
	P->extract("trend", trend, option_size);
	P->extract("hedging dates number", this->H_);
	P->extract("fd step", this->h_);

	this->mod_ = new BS(spot, sigma, rho, r, option_size, trend);
	this->opt_ = Method::createOption(P);


	P->extract("sample number", this->samples_);

	this->rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(this->rng, 0);

}
*/

Method::~Method(){
	delete (this->mod_)->spot_;
	delete (this->mod_)->sigma_;
	delete this->mod_;
	pnl_rng_free(&(this->rng));
	delete this->opt_;
}

/**
* Cette méthode crée la bonne instance d'option0
*/
/*Produit* Method::createOption(Param *P){

	double maturity, strike, valeurLiquidativeReference;
	PnlVect *payoffCoeff, *lowerBarrier, *upperBarrier;
	int time_steps, option_size;

	char* key;
	P->extract("option type", key);
	P->extract("maturity", maturity);
	P->extract("timestep number", time_steps);
	P->extract("option size", option_size);

	if (strcmp(key, "basket") == 0){
		P->extract("strike", strike);
		P->extract("payoff coefficients", payoffCoeff, option_size);
		Produit* op = new OptionBasket(maturity, time_steps, option_size, strike, payoffCoeff);
		return op;
	}

	else if (strcmp(key, "fondo_garantito") == 0){
		P->extract("valeur liquidative reference", valeurLiquidativeReference);
		Produit* op = new FondoGarantito(maturity, time_steps, option_size, valeurLiquidativeReference);
		return op;
	}

	else{
		return NULL;
	}
}
*/

/* Cette méthode permet de calculer le profit & loss d'un produit pour un certain nombre
* de rebalancement précisé dans le fichier .dat
*/

void Method::freeRiskInvestedPart(PnlVect *V, double T, double &profitLoss){
	//V = pnl_vect_create(this->H_);
	PnlMat *simulMarketResult, *tempMarketResult;
	simulMarketResult = pnl_mat_create(this->H_ + 1, this->mod_->size_);

	//Simulate H+1 values from 0 to T (market values)
	mod_->simul_market(simulMarketResult, T, this->H_, this->rng);

	PnlVect* precDelta, *ecartDelta, *copydelta_i;

	//Current Time of iteration
	double tho = 0.0;

	/* Compute V_0 */
	//Compute Price
	double refprice, refic;
	this->price(refprice, refic);
	std::cout << "price :" << refprice << std::endl;

	//Compute delta_0
	PnlVect* delta, *ic;
	delta = pnl_vect_create(this->mod_->size_);
	ic = pnl_vect_create(this->mod_->size_);
	this->delta(simulMarketResult, tho, delta, ic);
	cout << "delta " << tho << endl;
	pnl_vect_print(delta);

	//On récupère S_0
	PnlVect *s;
	s = pnl_vect_create(this->mod_->size_);
	pnl_mat_get_row(s, simulMarketResult, 0);

	//On calcul V_0
	LET(V, 0) = refprice - pnl_vect_scalar_prod(delta, s);
	precDelta = pnl_vect_copy(delta); //on sauvergarde le delta qu'on vient de calculer


	/* Compute V_i */
	for (int i = 1; i<V->size; i++){
		//On incrémente tho du pas de discrétisation de la simulation de marché à savoir T/H
		tho += T / ((double) this->H_);
		cout << "tho : " << tho << endl;

		//Extract the row from 0 to tho "time"
		tempMarketResult = pnl_mat_create(i + 1, this->mod_->size_);
		pnl_mat_extract_subblock(tempMarketResult, simulMarketResult, 0, i + 1, 0, this->mod_->size_);

		//Compute delta_i
		this->delta(tempMarketResult, tho, delta, ic);
		cout << "delta " << tho << endl;
		pnl_vect_print(delta);

		copydelta_i = pnl_vect_copy(delta);
		pnl_vect_minus_vect(copydelta_i, precDelta);
		pnl_mat_get_row(s, simulMarketResult, i);
		LET(V, i) = GET(V, i - 1)*exp(mod_->r_ * T / ((double) this->H_)) - pnl_vect_scalar_prod(copydelta_i, s);
		precDelta = pnl_vect_copy(delta);

		pnl_mat_free(&tempMarketResult);
	}

	profitLoss = GET(V, V->size - 1) + pnl_vect_scalar_prod(precDelta, s) - this->opt_->payoff(simulMarketResult);
	pnl_vect_free(&s);
	pnl_vect_free(&delta);
	pnl_vect_free(&ic);
	pnl_vect_free(&precDelta);

	pnl_mat_free(&simulMarketResult);
}