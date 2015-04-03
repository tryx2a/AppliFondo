#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

using namespace std;

class ParserCSV{
public:


	ParserCSV();
	~ParserCSV();

	PnlVect* createVectFromCSV(const char* infile);
	
	PnlMat* createMatFromCSV(const char* infile);

	vector<string> split(string stringToSplit, string separator);

	void getZcDevises(const char* infile,PnlVect* txEuro,PnlVect* txDollar,PnlVect* txYuan);

};
