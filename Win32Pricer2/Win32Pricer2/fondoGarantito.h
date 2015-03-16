#pragma once
#ifndef _FONDOGARANTITO_H
#define _FONDOGARANTITO_H

#include "produit.h"

class FondoGarantito : public Produit
{
public:
	double valeurLiquidativeReference_;

	FondoGarantito(const double T_, const int timeSteps_, const int size_, const double valeurLiquidativeReference_);

	~FondoGarantito();

	double payoff(const PnlMat *path);
};

#endif //_FONDOGARANTITO_H