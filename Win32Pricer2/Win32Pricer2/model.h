#ifndef _MODEL_H
#define _MODEL_H

#include "tauxLPM.h"
#include "tauxDeChange.h"

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

class Model{
public:
	int size_; /// nombre d'actifs du mod�le
	Taux* r_; /// taux d'int�r�t
	TauxDeChange *fx_; ///taux de change eur_doll et eur_yuan
	PnlVect *trend; /// trend des actifs du march�
	double rho_; /// param�tre de corr�lation
	PnlVect *sigma_; /// vecteur de volatilit�s
	PnlVect *spot_; /// valeurs initiales du sous-jacent
	int numberAssetEuro_; /// Nombre d'actifs en devise Euro 
	int numberAssetDollar_; /// Nombre d'actifs en devise Dollar
	int numberAssetYuan_; /// Nombre d'actifs en devise Yuan

	//bool isRate; ///Boolean permettant de d�terminer si on simule un taux de change

	Model(PnlVect *spot_, PnlVect *sigma_, double rho_, Taux* r_, int size_, PnlVect *trend, TauxDeChange *fx, int numberAssetEuro, int numberAssetDollar, int numberAssetYuan);
	Model(double *spot_, double *sigma_, double rho_, Taux* r_, int size_, double *trend, TauxDeChange *fx,
		int numberAssetEuro, int numberAssetDollar, int numberAssetYuan);

	virtual ~Model();

	/**
	* G�n�re une trajectoire du mod�le et la stocke dans path
	*
	* @param[out] path contient une trajectoire du mod�le.
	* C'est une matrice de taille (N+1) x d
	* @param[in] T  maturit�
	* @param[in] N nombre de dates de constatation
	*/
	virtual void asset(PnlMat *path, double subscriptionPeriod, int timeStepSubscription, double T, int N, PnlRng *rng);

	/**
	* Calcule une trajectoire du sous-jacent connaissant le
	* pass� jusqu' � la date t
	*
	* @param[out] path  contient une trajectoire du sous-jacent
	* donn�e jusqu'� l'instant T par la matrice past
	* @param[in] t date jusqu'� laquelle on connait la trajectoire
	* t n'est pas forc�ment une date de discr�tisation
	* @param[in] N nombre de pas de constatation
	* @param[in] T date jusqu'� laquelle on simule la trajectoire
	* @param[in] past trajectoire r�alis�e jusqu'a la date t
	*/
	virtual void asset(PnlMat *path, double t, double subscriptionPeriod, int timeStepSubscription, int N, double T, PnlRng *rng, const PnlMat *past);

	/**
	* Shift d'une trajectoire du sous-jacent
	*
	* @param[in]  path contient en input la trajectoire
	* du sous-jacent
	* @param[out] shift_path contient la trajectoire path
	* dont la composante d a �t� shift�e par (1+h)
	* � partir de la date t.
	* @param[in] t date � partir de laquelle on shift
	* @param[in] h pas de diff�rences finies
	* @param[in] d indice du sous-jacent � shifter
	* @param[in] timestep pas de constatation du sous-jacent
	*/
	virtual void shift_asset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep, int timeStepSubscription);

	/* Simulation de la couverture
	* @param[out] path contient la trajectoire simul�e
	* @param[in] T la maturit� (�gale � celle de l'option)
	* @param[in] H le nombre de rebalancement de notre portefeuille
	*/
	virtual void simul_market(PnlMat *path, double T, int H, PnlRng *rng);

};

#endif /* _MODEL_H */
