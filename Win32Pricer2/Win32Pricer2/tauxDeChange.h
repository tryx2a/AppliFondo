#ifndef _TAUXDECHANGE_H
#define _TAUXDECHANGE_H

#include "pnl/pnl_vector.h"

class TauxDeChange
{
public:

	PnlVect* txZcEuro;
	PnlVect* txZcDollar;
	PnlVect* txZcYuan;

	TauxDeChange();
	TauxDeChange(double* fxUsdEur, double* fxYuanEur);
	~TauxDeChange();

	double Devise_eur_doll(double time);
	double Devise_eur_yuan(double time);

	double evaluateInterpolationRate(double t, PnlVect* vectZC);
	double computeRate(double finalDate, PnlVect* vectZC);

};

#endif //_TAUXDECHANGE_H