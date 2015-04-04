
#ifndef _METHOD_H
#define _METHOD_H

#include "../produits/optionBasket.h"
#include "../produits/fondoGarantito.h"
#include "../model/model.h"
#include "pnl/pnl_random.h"
#include "../parser.h"


class Method{
public:
  Model *mod_; /*! pointeur vers le modèle */
  Produit *opt_; /*! pointeur sur l'option */
  PnlRng *rng; /*! pointeur sur le générateur */
  double h_; /*! pas de différence finie */
  int H_; /* nombre de période de rebalancement*/
  int samples_; /*! nombre de tirages Monte Carlo */


  Method(double *spot_, double *sigma_, double rho_, Taux* r_, int size_, double *trend, TauxDeChange *fx, int numberAssetEuro, int numberAssetDollar,
	  int numberAssetYuan, const char *pastData, const double T_, const int timeSteps_, const double valeurLiquidativeOrigine_, const double subscriptionPeriod_,
	  const int timeStepSubscription_, double h_, int H_, int samples_);


  Method(Model *mod, Produit *opt, double h, int H, int samples);

  virtual ~Method();

  /**
   * Calcule le prix de l'option à la date 0
   *
   * @param[out] prix valeur de l'estimateur Monte Carlo
   * @param[out] ic largeur de l'intervalle de confiance
   */
  virtual void price(double &prix, double &ic) = 0;

  /**
   * Calcule le prix de l'option à la date t
   *
   * @param[in]  past contient la trajectoire du sous-jacent
   * jusqu'à l'instant t
   * @param[in] t date à laquelle le calcul est fait
   * @param[out] prix contient le prix
   * @param[out] ic contient la largeur de l'intervalle
   * de confiance sur le calcul du prix
   */
  virtual void price(const PnlMat *past, double t, double &prix, double &ic) = 0;

  /**
   * Calcule le delta de l'option à la date t
   *
   * @param[in] past contient la trajectoire du sous-jacent
   * jusqu'à l'instant t
   * @param[in] t date à laquelle le calcul est fait
   * @param[out] delta contient le vecteur de delta
   * @param[out] ic contient la largeur de l'intervalle
   * de confiance sur le calcul du delta
   */
  virtual void delta(const PnlMat *past, double t, PnlVect *delta, PnlVect *ic) = 0;

  
  /**
   * Cette méthode permet de calculer le profit & loss d'un produit pour un certain nombre
   * de rebalancement précisé dans le fichier .dat
   *
   * @param[in] V vecteur contenant pour chaque date de rebalancement l'investissement
   * au taux sans risque
   * @param[in] T maturité du produit
   * @param[in] portfolio vecteur contenant la composition du portefeuille de couverture du produit à chaque date de rebalancement
   * @param[in] price vecteur contenant le prix du produit à chaque date de rebalancement
   */
  void freeRiskInvestedPart(PnlVect *V,double T, PnlVect *portfolio, PnlVect *price);

  /**
   * Cette méthode calcule la part investit au taux sans risque à un un instant tho donné correspondant à une date de rebalancement
   *
   * @param[in] V double correspondant à la part investit au taux sans risque
   * @param[in] T double correspondant à la maturité du produit
   * @param[in] portfolio double correspondant à la valeur du portefeuille de couverture
   * @param[in] price double correspondant au prix du produit
   * @param[in] delta vecteur correspondant à la part à investir dans chaque actif risqué pour se couvrir
   * @param[in] tho double correspondant à une date de rebalancement
   * @param[in] past matrice correspondant aux trajectoires passées des actifs risqués
   */
  void freeRiskInvestedPart(double &V, double T, double &portfolio, double &price, PnlVect *delta, double tho, PnlMat *past);
};

#endif /* !_METHOD_H */