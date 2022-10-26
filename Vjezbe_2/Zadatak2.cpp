#include<iostream>

using namespace std;

class ElementaryParticle {
	public:
	string ime;
	double masa;
	bool bozon;
	ElementaryParticle (string a, double m, bool b){
		ime = a;
		masa = m;
		bozon = b;
		}
	void printInfo (void){
		cout << ime << endl << masa << endl;
		if (bozon == true)
			cout << "bozon" << endl;
		else 
			cout << "fermion" << endl;
		return ;
		}
	};

int main(void){

ElementaryParticle Higgs("Higgsov bozon", 150, true);
ElementaryParticle top("top kvark", 50, false);
ElementaryParticle* pointer = new ElementaryParticle("Z bozon", 91, true);
Higgs.printInfo();
top.printInfo();
pointer->printInfo();
delete pointer;
return 0;
}
