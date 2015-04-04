#ifndef _TAUXVASICEK_H
#define _TAUXVASICEK_H

#include "pnl/pnl_vector.h"

class TauxVasicek
{
public:
  
  //dr = a(b-r)dt + voldBt
  
  double a;
  double b;
  double volatilityRate;
  int sizeRate;
  double initialRate;

  TauxVasicek(double a, double b, double volatilityRate, int sizeRate, double initialRate);
  ~TauxVasicek();

  PnlVect* computeRate();
  PnlVect* computeRate(double delta);
  
};

#endif //_TAUXVASICEK_H