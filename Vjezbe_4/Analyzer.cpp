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
			linestream>> _decayParticle1 >> masa1 >> bozon1 >> E1 >> px1 >> py1 >> pz1 
				  >> _decayParticle2 >> masa2 >> bozon2 >> E2 >> px2 >> py2 >> pz2;
		}
	
	
	}
	myReadFile.close();	
}

void Analyzer::ConvertTxtToRootFile (string input, TString output){
	fstream file, test;
	file.open(input, ios::in);
	//test.open("test.txt", ios::out);
	TFile *root_file = new TFile (output, "RECREATE");
	TTree *tree = new TTree ("Tree", "Higgs decay");
	skipLine = true;
	tree -> Branch ("DecayParticle1_Name", &_decayParticle1);
	tree -> Branch ("DecayParticle1_isBoson", &bozon1, "DecayParticle1_isBoson/D"); 
	tree -> Branch ("DecayParticle1_mass", &masa1, "DecayParticle1_mass/I");
	tree -> Branch ("DecayParticle1_E", &E1, "DecayParticle1_E/D");
	tree -> Branch ("DecayParticle1_px", &px1, "DecayParticle1_px/D");
	tree -> Branch ("DecayParticle1_py", &py1, "DecayParticle1_py/D");
	tree -> Branch ("DecayParticle1_pz", &pz1, "DecayParticle1_pz/D");

	tree -> Branch ("DecayParticle2_Name", &_decayParticle2);
	tree -> Branch ("DecayParticle2_isBoson", &bozon2, "DecayParticle2_isBoson/I");
	tree -> Branch ("DecayParticle2_mass", &masa2, "DecayParticle2_mass/D");
	tree -> Branch ("DecayParticle2_E", &E2, "DecayParticle2_E/D");
	tree -> Branch ("DecayParticle2_px", &px2, "DecayParticle2_px/D");
	tree -> Branch ("DecayParticle2_py", &py2, "DecayParticle2_py/D");
	tree -> Branch ("DecayParticle2_pz", &pz2, "DecayParticle2_pz/D");
	
	//int i=1;
	while (1){
		/*cout << i << endl;
		i++;*/
		if (skipLine){
			getline (file, _decayParticle1);
			skipLine = false; 
			continue;
		}	
		file >> _decayParticle1 >> masa1 >> bozon1 >> E1 >> px1 >> py1 >> pz1
                     >> _decayParticle2 >> masa2 >> bozon2 >> E2 >> px2 >> py2 >> pz2;
		/*test << _decayParticle1 << ' ' << masa1 << ' ' << bozon1 << ' ' << E1 << ' ' << px1 << ' ' << ' ' << py1 << ' ' << pz1
                     << ' ' << _decayParticle2 << ' ' << ' ' << masa2 << ' ' << bozon2 << ' ' << E2 << ' ' << px2 << ' ' << py2 << ' ' << pz2 << endl;*/
		if (file.eof()){
			break;
		}
		tree -> Fill();
	}
	tree ->Write();
	delete root_file;
	file.close();
}
