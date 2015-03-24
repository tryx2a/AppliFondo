#include "../MoteurCalcNatif/model/bs.h"
#include "../MoteurCalcNatif/method/mc.h"
#include "../MoteurCalcNatif/method/method.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <time.h>

using namespace std;

int main(int argc, char **argv)
{
	//const char *infile = argv[1];
	//Param *P = new Parser(infile);
	//Method *mc = new MonteCarlo(P);

	//Initialisation du spot
	PnlVect* spot = pnl_vect_create(22);
	LET(spot, 0) = 1.0745;
	LET(spot, 1) = 6.7307;
	LET(spot, 2) = 100;
	LET(spot, 3) = 100;
	LET(spot, 4) = 100;
	LET(spot, 5) = 100;
	LET(spot, 6) = 100;
	LET(spot, 7) = 100;
	LET(spot, 8) = 100;
	LET(spot, 9) = 100;
	LET(spot, 10) = 100;
	LET(spot, 11) = 100;
	LET(spot, 12) = 100;
	LET(spot, 13) = 100;
	LET(spot, 14) = 100;
	LET(spot, 15) = 100;
	LET(spot, 16) = 100;
	LET(spot, 17) = 100;
	LET(spot, 18) = 100;
	LET(spot, 19) = 100;
	LET(spot, 20) = 100;
	LET(spot, 21) = 100;

	//Init du sigma
	PnlVect* sigma = pnl_vect_create(22);
	LET(sigma, 0) = 0;
	LET(sigma, 1) = 0;
	LET(sigma, 2) = 0.2;
	LET(sigma, 3) = 0.05;
	LET(sigma, 4) = 0.3;
	LET(sigma, 5) = 0.1;
	LET(sigma, 6) = 0.2;
	LET(sigma, 7) = 0.05;
	LET(sigma, 8) = 0.3;
	LET(sigma, 9) = 0.1;
	LET(sigma, 10) = 0.2;
	LET(sigma, 11) = 0.05;
	LET(sigma, 12) = 0.3;
	LET(sigma, 13) = 0.1;
	LET(sigma, 14) = 0.2;
	LET(sigma, 15) = 0.05;
	LET(sigma, 16) = 0.3;
	LET(sigma, 17) = 0.1;
	LET(sigma, 18) = 0.2;
	LET(sigma, 19) = 0.05;
	LET(sigma, 20) = 0.3;
	LET(sigma, 21) = 0.1;

	//Init du trend
	PnlVect* trend = pnl_vect_create_from_double(22, 0.3);

	Produit* p = new FondoGarantito(5, 1, 22, 1000, 0.3, 4);

	Taux* LPMRate = new TauxLPM();

	TauxDeChange* fx = new TauxDeChange();

	Model* mod = new BS(spot, sigma, 0, LPMRate, 22, trend, fx, 13, 4, 3, NULL);

	Method* mc = new MonteCarlo(mod, p, 0.1, 70, 1000);

	double prix;
	double ic;

	//mc->price(prix, ic);
	//cout << "Output : " << endl << "Price : " << prix << endl << "Confidence interval : " << ic << endl;

	PnlVect *V;
	//V = pnl_vect_create(H + 1);
	V = pnl_vect_create(71);

	double profitLoss;

	//mc->freeRiskInvestedPart(V, T + subscriptionPeriod, profitLoss);
	mc->freeRiskInvestedPart(V, 5.3, profitLoss);
	cout << "V : " << endl;
	pnl_vect_print(V);
	cout << "Profit and Loss : " << profitLoss << endl;
	pnl_vect_free(&V);
	
	//delete mc;
	
	//PnlVect* u = pnl_vect_create_from_file("C:/Users/Yannick/Desktop/AppliFondo/Win32Pricer2/Debug/TauxZC.csv");

	//pnl_vect_print(u);


	int retour;
	cin >> retour;
	return 0;
}