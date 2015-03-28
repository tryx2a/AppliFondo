
#ifndef _METHOD_H
#define _METHOD_H

#include "fondoGarantito.h"
#include "model.h"
#include "pnl/pnl_random.h"


class Method{
public:
	Model *mod_; /*! pointeur vers le modèle */
	Produit *opt_; /*! pointeur sur l'option */
	PnlRng *rng; /*! pointeur sur le générateur */
	double h_; /*! pas de différence finie */
	int H_; /* nombre de période de rebalancement*/
	int samples_; /*! nombre de tirages Monte Carlo */

	Method(Model *mod, Produit *opt, double h, int H, int samples);

	//Method(Param* P);

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
	* Cette méthode créée et retourne la bonne instance d'option
	* en fonction de la key passée en paramètre.
	*
	* @param[in] P contient les données nécessaire pour
	* la création de l'option
	* @param[out] retourne la bonne instance d'option
	*/
	//static Produit* createOption(Param *P);

	/**
	* Cette méthode permet de calculer le profit & loss d'un produit pour un certain nombre
	* de rebalancement précisé dans le fichier .dat
	*
	* @param[in] V vecteur contenant pour chaque date de rebalancement l'investissement
	* au taux sans risque
	* @param[in] T maturité du produit
	* @param[in] profitLoss variable contenant le profit & loss final du produit
	*/
	void freeRiskInvestedPart(PnlVect *V, double T, double &profitLoss);

	/**
	* Cette méthode calcule la part investit au taux sans risque à un un instant tho donné correspondant à une date de rebalancement
	*
	* @param[in] V double correspondant à la part investit au taux sans risque
	* @param[in] T double correspondant à la maturité du produit
	* @param[in] portfolio double correspondant à la valeur du portefeuille de couverture
	* @param[in] payoff double correspondant à la valeur du payoff
	* @param[in] delta vecteur correspondant à la part à investir dans chaque actif risqué pour se couvrir
	* @param[in] tho double correspondant à une date de rebalancement
	* @param[in] past matrice correspondant aux trajectoires passées des actifs risqués
	*/
	void freeRiskInvestedPart(double &V, double T, double &portfolio, double &payoff, PnlVect *delta, double tho, PnlMat *past);
};

#endif /* !_METHOD_H */