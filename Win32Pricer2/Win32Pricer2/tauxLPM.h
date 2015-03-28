#ifndef _TAUXLPM_H
#define _TAUXLPM_H

#include "taux.h"

class TauxLPM : public Taux
{
public:

	PnlVect* vectZC;

	TauxLPM();
	TauxLPM(double *r);
	~TauxLPM();

	double evaluateRate(double constatationTime);

	double computeRate(double finalDate);
};

#endif