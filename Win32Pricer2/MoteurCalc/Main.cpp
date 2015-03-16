#pragma once
#include <iostream>
#include "pnl\pnl_vector.h"
#include "mc.h"

int main(int argc, char** argv){
	std::cout << "Test Moteur de Calcul" << std::endl;

	/*
	option size <int> 20
	spot <vector> 100
	valeur liquidative reference <float> 1000
	maturity <float> 5
	volatility <vector> 0.3
	interest rate <float> 0.03
	trend <vector> 0.03
	option type <string> fondo_garantito
	timestep number <int> 1
	hedging dates number <int> 60
	fd step <float> 0.1
	sample number <int> 10000
	*/
	/*int size = 20;
	PnlVect* spot = pnl_vect_create_from_double(size, 100);
	float vlr = 1000;
	float T = 5;
	PnlVect* sigma = pnl_vect_create_from_double(size, 0.3);
	float r = 0.03;
	PnlVect* trend = pnl_vect_create_from_double(size, 0.03);
	int timeStep = 1;
	int H = 60;
	float h = 0.1;
	int sample = 10000;
	float rho = 0.1;

	Model* mod = new BS(spot,sigma,rho,r,size,trend);
	Produit* prod = new FondoGarantito(T, timeStep, size, vlr);
	Method* mc = new MonteCarlo(mod, prod, h, H, sample);

	double prix = 0;
	double ic = 0;

	mc->price(prix, ic);

	std::cout << "Prix du Fondo : " << prix << std::endl;
	std::cout << "IC du Fondo : " << ic << std::endl;*/

	double * tab = new double[10];

	for (int i = 0; i < 10; i++){
		tab[i] = i;
	}

	PnlVect* u = pnl_vect_create_from_ptr(10, tab);

	pnl_vect_print(u);

	int retour;
	std::cin >> retour;
	std::cout << retour;

	return 0;
}