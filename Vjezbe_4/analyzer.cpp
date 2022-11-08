#include<iostream>
#include"ElementaryParticle.h"
#include<cstdlib>
#include<fstream>

using namespace std;

int main(void){
ElementaryParticle Higgs ("Higgs bozon", 125, true);
/*ElementaryParticle *Z = new ElementaryParticle ("Z bozon", 90, true);
ElementaryParticle top ("top kvark", 173, false);*/
ElementaryParticle* decayParticle_1 = new ElementaryParticle();
ElementaryParticle* decayParticle_2 = new ElementaryParticle();
int i;
/*Higgs.printInfo();
Higgs.fourVector(1,1,1);
Higgs.transverzalno();
Higgs.bosonDecay (decayParticle_1, decayParticle_2);
decayParticle_1 -> printInfo();
decayParticle_2 -> printInfo();
top.printInfo();
Z -> printInfo();
cout << Higgs.px << '\t' << Higgs.py << '\t' << Higgs.pz << endl;
cout << decayParticle_1 -> px << '\t' << decayParticle_1 -> py << '\t' << decayParticle_1 -> pz << endl;
cout << decayParticle_2 -> px << '\t' << decayParticle_2 -> py << '\t' << decayParticle_2 -> pz << endl;
delete Z;*/
srand (time(0));
ofstream myfile;
myfile.open ("analysis.txt");
myfile << "#DecayParticle1_Ime" << '\t' << "DecayParticle1_Masa" << '\t' << "DecayParticle1_Bozon" << '\t' << "DecayParticle1_E" << '\t' 
       << "DecayParticle1_px" << '\t' << "DecayParticle1_py" << '\t' << "DecayParticle1_pz" << '\t' << "DecayParticle2_Ime" << '\t'
       << "DecayParticle2_Masa" << '\t' << "DecayParticle2_Bozon" << '\t' << "DecayParticle2_E" << '\t' << "DecayParticle2_px" << '\t'
       << "DecayParticle2_py" << '\t' << "DecayParticle2_pz" << endl;
for (i = 0; i < 10000; i++){
	Higgs.fourVector(-100 + rand() % 201, -100 + rand() % 201, -100 + rand() % 201);
	Higgs.bosonDecay(decayParticle_1, decayParticle_2);
	myfile << decayParticle_1 -> ime << '\t' << decayParticle_1 -> masa << '\t' << decayParticle_1 -> bozon << '\t' << decayParticle_1 -> E
	       << '\t' << decayParticle_1 -> px << '\t' << decayParticle_1 -> py << '\t' << decayParticle_1 -> pz << '\t'
	       << decayParticle_2 -> ime << '\t' << decayParticle_2 -> masa << '\t' << decayParticle_2 -> bozon << '\t' << decayParticle_2 -> E
	       << '\t' << decayParticle_2 -> px << '\t' << decayParticle_2 -> py << '\t' << decayParticle_2 -> pz << endl;
	}
myfile.close();
delete decayParticle_1;
delete decayParticle_2;
return 0;
}
