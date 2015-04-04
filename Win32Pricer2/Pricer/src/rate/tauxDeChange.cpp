#include <iostream>

using namespace std;

#include "tauxDeChange.h"
#include "../parserCSV.h"

TauxDeChange::TauxDeChange(){

	/*ParserCSV* parse = new ParserCSV();

	//Taille 21 -> tous les 3 mois sur 5 ans
	this->txZcEuro = pnl_vect_create(23);
	this->txZcDollar = pnl_vect_create(23);
	this->txZcYuan = pnl_vect_create(23);

	parse->getZcDevises("../data/test_EuroDollYuan2.csv", txZcEuro,txZcDollar,txZcYuan);

	delete parse;*/
	this->txZcEuro = pnl_vect_create_from_list(23, 0.00024,0.00044,0.00063,0.00129,0.00164,0.0026,0.00374,0.00457,0.00584,0.00634,0.00756,0.0088,0.00974,0.01034,0.01149,0.01198,0.01356,0.01402,0.01451,0.01503,0.01567,0.01604,0.01654);
	this->txZcDollar = pnl_vect_create_from_list(23, 0.05024,0.05044,0.05063,
		0.05129,
		0.05164,
		0.0526,
		0.05374,
		0.05457,
		0.05584,
		0.05634,
		0.05756,
		0.0588,
		0.05974,
		0.06034,
		0.06149,
		0.06198,
		0.06356,
		0.06402,
		0.06451,
		0.06503,
		0.06567,
		0.06604,
		0.06654
		);
	this->txZcYuan = pnl_vect_create_from_list(23, 0.10024,
		0.10044,
		0.10063,
		0.10129,
		0.10164,
		0.1026,
		0.10374,
		0.10457,
		0.10584,
		0.10634,
		0.10756,
		0.1088,
		0.10974,
		0.11034,
		0.11149,
		0.11198,
		0.11356,
		0.11402,
		0.11451,
		0.11503,
		0.11567,
		0.11604,
		0.11654
		);

}

TauxDeChange::~TauxDeChange(){
	pnl_vect_free(&(this->txZcEuro));
	pnl_vect_free(&(this->txZcYuan));
	pnl_vect_free(&(this->txZcDollar));
}

double TauxDeChange::Devise_eur_doll(double t){
	cout<<"Taux euro :"  <<this->evaluateInterpolationRate(t, this->txZcEuro)<<endl;
	cout<<"Taux Dollar :"  <<this->evaluateInterpolationRate(t, this->txZcDollar)<<endl;
	return (this->evaluateInterpolationRate(t, this->txZcEuro)-this->evaluateInterpolationRate(t, this->txZcDollar));
}

double TauxDeChange::Devise_eur_yuan(double t){
	return (this->evaluateInterpolationRate(t, this->txZcEuro)-this->evaluateInterpolationRate(t, this->txZcYuan));
}

double TauxDeChange::evaluateInterpolationRate(double t, PnlVect* vectZC){
	int indiceInf;
	int indiceSup;
	double pente;

	double res = 0.0;

	if(t > 5.0){
		res = GET(vectZC, vectZC->size-1);
	}else{
		if(t <= 0){
			return 0.0;
		}else if( 0 > t && t < 0.25){
			double valeurMin = GET(vectZC, 0);
			double valeurMax = GET(vectZC, 1);
		
			pente = (valeurMax - valeurMin);

			res = pente * t + valeurMin;
		}else{

			indiceInf = int(4*t);
			double ecart = 4*t - indiceInf;
			indiceSup = indiceInf+1;

			double valeurMin = GET(vectZC, indiceInf);
			double valeurMax = GET(vectZC, indiceSup);

			pente = (valeurMax - valeurMin);

			res = pente * ecart + valeurMin;
		}
	}

	return res;
}

double TauxDeChange::computeRate(double finalDate,PnlVect* vectZC){

	double res = 0.0;

	if(finalDate > 5){
		return this->computeRate(5, vectZC);
	}else{

		if(finalDate <= 0){
			return 0.0;
		}else{
			double indiceInf = int(4*finalDate);

			//Calcul de l'aire principal
			double aireTotal = 0;
			for(int i = 0; i < indiceInf;i++){
	
				double valeurMin = GET(vectZC,i);
				double valeurMax = GET(vectZC,i+1);
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
	
			
			double valeurInterpole = this->evaluateInterpolationRate(finalDate,vectZC);
			
			double aireRestante;
			aireRestante = (valeurInterpole + GET(vectZC,indiceInf) )/2;
			
		
			aireTotal += (aireRestante*ecart) ;
			res = aireTotal;
		
			return res;
		}
	}

}