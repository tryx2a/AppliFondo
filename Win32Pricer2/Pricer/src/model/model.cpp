#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>  
#include "assert.h"
using namespace std;

#include "model.h"

Model::Model(PnlVect *spot_, PnlVect *sigma_,double rho_,Taux* r_,int size_,PnlVect *trend, TauxDeChange *fx, int numberAssetEuro, int numberAssetDollar, int numberAssetYuan)
{
	
	this->spot_= spot_;
	this->sigma_= sigma_;
	this->rho_= rho_;
	this->trend=trend;
	this->r_= r_;
	this->size_= size_;
  this->fx_ = fx;
  this->numberAssetEuro_ = numberAssetEuro;
  this->numberAssetDollar_ = numberAssetDollar;
  this->numberAssetYuan_ = numberAssetYuan;
  //this->isRate = false;
	
}

Model::Model(double *spot_, double *sigma_, double rho_, Taux* r_, int size_, double *trend, TauxDeChange *fx, int numberAssetEuro, int numberAssetDollar, int numberAssetYuan){

	PnlVect* pnl_spot_ = pnl_vect_create_from_ptr(size_, spot_);
	PnlVect* pnl_sigma_ = pnl_vect_create_from_ptr(size_, sigma_);
	PnlVect* pnl_trend = pnl_vect_create_from_ptr(size_, trend);


	this->spot_ = pnl_spot_;
	this->sigma_ = pnl_sigma_;
	this->rho_ = rho_;
	this->trend = pnl_trend;
	this->r_ = r_;
	this->size_ = size_;
	this->fx_ = fx;
	this->numberAssetEuro_ = numberAssetEuro;
	this->numberAssetDollar_ = numberAssetDollar;
	this->numberAssetYuan_ = numberAssetYuan;
}


Model::~Model(){

  if(this->spot_ != NULL){
    pnl_vect_free(&(this->spot_));
  }
  
  if(this->sigma_ != NULL){
    pnl_vect_free(&(this->sigma_));
  }
  cout << "michellllllllllllllllllllll" << endl;
  if(this->r_ != NULL){
    delete this->r_;  
  }
  
  if(this->trend != NULL){
    pnl_vect_free(&(this->trend));
  }
  
  if(this->fx_ != NULL){
    delete this->fx_;  
  }
}

  /**
   * Génère une trajectoire du modèle et la stocke dans path
   *
   * @param[out] path contient une trajectoire du modèle.
   * C'est une matrice de taille (N+1) x d
   * @param[in] T  maturité
   * @param[in] N nombre de dates de constatation
   */
void Model::asset(PnlMat *path, double subscriptionPeriod ,int timeStepSubscription, double T, int N,PnlRng *rng){}

  /**
   * Calcule une trajectoire du sous-jacent connaissant le
   * passé jusqu' à la date t
   *
   * @param[out] path  contient une trajectoire du sous-jacent
   * donnée jusqu'à l'instant T par la matrice past
   * @param[in] t date jusqu'à laquelle on connait la trajectoire
   * t n'est pas forcément une date de discrétisation
   * @param[in] N nombre de pas de constatation
   * @param[in] T date jusqu'à laquelle on simule la trajectoire
   * @param[in] past trajectoire réalisée jusqu'a la date t
   */
void Model::asset(PnlMat *path, double t,double subscriptionPeriod ,int timeStepSubscription, int N, double T,PnlRng *rng, const PnlMat *past){}

  /**
   * Shift d'une trajectoire du sous-jacent
   *
   * @param[in]  path contient en input la trajectoire
   * du sous-jacent
   * @param[out] shift_path contient la trajectoire path
   * dont la composante d a été shiftée par (1+h)
   * à partir de la date t.
   * @param[in] t date à partir de laquelle on shift
   * @param[in] h pas de différences finies
   * @param[in] d indice du sous-jacent à shifter
   * @param[in] timestep pas de constatation du sous-jacent
 	*/
void Model::shift_asset(PnlMat *shift_path, const PnlMat *path,int d, double h, double t, double timestep, int timeStepSubscription){}

  /* Simulation de la couverture
   * @param[out] path contient la trajectoire simulée
   * @param[in] T la maturité (égale à celle de l'option)
   * @param[in] H le nombre de rebalancement de notre portefeuille
   */
 void Model::simul_market(PnlMat *path, double T, int H, PnlRng *rng){}

 /**
 * Calcul la matrice de correlation à partir de données du passé
 * @[in] past : matrice correspondant aux trajectoires passées des actifs
 * @[in] corMat : matrice qui contiendra la matrice de corrélation des actifs
 */
 void Model::computeCorrelation(PnlMat *past, PnlMat* corMat){}