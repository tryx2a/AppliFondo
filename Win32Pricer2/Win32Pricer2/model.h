#pragma once
#ifndef _MODEL_H
#define _MODEL_H

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

class Model{
public:
	int size_; /// nombre d'actifs du modèle
	double r_; /// taux d'intérêt
	PnlVect *trend; /// trend des actifs du marché
	double rho_; /// paramètre de corrélation
	PnlVect *sigma_; /// vecteur de volatilités
	PnlVect *spot_; /// valeurs initiales du sous-jacent

	Model(PnlVect *spot_, PnlVect *sigma_, double rho_, double r_, int size_, PnlVect *trend);
	
	

	virtual ~Model();

	/**
	* Génère une trajectoire du modèle et la stocke dans path
	*
	* @param[out] path contient une trajectoire du modèle.
	* C'est une matrice de taille (N+1) x d
	* @param[in] T  maturité
	* @param[in] N nombre de dates de constatation
	*/
	virtual void asset(PnlMat *path, double T, int N, PnlRng *rng);

	/**
	* Calcule une trajectoire du sous-jacent connaissant le
	* passé jusqu' à la date t
	*
	* @param[out] path  contient une trajectoire du sous-jacent
	* donnée jusqu'à l'instant T par la matrice past
	* @param[in] t date jusqu'à laquelle on connait la trajectoire
	* t n'est pas forcément une date de discrétisation
	* @param[in] N nombre de pas de constatation
	* @param[in] T date jusqu'à laquelle on simule la trajectoire
	* @param[in] past trajectoire réalisée jusqu'a la date t
	*/
	virtual void asset(PnlMat *path, double t, int N, double T, PnlRng *rng, const PnlMat *past);

	/**
	* Shift d'une trajectoire du sous-jacent
	*
	* @param[in]  path contient en input la trajectoire
	* du sous-jacent
	* @param[out] shift_path contient la trajectoire path
	* dont la composante d a été shiftée par (1+h)
	* à partir de la date t.
	* @param[in] t date à partir de laquelle on shift
	* @param[in] h pas de différences finies
	* @param[in] d indice du sous-jacent à shifter
	* @param[in] timestep pas de constatation du sous-jacent
	*/
	virtual void shift_asset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep);

	/* Simulation de la couverture
	* @param[out] path contient la trajectoire simulée
	* @param[in] T la maturité (égale à celle de l'option)
	* @param[in] H le nombre de rebalancement de notre portefeuille
	*/
	virtual void simul_market(PnlMat *path, double T, int H, PnlRng *rng);

};

#endif /* _MODEL_H */
