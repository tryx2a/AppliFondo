#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>  
#include <ctime>
#include "assert.h"

using namespace std;

#include "bs.h"


//Blacḱ&Scholes Constructor
BS::BS(PnlVect *spot_, PnlVect *sigma_, double rho_, Taux* r_, int size_, PnlVect *trend, TauxDeChange *fx, int numberAssetEuro, int numberAssetDollar, int numberAssetYuan, const char *pastData) :Model(spot_, sigma_, rho_, r_, size_, trend, fx, numberAssetEuro, numberAssetDollar, numberAssetYuan)
{

	PnlMat *past = NULL;
	if (pastData != NULL){
		past = pnl_mat_create_from_file(pastData);
	}
	PnlMat *chol;
	chol = pnl_mat_create(size_, size_);
	computeCholesky(chol, rho_, past);
	this->chol = chol;
}

BS::BS(double *spot_, double *sigma_, double rho_, Taux* r_, int size_, double *trend, TauxDeChange *fx,
	int numberAssetEuro, int numberAssetDollar, int numberAssetYuan, const char *pastData)
	: Model(spot_, sigma_, rho_, r_, size_, trend, fx, numberAssetEuro, numberAssetDollar, numberAssetYuan)
{
	PnlMat *past = NULL;
	if (pastData != NULL){
		past = pnl_mat_create_from_file(pastData);
	}
	PnlMat *chol;
	chol = pnl_mat_create(size_, size_);
	computeCholesky(chol, rho_, past);
	this->chol = chol;
}

//Blacḱ&Scholes Destructor		
BS::~BS()
{
	//Free the cholesky matrix
	pnl_mat_free(&chol);
}

void BS::computeCorrelation(PnlMat *past, PnlMat* corMat){

	int nbLigne = past->m;
	int nbColonne = past->n;
	double sum = 0.0;
	double sumCarre = 0.0;

	//Calcul des écarts types des actifs
	for (int i = 0; i<nbColonne; i++){
		sum = 0.0;
		sumCarre = 0.0;
		for (int j = 0; j<nbLigne; j++){
			sumCarre += MGET(past, j, i)*MGET(past, j, i);
			sum += MGET(past, j, i);
		}
		MLET(corMat, i, i) = sqrt(sumCarre / past->m - sum / past->m*sum / past->m);
		LET(sigma_, i) = MGET(corMat, i, i);
	}

	double sumproduit = 0, sum1 = 0, sum2 = 0;
	//Calcul des corrélations entre les actifs
	for (int k = 0; k<corMat->m; k++){
		for (int l = k + 1; l<corMat->n; l++){
			sumproduit = 0;
			sum1 = 0;
			sum2 = 0;
			for (int i = 0; i<nbLigne; i++){
				sumproduit += MGET(past, i, k)*MGET(past, i, l);
				sum1 += MGET(past, i, k);
				sum2 += MGET(past, i, l);
			}
			MLET(corMat, k, l) = (sumproduit / nbLigne - sum1*sum2 / (nbLigne*nbLigne)) / (MGET(corMat, k, k)*MGET(corMat, l, l));
			MLET(corMat, l, k) = MGET(corMat, k, l);
		}
	}
	pnl_mat_set_diag(corMat, 1, 0);
}

void BS::computeCholesky(PnlMat *chol, double rho_, PnlMat *past)
{
	//Initial correlation matrix
	PnlMat *corMatrix;
	double size_ = this->size_;

	//Fill the matrix with the correlation factor.
	if (past != NULL){
		corMatrix = pnl_mat_create(size_, size_);
		computeCorrelation(past, corMatrix);
	}
	else{
		corMatrix = pnl_mat_create_from_scalar(size_, size_, rho_);
		pnl_mat_set_diag(corMatrix, 1, 0);
	}

	int exitChol = pnl_mat_chol(corMatrix);

	if (exitChol != 0){
		cout << "Cholesky failed" << endl;
		throw std::exception();
	}
	//Clone the result
	pnl_mat_clone(chol, corMatrix);
	//Free the temp matrix
	pnl_mat_free(&corMatrix);
}

void BS::asset(PnlMat *path, double t, double subscriptionPeriod, int timeStepSubscription, int N, double T, PnlRng *rng, const PnlMat *past){

	PnlVect *vectorGaussian;
	vectorGaussian = pnl_vect_create(this->size_);
	double epsilon = 0.001;
	double pasDiscretisation;
	int index; //correspond à l'index de la matrice path jusqu'au quel on connait la trajectoire grace à "past"
	int indexPast; //correspond à l'index max de "past" dans la période de souscription

	if (t < subscriptionPeriod){ // t se trouve dans la période de souscription
		pasDiscretisation = subscriptionPeriod / timeStepSubscription;

		// Si t n'est pas un pas de dicrétisation
		double reste = fmod(t, pasDiscretisation);
		if (!(fabs(reste)<epsilon)){
			t -= reste; //On ajuste t pour qu'il soit sur un pas de discrétisation.
		}

		index = t / pasDiscretisation;
		indexPast = past->m - 1;
	}
	else{
		pasDiscretisation = T / N;

		//Calcul du pas de discrétisation de la matrice past
		double pasDiscretisationPast = t / (past->m - 1);

		//Calcul de l'index où se situe la date finale de la période de souscription
		indexPast = subscriptionPeriod / pasDiscretisationPast;
		index = timeStepSubscription;
	}


	if (index == 0){
		this->asset(path, subscriptionPeriod, timeStepSubscription, T, N, rng);
	}
	else{

		//On remplit la matrice path jusqu'à l'indice index via la matrice past
		for (int i = 0; i <= index; i++){
			for (int j = 0; j < this->size_; j++){
				if (i == 0){
					MLET(path, i, j) = MGET(past, i, j);
				}
				else{
					MLET(path, i, j) = MGET(past, (int)((double)(indexPast)* i / index + 0.5), j);
				}
			}
		}

		// On simule le reste de la trajectoire dans la période de souscription si on ne connait pas encore toute la trajectoire
		for (int i = index + 1; i < timeStepSubscription + 1; i++){
			//Create the gaussian for each simulation
			pnl_vect_rng_normal(vectorGaussian, this->size_, rng);
			for (int j = 0; j < this->size_; j++){
				MLET(path, i, j) = this->computeIteration(MGET(path, i - 1, j), subscriptionPeriod / timeStepSubscription, j, vectorGaussian, false, t);
			}
		}

		if (t == T){ //Si t est la maturité du produit, alors on connait la trajectoire entière via "past"
			for (int j = 0; j < this->size_; j++){
				MLET(path, timeStepSubscription + 1, j) = MGET(past, past->m - 1, j);
			}
		}
		else{
			//Create the gaussian for each simulation
			pnl_vect_rng_normal(vectorGaussian, this->size_, rng);
			//Calcul de la trajectoire à la date de constatation finale
			for (int j = 0; j<this->size_; j++){
				MLET(path, timeStepSubscription + 1, j) = this->computeIteration(MGET(path, timeStepSubscription, j), T / N, j, vectorGaussian, false, subscriptionPeriod);
			}
		}

		for (int i = 0; i <= timeStepSubscription + 1; i++){ // on multi par la devise
			for (int j = 2 + this->numberAssetEuro_; j<this->size_; j++){
				if (j < 2 + this->numberAssetEuro_ + this->numberAssetDollar_){
					MLET(path, i, j) = MGET(path, i, j)*MGET(path, i, 0);
				}
				else{
					MLET(path, i, j) = MGET(path, i, j)*MGET(path, i, 1);
				}
			}
		}
	}
	pnl_vect_free(&vectorGaussian);
}

void BS::asset(PnlMat *path, double subscriptionPeriod, int timeStepSubscription, double T, int N, PnlRng *rng){


	//Initialize the first path row with the spot prices
	for (int j = 0; j<this->size_; j++){
		MLET(path, 0, j) = GET(this->spot_, j);


	}
	PnlVect *vectorGaussian;
	vectorGaussian = pnl_vect_create(this->size_);

	//Calcul de la trajectoire jusqu'à la fin de période de souscription
	for (int i = 1; i<timeStepSubscription + 1; i++){
		//Create the gaussian for each simulation
		pnl_vect_rng_normal(vectorGaussian, this->size_, rng);
		//For each assets 
		for (int j = 0; j<this->size_; j++){
			MLET(path, i, j) = this->computeIteration(MGET(path, i - 1, j), subscriptionPeriod / timeStepSubscription, j, vectorGaussian, false, 0.0);
		}
	}

	//Calcul de la trajectoire à la date de constatation finale
	for (int j = 0; j<this->size_; j++){
		MLET(path, timeStepSubscription + 1, j) = this->computeIteration(MGET(path, timeStepSubscription, j), T / N, j, vectorGaussian, false, 0.0);
	}

	for (int i = 0; i <= timeStepSubscription + 1; i++){ // on multi par la devise
		for (int j = 2 + this->numberAssetEuro_; j<this->size_; j++){
			if (j < 2 + this->numberAssetEuro_ + this->numberAssetDollar_){
				MLET(path, i, j) = MGET(path, i, j)*MGET(path, i, 0);
			}
			else{
				MLET(path, i, j) = MGET(path, i, j)*MGET(path, i, 1);
			}
		}
	}

	pnl_vect_free(&vectorGaussian);
}

double BS::computeIteration(double currentPrice, double h, int assetIndex, PnlVect* vectorGaussian, bool useTrend, double t){
	//Compute the scalar product
	PnlVect rowChol;
	rowChol = pnl_vect_wrap_mat_row(this->chol, assetIndex);
	double scalarResult = pnl_vect_scalar_prod(&rowChol, vectorGaussian);
	double sigma = GET(this->sigma_, assetIndex);
	//Compute the exponential argument
	double expArg;
	double mu;

	if (useTrend){
		mu = GET(this->trend, assetIndex);
		expArg = sqrt(h)*scalarResult*sigma + h*(mu - (sigma*sigma / 2));
	}
	else{
		if (assetIndex == 0){ //simulation de la devise eur_dol
			expArg = sqrt(h)*scalarResult*sigma + (this->fx_->computeRate(t + h, this->fx_->txZcEuro) - this->fx_->computeRate(t, this->fx_->txZcEuro) - this->fx_->computeRate(t + h, this->fx_->txZcDollar) + this->fx_->computeRate(t, this->fx_->txZcDollar) - h*(sigma*sigma / 2));
		}
		else if (assetIndex == 1){ //simulation de la devise eur_yuan
			expArg = sqrt(h)*scalarResult*sigma + (this->fx_->computeRate(t + h, this->fx_->txZcEuro) - this->fx_->computeRate(t, this->fx_->txZcEuro) - this->fx_->computeRate(t + h, this->fx_->txZcYuan) + this->fx_->computeRate(t, this->fx_->txZcYuan) - h*(sigma*sigma / 2));
		}
		else{
			expArg = sqrt(h)*scalarResult*sigma + (this->r_->computeRate(t + h) - this->r_->computeRate(t) - h*(sigma*sigma / 2));
		}
	}

	double price = currentPrice * exp(expArg);

	return price;

}

void BS::shift_asset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep, int timeStepSubscription){
	//Clone the in matrix into the out matrix
	pnl_mat_clone(shift_path, path);
	//Calculate the index associate to the time t

	int index;
	if (t <= timestep * timeStepSubscription){
		index = t / timestep;
	}
	else{
		index = timeStepSubscription + 1;
	}

	for (int i = index; i < path->m; ++i){
		MLET(shift_path, i, d) = MGET(shift_path, i, d) * (1 + h);
	}
}

void BS::simul_market(PnlMat *path, double T, int H, PnlRng *rng){

	assert(H != 0);
	//Initialize the first path row with the spot prices
	for (int j = 0; j<this->size_; j++){
		MLET(path, 0, j) = GET(this->spot_, j);
	}
	PnlVect *vectorGaussian;
	vectorGaussian = pnl_vect_create(this->size_);
	for (int i = 1; i<H + 1; i++){
		pnl_vect_rng_normal(vectorGaussian, this->size_, rng);
		//For each assets 
		for (int j = 0; j<this->size_; j++){
			MLET(path, i, j) = this->computeIteration(MGET(path, i - 1, j), T / H, j, vectorGaussian, true, i*(T / H));
		}
	}
	pnl_vect_free(&vectorGaussian);
}
