#include <iostream>

using namespace std;

#include "tauxLPM.h"


TauxLPM::TauxLPM() : Taux(){

	this->vectZC = pnl_vect_create_from_double(23, 0.03);
}

TauxLPM::TauxLPM(double* r){

	this->vectZC = pnl_vect_create_from_ptr(23,r);
}

TauxLPM::~TauxLPM(){
	pnl_vect_free(&(this->vectZC));
}

/*
*	Réalise une interpolation pour déterminer un taux intermédiaire
*/
double TauxLPM::evaluateRate(double constatationTime){
	int indiceInf;
	int indiceSup;
	double pente;

	double res = 0.0;

	if (constatationTime >= 5){
		res = GET(this->vectZC, this->vectZC->size - 1);
	}
	else{
		if (constatationTime <= 0){
			return 0.0;
		}
		else if (0 > constatationTime && constatationTime < 0.25){
			double valeurMin = GET(this->vectZC, 0);
			double valeurMax = GET(this->vectZC, 1);

			pente = (valeurMax - valeurMin);

			res = pente * constatationTime + valeurMin;
		}
		else{

			indiceInf = int(4 * constatationTime);
			double ecart = 4 * constatationTime - indiceInf;
			indiceSup = indiceInf + 1;

			double valeurMin = GET(this->vectZC, indiceInf);
			double valeurMax = GET(this->vectZC, indiceSup);

			pente = (valeurMax - valeurMin);

			res = pente * ecart + valeurMin;
		}
	}

	return res;
}


double TauxLPM::computeRate(double finalDate){

	double res = 0.0;

	if (finalDate > 5){
		return this->computeRate(5);
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

				double valeurMin = GET(this->vectZC, i);
				double valeurMax = GET(this->vectZC, i + 1);
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


			double valeurInterpole = this->evaluateRate(finalDate);

			double aireRestante;
			aireRestante = (valeurInterpole + GET(this->vectZC, indiceInf)) / 2;


			aireTotal += (aireRestante*ecart);
			res = aireTotal;

			return res;
		}
	}

}