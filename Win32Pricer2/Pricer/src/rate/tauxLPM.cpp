#include <iostream>

using namespace std;

#include "tauxLPM.h"
#include "../parserCSV.h"

TauxLPM::TauxLPM() : Taux(){
	/*ParserCSV* parse = new ParserCSV();
	this->vectZC = parse->createVectFromCSV("../data/TauxZC.csv");
	delete parse;*/
	this->vectZC = pnl_vect_create_from_list(23, 0.00024,
		0.00044,
		0.00063,
		0.00129,
		0.00164,
		0.0026,
		0.00374,
		0.00457,
		0.00584,
		0.00634,
		0.00756,
		0.0088,
		0.00974,
		0.01034,
		0.01149,
		0.01198,
		0.01356,
		0.01402,
		0.01451,
		0.01503,
		0.01567,
		0.01604,
		0.01654
		);
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

	if(constatationTime > 5){
		res = GET(this->vectZC, this->vectZC->size-1);
	}else{
		if(constatationTime <= 0){
			return 0.0;
		}else if( 0 > constatationTime && constatationTime < 0.25){
			double valeurMin = GET(this->vectZC, 0);
			double valeurMax = GET(this->vectZC, 1);
		
			pente = (valeurMax - valeurMin);

			res = pente * constatationTime + valeurMin;
		}else{

			indiceInf = int(4*constatationTime);
			double ecart = 4*constatationTime - indiceInf;
			indiceSup = indiceInf+1;

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

	if(finalDate > 5){
		return this->computeRate(5);
	}else{

		if(finalDate <= 0){
			return 0.0;
		}else{
			double indiceInf = int(4*finalDate);

			//Calcul de l'aire principal
			double aireTotal = 0;
			for(int i = 0; i < indiceInf;i++){
	
				double valeurMin = GET(this->vectZC,i);
				double valeurMax = GET(this->vectZC,i+1);
				double valeurMoyen = (valeurMin + valeurMax)/2;

				aireTotal += valeurMoyen * 0.25;
			}

			//Calcul de l'aire restante
			double ecart = 0.0;
			if(finalDate>0 && finalDate <0.25){
				ecart = 0.25*finalDate;
			}else{
				ecart = 0.25*(4*finalDate - indiceInf);
			}
	
			
			double valeurInterpole = this->evaluateRate(finalDate);
			
			double aireRestante;
			aireRestante = (valeurInterpole + GET(this->vectZC,indiceInf) )/2;
			
		
			aireTotal += (aireRestante*ecart) ;
			res = aireTotal;
		
			return res;
		}
	}

}