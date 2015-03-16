#include <iostream>

using namespace std;

#include "produit.h"


Produit::Produit(const double T_, const int timeSteps_, const int size_){
	this->T_ = T_;
	this->TimeSteps_ = timeSteps_;
	this->size_ = size_;
}

Produit::~Produit(){}

