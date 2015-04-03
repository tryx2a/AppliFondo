#include <iostream>

using namespace std;

#include "fondoGarantito.h"

/**
* Constructeur de la classe FondoGarantito
*/
FondoGarantito::FondoGarantito(const double T_, const int timeSteps_, const int size_, const double valeurLiquidativeOrigine_, const double subscriptionPeriod_, const int timeStepSubscription_) : Produit(T_, timeSteps_, size_){
	this->valeurLiquidativeOrigine_ = valeurLiquidativeOrigine_;
	this->subscriptionPeriod_ = subscriptionPeriod_;
	this->timeStepSubscription_ = timeStepSubscription_;
}

/**
* Destructeur de la classe FondoGarantito
*/
FondoGarantito::~FondoGarantito(){}

/**
* Calcul la VLR sur la période de soucription du produit financier
*/
double FondoGarantito::computeVLR(const PnlMat *path){
	PnlVect *assetAtSpot = pnl_vect_new();
	pnl_mat_get_row(assetAtSpot, path, 0);

	double valeurLiquidativeReference = 0.0;
	double rentabilite = 0.0;
	double rentabiliteMax = 0.0;

	for (int i = 1; i <= this->timeStepSubscription_; i++){
		for (int j = 0; j<this->size_; j++){
			rentabilite += MGET(path, i, j) / GET(assetAtSpot, j) - 1.0;
		}
		rentabilite /= this->size_;
		if (rentabilite > rentabiliteMax){
			rentabiliteMax = rentabilite;
		}
	}

	pnl_vect_free(&assetAtSpot);

	return this->valeurLiquidativeOrigine_*(1 + rentabiliteMax);
}

/**
* Implémentation de la méthode de payoff
*/
double FondoGarantito::payoff(const PnlMat *path){
	double gamma = 0.0;
	double rentabiliteAsset = 0.0;

	PnlVect *assetAtMaturity = pnl_vect_new();
	PnlVect *assetAtSpot = pnl_vect_new();

	//Extraction des valeurs des actifs en date de constatation finale
	pnl_mat_get_row(assetAtMaturity, path, TimeSteps_ + timeStepSubscription_);

	//Extraction des valeurs des actifs en date de constatation initiale
	pnl_mat_get_row(assetAtSpot, path, timeStepSubscription_);

	for (int i = 0; i<assetAtMaturity->size; i++){
		rentabiliteAsset = GET(assetAtMaturity, i) / GET(assetAtSpot, i) - 1.0;

		if (rentabiliteAsset > 0.375){
			gamma += 0.375;
		}
		else if (rentabiliteAsset >= -0.1 && rentabiliteAsset < 0.0){
			gamma -= rentabiliteAsset;
		}
		else{
			gamma += rentabiliteAsset;
		}

	}

	gamma = gamma / assetAtMaturity->size;

	pnl_vect_free(&assetAtMaturity);
	pnl_vect_free(&assetAtSpot);

	if (gamma < 0.0){
		gamma = 0.0;
	}

	double VLR = computeVLR(path);
	double payoff = VLR*(1 + gamma);


	return payoff;
}