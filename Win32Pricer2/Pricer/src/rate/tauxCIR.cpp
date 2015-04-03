#include <iostream>
#include <math.h>

using namespace std;

#include "tauxCIR.h"
#include "pnl/pnl_random.h"

TauxCIR::TauxCIR(double a, double b, double volatilityRate, int sizeRate, double initialRate){
	this->a = a;
	this->b = b;
	this->volatilityRate = volatilityRate;
	this->sizeRate = sizeRate;
	this->initialRate = initialRate;
}

TauxCIR::~TauxCIR(){}

PnlVect* TauxCIR::computeRate(){

 	PnlVect* res = pnl_vect_create(this->sizeRate);
	LET(res,0) = this->initialRate ;
 	
 	//Initialisation du taux initial
 	PnlVect* rate = pnl_vect_create(this->sizeRate);

 	//Initialisation generateur aléatoire
 	PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
  	pnl_rng_sseed(rng, 0);

  	for(int j = 0; j < 10000 ; j ++){
 		
 		for(int i = 0; i < this->sizeRate - 1; i++ ){
 			double precRate = GET(rate, i);
 			double tempRes = precRate + this->a*(this->b - precRate);
 			double norme = pnl_rng_normal (rng);
 		
 			double argSqrt = this->volatilityRate*sqrt( precRate )+ (this->volatilityRate*this->volatilityRate/4)*(norme*norme - 1);
 			argSqrt *= norme;

 			LET(rate,i+1) = tempRes + argSqrt;
 			LET(res, i+1) += GET(rate,i+1);
 		}
 	}

 	//Calcul de la moyenne
 	for(int i =0; i < this->sizeRate ; i ++){
 		LET(res,i) = GET(res,i)/10000;
 	}
 	
 	return res;
}

PnlVect* TauxCIR::computeRate(double delta){

 	PnlVect* res = pnl_vect_create(this->sizeRate);
	LET(res,0) = this->initialRate ;
 	
 	//Initialisation du taux initial
 	PnlVect* rate = pnl_vect_create(this->sizeRate);

 	//Initialisation generateur aléatoire
 	PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
  	pnl_rng_sseed(rng, 0);

  	for(int j = 0; j < 10000 ; j ++){
 		
 		for(int i = 0; i < this->sizeRate - 1; i++ ){
 			double precRate = GET(rate, i);
 			double tempRes = precRate + this->a*(this->b - precRate)*delta;
 			double norme = pnl_rng_normal (rng);
 		
 			double argSqrt = this->volatilityRate*sqrt( precRate*delta )+
 			 (this->volatilityRate*this->volatilityRate/4)*delta*(norme*norme - 1); 
 			argSqrt *= norme;

 			LET(rate,i+1) = tempRes + argSqrt;
 			LET(res, i+1) += GET(rate,i+1);
 		}
 	}

 	//Calcul de la moyenne
 	for(int i =0; i < this->sizeRate ; i ++){
 		LET(res,i) = GET(res,i)/10000;
 	}

 	return res;
}
