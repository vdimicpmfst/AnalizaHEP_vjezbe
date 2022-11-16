#include"Analyzer.h"

Analyzer::Analyzer(){

}

Analyzer::~Analyzer(){

}

void Analyzer::ReadTextFile(string filename){
	ifstream myReadFile;
	myReadFile.open(filename.c_str());
	string line;
	skipLine = true;
	if (myReadFile.is_open()){
		while (getline (myReadFile, line)){
			stringstream linestream(line);
			if (skipLine){
				skipLine = false;
				continue;
				}
			linestream>> _decayParticle1 >> bozon1 >> masa1 >> E1 >> px1 >> py1 >> pz1 
				  >> _decayParticle2 >> bozon2 >> masa2 >> E2 >> px2 >> py2 >> pz2;
		}
	
	
	}
	myReadFile.close();	
}

