#ifndef _TAUX_H
#define _TAUH_H

#include "pnl/pnl_vector.h"

//Classe Taux abstraite
class Taux
{
public:
	/*
	Constructeur � param�tre
	*/
	Taux();

	/*
	Destructeur
	*/
	virtual ~Taux();

	/*
	Renvoie le taux constat� � la date constatationTime
	*/
	virtual double evaluateRate(double constatationTime) = 0;
	virtual double computeRate(double finalDate) = 0;
};

#endif //_TAUX_H