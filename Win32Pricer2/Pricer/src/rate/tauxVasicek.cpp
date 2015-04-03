#include <iostream>
#include <math.h>

using namespace std;

#include "tauxVasicek.h"
#include "pnl/pnl_random.h"

TauxVasicek::TauxVasicek(double a, double b, double volatilityRate, int sizeRate, double initialRate){
	this->a = a;
	this->b = b;
	this->volatilityRate = volatilityRate;
	this->sizeRate = sizeRate;
	this->initialRate = initialRate;
}

TauxVasicek::~TauxVasicek(){}

PnlVect* TauxVasicek::computeRate(){
 	
 	PnlVect* rate = pnl_vect_create(this->sizeRate);

 	//Initialisation du taux initial
 	LET(rate,0) = this->initialRate;

 	//Initialisation generateur aléatoire
 	PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
  	pnl_rng_sseed(rng, 0);

 	for(int i = 0; i < this->sizeRate - 1; i++ ){
 		
 		double precRate = GET(rate, i);
 		double tempRes = precRate*exp(-this->a) + this->b*(1-exp(-this->a));
 		
 		double norme = pnl_rng_normal (rng);
 		
 		double argSqrt = this->volatilityRate*sqrt( (1-exp(-2*this->a)) / (2*this->a) ) ;
 		argSqrt *= norme;

 		LET(rate,i+1) = tempRes + argSqrt;
 	}

	cout<<"Fin de Vasicek"<<endl;
 	return rate;
}

PnlVect* TauxVasicek::computeRate(double delta){
 	
 	PnlVect* rate = pnl_vect_create(this->sizeRate);

 	//Initialisation du taux initial
 	LET(rate,0) = this->initialRate;

 	//Initialisation generateur aléatoire
 	PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
  	pnl_rng_sseed(rng, 0);

 	for(int i = 0; i < this->sizeRate - 1; i++ ){
 		
 		double precRate = GET(rate, i);
 		double tempRes = precRate*exp(-this->a * delta) + this->b*(1-exp(-this->a * delta));
 		
 		double norme = pnl_rng_normal (rng);
 		
 		double argSqrt = this->volatilityRate*sqrt( (1-exp(-2*this->a * delta)) / (2*this->a) ) ;
 		argSqrt *= norme;

 		LET(rate,i+1) = tempRes + argSqrt;
 	}

 	cout<<"Fin de Vasicek"<<endl;
 	return rate;
}