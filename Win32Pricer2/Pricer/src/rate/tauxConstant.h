#ifndef _TAUXCONSTANT_H
#define _TAUXCONSTANT_H

#include "taux.h"

class TauxConstant : public Taux
{
public:
  
  double r_;

  TauxConstant(double r);
  ~TauxConstant();

  double evaluateRate(double constatationTime);
  double computeRate(double finalDate);
  
};

#endif //_TAUXCONSTANT_H