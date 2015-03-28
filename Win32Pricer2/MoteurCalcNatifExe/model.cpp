#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>  
#include "assert.h"
using namespace std;

#include "model.h"

Model::Model(PnlVect *spot_, PnlVect *sigma_, double rho_, Taux* r_, int size_, PnlVect *trend, TauxDeChange *fx, int numberAssetEuro, int numberAssetDollar, int numberAssetYuan)
{
	this->spot_ = spot_;
	this->sigma_ = sigma_;
	this->rho_ = rho_;
	this->trend = trend;
	this->r_ = r_;
	this->size_ = size_;
	this->fx_ = fx;
	this->numberAssetEuro_ = numberAssetEuro;
	this->numberAssetDollar_ = numberAssetDollar;
	this->numberAssetYuan_ = numberAssetYuan;
	//this->isRate = false;

}

Model::Model(double *spot_, double *sigma_, double rho_, Taux* r_, int size_, double *trend, TauxDeChange *fx,
	int numberAssetEuro, int numberAssetDollar, int numberAssetYuan)
{
	this->spot_ = pnl_vect_create_from_ptr(size_, spot_);
	this->sigma_ = pnl_vect_create_from_ptr(size_, sigma_);
	this->rho_ = rho_;
	this->trend = pnl_vect_create_from_ptr(size_, trend);
	this->r_ = r_;
	this->size_ = size_;
	this->fx_ = fx;
	this->numberAssetEuro_ = numberAssetEuro;
	this->numberAssetDollar_ = numberAssetDollar;
	this->numberAssetYuan_ = numberAssetYuan;
	//this->isRate = false;
}
Model::~Model(){

	if (this->spot_ != NULL){
		pnl_vect_free(&(this->spot_));
	}
	if (this->sigma_ != NULL){
		pnl_vect_free(&(this->sigma_));
	}
	if (this->r_ != NULL){
		delete this->r_;
	}
	if (this->trend != NULL){
		pnl_vect_free(&(this->trend));
	}
	if (this->fx_ != NULL){
		delete this->fx_;
	}
}

/**
* G�n�re une trajectoire du mod�le et la stocke dans path
*
* @param[out] path contient une trajectoire du mod�le.
* C'est une matrice de taille (N+1) x d
* @param[in] T  maturit�
* @param[in] N nombre de dates de constatation
*/
void Model::asset(PnlMat *path, double subscriptionPeriod, int timeStepSubscription, double T, int N, PnlRng *rng){}

/**
* Calcule une trajectoire du sous-jacent connaissant le
* pass� jusqu' � la date t
*
* @param[out] path  contient une trajectoire du sous-jacent
* donn�e jusqu'� l'instant T par la matrice past
* @param[in] t date jusqu'� laquelle on connait la trajectoire
* t n'est pas forc�ment une date de discr�tisation
* @param[in] N nombre de pas de constatation
* @param[in] T date jusqu'� laquelle on simule la trajectoire
* @param[in] past trajectoire r�alis�e jusqu'a la date t
*/
void Model::asset(PnlMat *path, double t, double subscriptionPeriod, int timeStepSubscription, int N, double T, PnlRng *rng, const PnlMat *past){}

/**
* Shift d'une trajectoire du sous-jacent
*
* @param[in]  path contient en input la trajectoire
* du sous-jacent
* @param[out] shift_path contient la trajectoire path
* dont la composante d a �t� shift�e par (1+h)
* � partir de la date t.
* @param[in] t date � partir de laquelle on shift
* @param[in] h pas de diff�rences finies
* @param[in] d indice du sous-jacent � shifter
* @param[in] timestep pas de constatation du sous-jacent
*/
void Model::shift_asset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep, int timeStepSubscription){}

/* Simulation de la couverture
* @param[out] path contient la trajectoire simul�e
* @param[in] T la maturit� (�gale � celle de l'option)
* @param[in] H le nombre de rebalancement de notre portefeuille
*/
void Model::simul_market(PnlMat *path, double T, int H, PnlRng *rng){}