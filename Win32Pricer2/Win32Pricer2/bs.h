#pragma once
#ifndef _BS_H
#define _BS_H

#include "model.h"

/// \brief Mod�le de Black Scholes
class BS : public Model
{
public:
	PnlMat *chol; /// matrice de cholesky calcul� dans le constructeur

	BS(PnlVect *spot_, PnlVect *sigma_, double rho_, double r_, int size_, PnlVect *trend);
	

	~BS();

	/**
	* G�n�re une trajectoire du mod�le et la stocke dans path
	*
	* @param[out] path contient une trajectoire du mod�le.
	* C'est une matrice de taille (N+1) x d
	* @param[in] T  maturit�
	* @param[in] N nombre de dates de constatation
	*/
	void asset(PnlMat *path, double T, int N, PnlRng *rng);

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
	void asset(PnlMat *path, double t, int N, double T, PnlRng *rng, const PnlMat *past);

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
	void shift_asset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep);

	/**
	* Compute Cholesky factorization for the identity matrix
	* @param[out] Return the cholesky factorized matrix
	* @param[in] rho_ param�tre de corr�lation
	*/
	void computeCholesky(PnlMat *L, double rho_);

	/**
	* Shift d'une trajectoire du sous-jacent
	*
	* @param[in]  currentPrice
	* @param[in]  h
	* @param[in]  assetIndex
	* @param[out] computedPrice
	*/
	double computeIteration(double currentPrice, double h, int assetIndex, PnlVect* vectorGaussian, bool useTrend);


	/**
	* Simulation de la couverture
	* @param[out] path contient la trajectoire simul�e
	* @param[in] T la maturit� (�gale � celle de l'option)
	* @param[in] H le nombre de rebalancement de notre portefeuille
	*/
	void simul_market(PnlMat *path, double T, int H, PnlRng *rng);

};


#endif /* _BS_H */

