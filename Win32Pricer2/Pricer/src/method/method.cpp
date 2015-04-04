#include "method.h"
#include "../model/bs.h"
#include <cstring>
#include <math.h>
#include <ctime>
#include "../rate/tauxLPM.h"
#include "../rate/tauxDeChange.h"
#include <iostream>

using namespace std;

Method::Method(double *spot_, double *sigma_, double rho_, Taux* r_, int size_, double *trend, TauxDeChange *fx, int numberAssetEuro, int numberAssetDollar,
	int numberAssetYuan, const char *pastData, const double T_, const int timeSteps_, const double valeurLiquidativeOrigine_, const double subscriptionPeriod_,
	const int timeStepSubscription_, double h_, int H_, int samples_){

	this->h_ = h_;
	this->H_ = H_;
	this->samples_ = samples_;

	this->mod_ = new BS(spot_, sigma_, rho_, r_, size_, trend, fx, numberAssetEuro, numberAssetDollar, numberAssetYuan, pastData);
	this->opt_ = new FondoGarantito(T_, timeSteps_, size_, valeurLiquidativeOrigine_, subscriptionPeriod_, timeStepSubscription_);

	this->rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(this->rng, std::time(NULL));
}

Method::Method(Model *mod, Produit *opt, double h, int H, int samples)
{
	this->mod_ = mod;
	this->opt_ = opt;
	this->rng = rng;
	this->h_ = h;
	this->H_ = H;
	this->samples_ = samples;

	this->rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(this->rng, std::time(NULL));
}

Method::~Method(){
	
  delete this->mod_;
  delete this->opt_;
  pnl_rng_free(&(this->rng));
}

/* Cette méthode permet de calculer le profit & loss d'un produit pour un certain nombre
 * de rebalancement précisé dans le fichier .dat
 */
void Method::freeRiskInvestedPart(PnlVect *V, double T, PnlVect *portfolio, PnlVect *price){
  FondoGarantito *fg = dynamic_cast<FondoGarantito*>(opt_);
  PnlMat *simulMarketResult, *tempMarketResult, *path;
  simulMarketResult = pnl_mat_create(this->H_+1,this->mod_->size_);
  path = pnl_mat_create(this->H_+1,this->mod_->size_);
  
  //Simulate H+1 values from 0 to T (market values)
  mod_->simul_market(simulMarketResult,T,this->H_,this->rng);

  PnlVect* precDelta, *copydelta_i;
      
  //Current Time of iteration
  double tho=0.0;
  
  /* Compute V_0 */
  //Compute Price
  
  double refprice,refic;
  
  this->price(refprice,refic);
  
  cout << "price : " << refprice << endl;
  //Compute delta_0
  PnlVect* delta,*ic;
  delta = pnl_vect_create(this->mod_->size_);
  ic = pnl_vect_create(this->mod_->size_);
  this->delta(simulMarketResult,tho,delta,ic);
  /*for (int k = 0; k < path->m; k++){
	  for (int l = 0; l < path->n; l++){
		  std::cout << simulMarketResult->array[k*path->m + l];
	  }
	  std::cout << std::endl;
  }*/
  cout<<"delta : "<< tho<<endl;
  pnl_vect_print(delta);

  //On récupère S_0
  PnlVect *s;
  s = pnl_vect_create(this->mod_->size_);
  pnl_mat_get_row(s,simulMarketResult,0);

  //On calcul V_0
  LET(V,0) = refprice - pnl_vect_scalar_prod(delta,s);
  precDelta = pnl_vect_copy(delta); //on sauvergarde le delta qu'on vient de calculer
  LET(portfolio, 0) = GET(V,0)+pnl_vect_scalar_prod(precDelta,s);
  LET(price, 0) = refprice;

  /* Compute V_i */
  
  for(int i = 1; i<V->size; i++){
    //On incrémente tho du pas de discrétisation de la simulation de marché à savoir T/H
    tho += T/((double) this->H_);
    cout<<"tho : "<<tho<<endl;

    //Extract the row from 0 to tho "time"
    tempMarketResult = pnl_mat_create(i+1,this->mod_->size_);
    //pnl_mat_extract_subblock(tempMarketResult, simulMarketResult, 0, i+1, 0, this->mod_->size_);
	for (int k = 0; k < this->mod_->size_; k++){
		for (int l = 0; l < i + 1; l++){
			MLET(tempMarketResult, k, l) = MGET(simulMarketResult,k,l);
		}
	}

    //Compute delta_i
    this->delta(tempMarketResult, tho, delta, ic);
    cout<<"delta : "<<tho<<endl;
    pnl_vect_print(delta);

    copydelta_i = pnl_vect_copy(delta);
    pnl_vect_minus_vect(copydelta_i,precDelta);
    pnl_mat_get_row(s,simulMarketResult,i);
    LET(V,i) = GET(V,i-1)*exp(mod_->r_->computeRate(this->opt_->T_ / ((double) this->H_) ) ) - pnl_vect_scalar_prod(copydelta_i,s);

    pnl_vect_free(&precDelta);
    precDelta = pnl_vect_copy(delta);

    LET(portfolio, i) = GET(V,i)+pnl_vect_scalar_prod(precDelta,s);
    this->price(tempMarketResult, tho, refprice, refic);
    LET(price, i) = refprice;

    pnl_vect_free(&copydelta_i);
    pnl_mat_free(&tempMarketResult);
  }

  pnl_vect_free(&s);
  pnl_vect_free(&delta);
  pnl_vect_free(&ic);
  pnl_vect_free(&precDelta);
  pnl_mat_free(&simulMarketResult);
  pnl_mat_free(&path);
  
}


void Method::freeRiskInvestedPart(double &V, double T, double &portfolio, double &price, PnlVect *delta, double tho, PnlMat *past){
    
  FondoGarantito *fg = dynamic_cast<FondoGarantito*>(opt_);
  PnlMat *path = pnl_mat_create(this->H_+1,this->mod_->size_);

  if(tho == 0.0){
    //Calcul du prix
    double refprice,refic;
    this->price(refprice,refic);
    cout<<"price : "<<refprice<<endl;

    //Compute delta_0
    PnlVect *ic;
    ic = pnl_vect_create(this->mod_->size_);
    this->delta(past,tho,delta,ic);

    //On récupère S_0
    PnlVect *s;
    s = pnl_vect_create(this->mod_->size_);
    pnl_mat_get_row(s,past,0);

    //On calcul V_0
    V = refprice - pnl_vect_scalar_prod(delta,s);
    std::cout<<"V : "<<V<<std::endl;
    portfolio = V + pnl_vect_scalar_prod(delta,s);
    price = refprice;

    pnl_vect_free(&s);
    pnl_vect_free(&ic);
  }
  else{

    PnlVect *precDelta = pnl_vect_copy(delta);
    PnlVect *ic = pnl_vect_create(this->mod_->size_);
    PnlVect *copyDelta;
    PnlVect *s = pnl_vect_create(this->mod_->size_);
    double precV = V;

    //On calcule le nouveau delta
    this->delta(past, tho, delta, ic);

    //Calcul de la différence entre ce delta et le précédant
    copyDelta = pnl_vect_copy(delta);
    pnl_vect_minus_vect(copyDelta,precDelta);
    pnl_mat_get_row(s,past,past->m-1);

    //Calcul de la part investit au taux sans risque
    V = precV*exp(mod_->r_->computeRate(this->opt_->T_ / ((double) this->H_) ) ) - pnl_vect_scalar_prod(copyDelta,s);
    std::cout<<"V : "<<V<<std::endl;
    portfolio = V + pnl_vect_scalar_prod(delta,s);


    double refic;
    this->price(past, tho, price, refic);

    pnl_vect_free(&precDelta);
    pnl_vect_free(&copyDelta);
    pnl_vect_free(&ic);
    pnl_vect_free(&s);

  }
  pnl_mat_free(&path);
}

