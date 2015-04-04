#ifndef _TAUXCIR_H
#define _TAUXCIR_H

#include "pnl/pnl_vector.h"

class TauxCIR
{
public:
  
  //dr = a(b-r)dt + voldBt
  
  double a;
  double b;
  double volatilityRate;
  int sizeRate;
  double initialRate;

  TauxCIR(double a, double b, double volatilityRate, int sizeRate, double initialRate);
  ~TauxCIR();

  PnlVect* computeRate();
  PnlVect* computeRate(double delta);
  

};

#endif //_TAUXCIR_H