#pragma once
#ifndef _PRODUIT_H
#define _PRODUIT_H

#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

/// \brief Classe Produit abstraite
class Produit
{
public:
	double T_; /// maturité
	int TimeSteps_; /// nombre de pas de temps de discrétisation
	int size_; /// dimension du modèle, redondant avec BS::size_

	/**
	* Constructeur de la classe Produit
	*/
	Produit(const double T_, const int TimeSteps_, const int size);

	/**
	* Destructeur de la classe Produit
	*/
	virtual ~Produit();

	/**
	* Calcule la valeur du payoff sur la trajectoire
	*
	* @param[in] path est une matrice de taille (N+1) x d
	* contenant une trajectoire du modèle telle que créée
	* par la fonction asset.
	* @return phi(trajectoire)
	*/
	virtual double payoff(const PnlMat *path) = 0;
};


#endif /* _PRODUIT_H */

