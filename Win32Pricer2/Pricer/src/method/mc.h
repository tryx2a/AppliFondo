#ifndef _MC_H
#define _MC_H

#include "../produits/optionBasket.h"
#include "../produits/fondoGarantito.h"
#include "../model/bs.h"
#include "pnl/pnl_random.h"
#include "../parser.h"
#include "method.h"

class MonteCarlo : public Method
{
public:


	MonteCarlo(double *spot_, double *sigma_, double rho_, Taux* r_, int size_, double *trend, TauxDeChange *fx, int numberAssetEuro, int numberAssetDollar,
		int numberAssetYuan, const char *pastData, const double T_, const int timeSteps_, const double valeurLiquidativeOrigine_, const double subscriptionPeriod_,
		const int timeStepSubscription_, double h_, int H_, int samples_);

  /*
   * Constructeur MonteCarlo
   */
	MonteCarlo(Model *mod, Produit *opt, double h, int H, int samples);

  /**
   * Calcule le prix de l'option � la date 0
   *
   * @param[out] prix valeur de l'estimateur Monte Carlo
   * @param[out] ic largeur de l'intervalle de confiance
   */
  void price(double &prix, double &ic);

  /**
   * Calcule le prix de l'option � la date t
   *
   * @param[in]  past contient la trajectoire du sous-jacent
   * jusqu'� l'instant t
   * @param[in] t date � laquelle le calcul est fait
   * @param[out] prix contient le prix
   * @param[out] ic contient la largeur de l'intervalle
   * de confiance sur le calcul du prix
   */
  void price(const PnlMat *past, double t, double &prix, double &ic);

  /**
   * Calcule le delta de l'option � la date t
   *
   * @param[in] past contient la trajectoire du sous-jacent
   * jusqu'� l'instant t
   * @param[in] t date � laquelle le calcul est fait
   * @param[out] delta contient le vecteur de delta
   * @param[out] ic contient la largeur de l'intervalle
   * de confiance sur le calcul du delta
   */
  void delta(const PnlMat *past, double t, PnlVect *delta, PnlVect *ic);


};

#endif /* _MC_H */

