#include <iostream>

using namespace std;

#include "tauxConstant.h"

TauxConstant::TauxConstant(double r) : Taux(){
	this->r_ = r;
}

TauxConstant::~TauxConstant(){}

double TauxConstant::evaluateRate(double constatationTime){
	return this->r_;
}

double TauxConstant::computeRate(double finalDate){
	return 0.0;
}