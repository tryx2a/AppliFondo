#include <iostream>

using namespace std;

#include "fondoGarantito.h"

/**
* Constructeur de la classe FondoGarantito
*/
FondoGarantito::FondoGarantito(const double T_, const int timeSteps_, const int size_, const double valeurLiquidativeReference_) : Produit(T_, timeSteps_, size_){
	this->valeurLiquidativeReference_ = valeurLiquidativeReference_;
}

/**
* Destructeur de la classe FondoGarantito
*/
FondoGarantito::~FondoGarantito(){}

/**
* Implémentation de la méthode de payoff
*/
double FondoGarantito::payoff(const PnlMat *path){
	double gamma = 0.0;
	double rentabiliteAsset = 0.0;

	PnlVect *assetAtMaturity = pnl_vect_new();
	PnlVect *assetAtSpot = pnl_vect_new();

	//Extraction des valeurs des actifs à maturité
	pnl_mat_get_row(assetAtMaturity, path, TimeSteps_);

	//Extraction des valeurs des actifs en t=0
	pnl_mat_get_row(assetAtSpot, path, 0);

	for (int i = 0; i<assetAtMaturity->size; i++){
		rentabiliteAsset = GET(assetAtMaturity, i) / GET(assetAtSpot, i) - 1;

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

	return this->valeurLiquidativeReference_*(1 + gamma);
}