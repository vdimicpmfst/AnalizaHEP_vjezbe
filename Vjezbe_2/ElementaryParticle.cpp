#include<iostream>
#include"ElementaryParticle.h"

using namespace std;

ElementaryParticle::ElementaryParticle (string i, double m, bool b){
	ime = i;
	masa = m;
	bozon = b;
	}
void ElementaryParticle::printInfo (void){
	cout << ime << endl << masa << endl;
        if (bozon == true)
                cout << "bozon" << endl;
        else
                cout << "fermion" << endl;
        return ;
        }
