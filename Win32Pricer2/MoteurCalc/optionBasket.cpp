#include <iostream>
#include <assert.h> 

using namespace std;

#include "optionBasket.h"

/**
* Constructeur de la classe OptionBasket
*/
OptionBasket::OptionBasket(const double T_, const int timeSteps_, const int size_, const double strike_, const PnlVect* payoffCoeff_) : Produit(T_, timeSteps_, size_){
	this->strike_ = strike_;
	this->payoffCoeff_ = pnl_vect_copy(payoffCoeff_);
}

/**
* Destructeur de la classe OptionBasket
*/
OptionBasket::~OptionBasket(){
	if (&(this->payoffCoeff_) != NULL)
		pnl_vect_free(&(this->payoffCoeff_));
}

/**
* Implémentation de la méthode de payoff
*/
double OptionBasket::payoff(const PnlMat *path){

	double res = 0.0;

	int i;
	PnlVect * assetAtMaturity = pnl_vect_new();

	//On extrait la ligne                                                                                                                                                            
	pnl_mat_get_row(assetAtMaturity, path, TimeSteps_);

	assert(assetAtMaturity->size == payoffCoeff_->size);

	for (int i = 0; i<assetAtMaturity->size; i++){
		res += GET(assetAtMaturity, i)*GET(payoffCoeff_, i);
	}

	pnl_vect_free(&assetAtMaturity);

	res -= this->strike_;

	if (res <= 0.0){
		return 0.0;
	}

	return res;
}
