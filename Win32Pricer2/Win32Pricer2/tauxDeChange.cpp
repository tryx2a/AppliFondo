#include <iostream>

using namespace std;

#include "tauxDeChange.h"

TauxDeChange::TauxDeChange(){


	//Taille 21 -> tous les 3 mois sur 5 ans
	//this->txZcEuro = pnl_vect_create_from_file("C:/Users/Yannick/Desktop/AppliFondo/Win32Pricer2/data/zcEUR.csv");
	//this->txZcDollar = pnl_vect_create_from_file("C:/Users/Yannick/Desktop/AppliFondo/Win32Pricer2/data/zcUSD.csv");
	//this->txZcYuan = pnl_vect_create_from_file("C:/Users/Yannick/Desktop/AppliFondo/Win32Pricer2/data/zcCNY.csv");

	this->txZcEuro = pnl_vect_create_from_double(23, 1);
	this->txZcDollar = pnl_vect_create_from_double(23, 1);
	this->txZcYuan = pnl_vect_create_from_double(23, 1);
}

TauxDeChange::TauxDeChange(double* fxUsdEur, double* fxYuanEur){

	this->txZcEuro = pnl_vect_create_from_double(23, 1);
	this->txZcDollar = pnl_vect_create_from_ptr(23, fxUsdEur);
	this->txZcYuan = pnl_vect_create_from_ptr(23,fxYuanEur);
}

TauxDeChange::~TauxDeChange(){
	pnl_vect_free(&(this->txZcEuro));
	pnl_vect_free(&(this->txZcYuan));
	pnl_vect_free(&(this->txZcDollar));
}

double TauxDeChange::Devise_eur_doll(double t){
	cout << "Taux euro :" << this->evaluateInterpolationRate(t, this->txZcEuro) << endl;
	cout << "Taux Dollar :" << this->evaluateInterpolationRate(t, this->txZcDollar) << endl;
	return (this->evaluateInterpolationRate(t, this->txZcEuro) - this->evaluateInterpolationRate(t, this->txZcDollar));
}

double TauxDeChange::Devise_eur_yuan(double t){
	return (this->evaluateInterpolationRate(t, this->txZcEuro) - this->evaluateInterpolationRate(t, this->txZcYuan));
}

double TauxDeChange::evaluateInterpolationRate(double t, PnlVect* vectZC){
	int indiceInf;
	int indiceSup;
	double pente;

	double res = 0.0;

	if (t >= 5.0){
		res = GET(vectZC, vectZC->size - 1);
	}
	else{
		if (t <= 0){
			return 0.0;
		}
		else if (0 > t && t < 0.25){
			double valeurMin = GET(vectZC, 0);
			double valeurMax = GET(vectZC, 1);

			pente = (valeurMax - valeurMin);

			res = pente * t + valeurMin;
		}
		else{

			indiceInf = int(4 * t);
			double ecart = 4 * t - indiceInf;
			indiceSup = indiceInf + 1;

			double valeurMin = GET(vectZC, indiceInf);
			double valeurMax = GET(vectZC, indiceSup);

			pente = (valeurMax - valeurMin);

			res = pente * ecart + valeurMin;
		}
	}

	return res;
}

double TauxDeChange::computeRate(double finalDate, PnlVect* vectZC){

	double res = 0.0;

	if (finalDate > 5){
		return this->computeRate(5, vectZC);
	}
	else{

		if (finalDate <= 0){
			return 0.0;
		}
		else{
			double indiceInf = int(4 * finalDate);

			//Calcul de l'aire principal
			double aireTotal = 0;
			for (int i = 0; i < indiceInf; i++){

				double valeurMin = GET(vectZC, i);
				double valeurMax = GET(vectZC, i + 1);
				double valeurMoyen = (valeurMin + valeurMax) / 2;

				aireTotal += valeurMoyen * 0.25;
			}

			//Calcul de l'aire restante
			double ecart = 0.0;
			if (finalDate>0 && finalDate <0.25){
				ecart = 0.25*finalDate;
			}
			else{
				ecart = 0.25*(4 * finalDate - indiceInf);
			}


			double valeurInterpole = this->evaluateInterpolationRate(finalDate, vectZC);

			double aireRestante;
			aireRestante = (valeurInterpole + GET(vectZC, indiceInf)) / 2;


			aireTotal += (aireRestante*ecart);
			res = aireTotal;

			return res;
		}
	}

}