#ifndef _FONDOGARANTITO_H
#define _FONDOGARANTITO_H

#include "produit.h"

class FondoGarantito : public Produit
{
public:
	double valeurLiquidativeOrigine_;
	double subscriptionPeriod_;
	int timeStepSubscription_;

	/**
	* Constructeur du FondoGarantito
	*
	* @param[in] T_ : correspond � maturit� du produit.
	*
	* @param[in] timeSteps_ : nombre de date de constation sur la p�riode mentionn�e au dessus.
	*
	* @param[in] size_ : taille du produit
	*
	* @param[in] valeurLiquidativeOrigine_ : valeur liquidative de r�f�rence du produit, elle est
	* initialis�e � la valeur liquidative d'origine du produit (1000�).
	*/
	FondoGarantito(const double T_, const int timeSteps_, const int size_, const double valeurLiquidativeOrigine_, const double subscriptionPeriod_, const int timeStepSubscription_);

	~FondoGarantito();

	double payoff(const PnlMat *path);

	double computeVLR(const PnlMat *path);
};

#endif //_FONDOGARANTITO_H