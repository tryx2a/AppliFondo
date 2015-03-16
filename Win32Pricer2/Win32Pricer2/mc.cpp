#include "mc.h"
#include <cstring>
#include <math.h>
#include <iostream>

using namespace std;


/*MonteCarlo::MonteCarlo(Param* P) : Method(P){}
*/

MonteCarlo::MonteCarlo(Model *mod, Produit *opt, double h, int H, int samples) : Method(mod, opt, h, H, samples){

}

MonteCarlo::MonteCarlo(int option_size, double* spot, double* sigma, double* trend, double r, double rho, double h, int H, double maturity, int timeSteps, int samples, double vlr) : Method(option_size, spot, sigma, trend, r, rho, h, H, maturity, timeSteps, samples, vlr){}


/**
* Calcul le prix de l'option en t=0 et la largeur de son intervalle de confinace
*/
void MonteCarlo::price(double &prix, double &ic){
	double coeffActu = exp(-(mod_->r_ * opt_->T_));
	//Matrix of assets

	//Initialize with spot
	PnlMat* path;
	path = pnl_mat_create(opt_->TimeSteps_ + 1, (this->mod_)->size_);

	//Calcul du payOff   
	double payOffOption = 0;
	double mean_payOffSquare = 0;
	double tmp;

	for (int m = 1; m <= this->samples_; m++){
		mod_->asset(path, opt_->T_, opt_->TimeSteps_, this->rng);
		tmp = opt_->payoff(path);
		payOffOption += tmp;
		mean_payOffSquare += tmp*tmp;
	}

	payOffOption = payOffOption / this->samples_;
	mean_payOffSquare = mean_payOffSquare / this->samples_;

	//Calcul du prix de l'option en t=0
	prix = coeffActu * payOffOption;

	//Free path
	pnl_mat_free(&path);

	//Calcul de la largeur de l'intervalle de confinace
	double cst = exp(-2 * (mod_->r_ * opt_->T_));

	double varEstimator = cst * (mean_payOffSquare - (payOffOption*payOffOption));

	//Print estimator variance on screen : To be remove ?
	std::cout << "Var Estimator: " << varEstimator << std::endl;

	ic = (prix + 1.96*sqrt(varEstimator) / sqrt(this->samples_)) - (prix - 1.96*sqrt(varEstimator) / sqrt(this->samples_));
}


/**
* Calcul le prix de l'option en t>0
*/
void MonteCarlo::price(const PnlMat *past, double t, double &prix, double &ic){

	double coeffActu = exp(-(mod_->r_ * (opt_->T_ - t)));

	//Matrix of assets
	PnlMat* path;
	path = pnl_mat_create(opt_->TimeSteps_ + 1, (this->mod_)->size_);
	//Calcul du payOff   
	double payOffOption = 0;
	double mean_payOffSquare = 0;
	double tmp;
	for (int m = 1; m <= this->samples_; m++){
		mod_->asset(path, t, opt_->TimeSteps_, opt_->T_, this->rng, past);
		tmp = opt_->payoff(path);
		payOffOption += tmp;
		mean_payOffSquare += tmp*tmp;
	}
	pnl_mat_print(path);
	payOffOption = payOffOption / this->samples_;
	mean_payOffSquare = mean_payOffSquare / this->samples_;

	//calcul du prix de l'option en t>0
	prix = coeffActu * payOffOption;

	//Free path
	pnl_mat_free(&path);

	//Calcul de la largeur de l'intervalle de confinace
	double cst = exp(-2 * (mod_->r_ * (opt_->T_ - t)));

	double varEstimator = cst * (mean_payOffSquare - (payOffOption*payOffOption));


	ic = (prix + 1.96*sqrt(varEstimator) / sqrt(this->samples_)) - (prix - 1.96*sqrt(varEstimator) / sqrt(this->samples_));
}

/*
* Calcul le delta à un t donné
*/
void MonteCarlo::delta(const PnlMat *past, double t, PnlVect *delta, PnlVect *ic){
	int nbAsset = this->opt_->size_;
	PnlMat* path_shift_up = pnl_mat_create(this->opt_->TimeSteps_ + 1, nbAsset);
	PnlMat* path_shift_down = pnl_mat_create(this->opt_->TimeSteps_ + 1, nbAsset);
	PnlMat* path = pnl_mat_create(this->opt_->TimeSteps_ + 1, nbAsset);
	PnlVect* sum = pnl_vect_create(nbAsset);
	double tstep = this->opt_->T_ / this->opt_->TimeSteps_;

	for (int j = 0; j < this->samples_; ++j){
		//Select the right asset method to call  
		if (t == 0){
			this->mod_->asset(path, this->opt_->T_, this->opt_->TimeSteps_, this->rng);
		}
		else{

			this->mod_->asset(path, t, this->opt_->TimeSteps_, this->opt_->T_, this->rng, past);

		}

		for (int i = 0; i < nbAsset; ++i){
			this->mod_->shift_asset(path_shift_up, path, i, this->h_, t, tstep);
			this->mod_->shift_asset(path_shift_down, path, i, -this->h_, t, tstep);
			LET(sum, i) = GET(sum, i) + this->opt_->payoff(path_shift_up) - this->opt_->payoff(path_shift_down);

		}
	}

	for (int i = 0; i < nbAsset; i++){
		if (t == 0){
			LET(delta, i) = GET(sum, i) * exp(-this->mod_->r_ * (this->opt_->T_ - t)) / (2.0 * this->samples_ * MGET(path, 0, i) * this->h_);
		}
		else{
			LET(delta, i) = GET(sum, i) * exp(-this->mod_->r_ * (this->opt_->T_ - t)) / (2.0 * this->samples_ * MGET(past, past->m - 1, i) * this->h_);
		}
	}

	pnl_vect_free(&sum);
	pnl_mat_free(&path);
	pnl_mat_free(&path_shift_up);
	pnl_mat_free(&path_shift_down);
}
