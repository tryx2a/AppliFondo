using namespace std;

#include "parserCSV.h"
#include <sstream>

ParserCSV::ParserCSV(){}

ParserCSV::~ParserCSV(){}
	
PnlVect* ParserCSV::createVectFromCSV(const char* infile){

	int sizeFile = 0;

	string line;
  	ifstream fichier(infile, ios::in);

  	//Si reussite de l'ouverture
  	if (fichier.is_open())
  	{
    	//Calcul la taille du vecteur
    	while ( getline (fichier,line) )
    	{
      		sizeFile ++;
    	}
    	fichier.close();
  	}else{ //Echec de l'ouverture
  		cout << "Unable to open file 1"<<endl; 
  	}


  	PnlVect* vectTaux = pnl_vect_create(sizeFile);
  	ifstream fichier2(infile, ios::in);
  	if (fichier2.is_open())
  	{
  		int cmp = 0;
    	//Attribution des composantes
    	while ( getline (fichier2,line) )
    	{
  			LET(vectTaux,cmp) = atof(line.c_str());
  			cmp++;
    	}
    	fichier2.close();
  	}else{ //Echec de l'ouverture
  		cout << "Unable to open file 2"<<endl; 
  	}

	return vectTaux;
}



void ParserCSV::getZcDevises(const char* infile, PnlVect* txEuro,PnlVect* txDollar,PnlVect* txYuan){

    int sizeFile = 0;
    //Calcul de la taille du fichier
    string line;
    ifstream fichier(infile, ios::in);

    //Si reussite de l'ouverture
    if (fichier.is_open())
    {

      //Calcul la taille du vecteur
      while ( getline (fichier,line) )
      {
          sizeFile ++;
      }
      fichier.close();
    }else{ //Echec de l'ouverture
      cout << "Unable to open file 1"<<endl; 
    }

    //Initialisation et creation du vecteur
    PnlVect* vectTaux = pnl_vect_create(sizeFile);

    ifstream fichier2(infile, ios::in);
    if (fichier2.is_open())
    {
      int cmp = 0;
      //Attribution des composantes
      while ( getline (fichier2,line) )
      {
        LET(vectTaux,cmp) = atof(line.c_str());
        cmp++;
      }
      fichier2.close();
    }else{ //Echec de l'ouverture
      cout << "Unable to open file 2"<<endl; 
    }

    //Creation des 3 devises
    for(int i = 0 ; i < 69 ; i ++){
      if(i < 23){
        LET(txEuro, i) = GET(vectTaux,i);
      }else if(i >= 23 && i<46){
        LET(txDollar,i-23) = GET(vectTaux,i);
      }else{
        LET(txYuan,i-46) = GET(vectTaux,i);      
      }
    }


    pnl_vect_free(&vectTaux);
}

vector<string> ParserCSV::split(string s, string delimiter){

  size_t pos = 0;
  std::vector<string> vectTokens;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      //std::cout << token << std::endl;
      vectTokens.push_back(token);
      s.erase(0, pos + delimiter.length());
  }

  return vectTokens;
}

PnlMat* ParserCSV::createMatFromCSV(const char* infile){

  int nbLigne = 0;
  int nbColonne = 0;

  bool firstLine = false;

  string line;
  ifstream fichier(infile, ios::in);

  //Si reussite de l'ouverture
  if (fichier.is_open())
  {
    //Calcul la taille de la matrice
    while ( getline (fichier,line) )
    {
      nbLigne ++;
      //Determine le nombre de colonne de la matrice
      if(firstLine){
        firstLine = true;
        vector<string> v = this->split(line,";");
        nbColonne = v.size();
      }
    }
    fichier.close();
  }else{ //Echec de l'ouverture
    cout << "Unable to open file 1"<<endl; 
  }

  //Initialisation de la matrice
  PnlMat* mat = pnl_mat_create (nbLigne, nbColonne);
    
    ifstream fichier2(infile, ios::in);
    if (fichier2.is_open())
    {
      int cmp = 0;
      //Attribution des composantes
      while ( getline (fichier2,line) )
      {
        //Traitement de la ligne
        vector<string> v = this->split(line,";");

        //Parcourt du vecteur en colonne
        int indiceCol = 0;
        for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it){
          //std::cout << ' ' << *it<<endl;
          MLET(mat,cmp,indiceCol) = atof((*it).c_str());
          indiceCol++;
        }

        cmp++;
      }
      fichier2.close();
    }else{ //Echec de l'ouverture
      cout << "Unable to open file 2"<<endl; 
    }

  return mat;


}

