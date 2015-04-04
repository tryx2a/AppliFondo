#include <iostream>
#include ".\method\mc.h"
#include <time.h>
#include ".\method\method.h"
#include "./rate/tauxLPM.h"
#include <windows.h>
using namespace std;

int main(int argc, char **argv)
{
  double T=5; 
  double subscriptionPeriod=0.3;
  int H=70;
  double h = 0.1;
  int samples = 50;
  int timestep = 1;
  int size = 22;
  double vlOrigine = 1000;
  int timeStepSub = 4;
  
  Taux* r = new TauxLPM();
  
  TauxDeChange* fx = new TauxDeChange();
  
  int numEuro = 13;
  int numDollar = 4;
  int numYuan = 3;
  PnlVect* trend = pnl_vect_create_from_double(22, 0.3);
  double rho = 0;
  PnlVect* spot = pnl_vect_create(22);
  LET(spot, 0) = 1.0745;
  LET(spot, 1) = 6.7307;
  LET(spot, 2) = 53.49;
  LET(spot, 3) = 214.01;
  LET(spot, 4) = 16.92;
  LET(spot, 5) = 4.04;
  LET(spot, 6) = 99600;
  LET(spot, 7) = 6.39;
  LET(spot, 8) = 47.1;
  LET(spot, 9) = 18.1;
  LET(spot, 10) = 69.15;
  LET(spot, 11) = 30.22;
  LET(spot, 12) = 6.25;
  LET(spot, 13) = 78.7;
  LET(spot, 14) = 30.95;
  LET(spot, 15) = 122.45;
  LET(spot, 16) = 56.75;
  LET(spot, 17) = 63.44;
  LET(spot, 18) = 85.65;
  LET(spot, 19) = 65.88;
  LET(spot, 20) = 32.93;
  LET(spot, 21) = 54.23;
  PnlVect* sigma = pnl_vect_create(22);
  LET(sigma, 0) = 0.3;
  LET(sigma, 1) = 0.3;
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
 
  //Produit* p = new FondoGarantito(T, timestep, size, vlOrigine, subscriptionPeriod, timeStepSub);
  //Model* mod = new BS(spot, sigma, rho, LPMRate, size, trend, fx, numEuro, numDollar, numYuan, NULL);
  //Method *mc = new MonteCarlo(mod, p, h, H, samples);
  Method* mc = new MonteCarlo(spot->array, sigma->array, rho, r, size, trend->array, fx, numEuro, numDollar, numYuan, NULL, T, timestep, vlOrigine, subscriptionPeriod, timeStepSub, h, H, samples);


  double V = 0.0;
  double portfolio=0.0;
  double price=0.0;
  double tho = 0.0;
  PnlVect *delta = pnl_vect_create(mc->opt_->size_);
  PnlMat *simulMarketResult, *tempMarketResult;
  simulMarketResult = pnl_mat_create(mc->H_ + 1, mc->mod_->size_);
  mc->mod_->simul_market(simulMarketResult, T, mc->H_, mc->rng);
  tempMarketResult = pnl_mat_copy(simulMarketResult);

  
  for (int i = 0; i<H + 1; i++){
	  mc->freeRiskInvestedPart(V, T + subscriptionPeriod, portfolio, price, delta, tho, tempMarketResult);

	  cout << "Tho : " << tho << endl;
	  cout << "Delta : " << endl;
	  pnl_vect_print(delta);
	  cout << "Tracking Error : " << portfolio - price << endl;

	  tho += (T + subscriptionPeriod) / ((double)mc->H_);
	  //Extraction des données de la matrice past pour la date de rebalancement
	  pnl_mat_free(&tempMarketResult);
	  if (i<H){
		  tempMarketResult = pnl_mat_create((i + 1) + 1, mc->mod_->size_);
		  pnl_mat_extract_subblock(tempMarketResult, simulMarketResult, 0, (i + 1) + 1, 0, mc->mod_->size_);
	  }
  }
  //mc->freeRiskInvestedPart(V, tim, portfolio, price);
  
  pnl_vect_free(&sigma);
  pnl_vect_free(&spot);
  pnl_vect_free(&trend);

  delete mc;
  
  
  return 0;
  
}
