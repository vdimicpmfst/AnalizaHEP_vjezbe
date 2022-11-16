#include<iostream>
#include<sstream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<vector>

using namespace std;

class Analyzer{

public:
	Analyzer ();
	~Analyzer ();
	void ReadTextFile (string);
	string _decayParticle1, _decayParticle2;
	bool bozon1, bozon2;
	double masa1, px1, py1, pz1, E1, masa2, px2, py2, pz2, E2;
	ifstream myReadFile;
	string line;
	bool skipLine;
	
};
