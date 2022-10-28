#include<iostream>
#include"ElementaryParticle.h"
#include<cmath>
#include<cstdlib>

using namespace std;

ElementaryParticle::ElementaryParticle (string i, double m, bool b){
	ime = i;
	masa = m;
	bozon = b;
	}
ElementaryParticle::ElementaryParticle (void){
	ime = "";
	masa = 0;
	bozon = 0;
	}
void ElementaryParticle::printInfo (void){
	cout << ime << endl << masa << endl;
        if (bozon == true)
                cout << "bozon" << endl;
        else
                cout << "fermion" << endl;
        return ;
        }
void ElementaryParticle::fourVector(double p1, double p2, double p3){
	px = p1;
	py = p2;
	pz = p3;
	E = sqrt(px*px + py*py + pz*pz + masa*masa);
	return ;
	}
void ElementaryParticle::transverzalno (void){
	cout << "Transverzalna kolicina gibanja = " <<sqrt (px*px + py*py)<< endl;
	return ;
	}
void ElementaryParticle::bosonDecay(ElementaryParticle* particle1, ElementaryParticle* particle2){
	if (!bozon){
		cout << "Raspad nije moguc" << endl;
		return ;
		}
	srand(time(0));
	int rng = rand () % 1000;
	if (rng < 214){
		particle1 -> ime = "W bozon";
		particle2 -> ime = "W bozon";
		}
	else if (rng >= 214 && rng < 278){
                particle1 -> ime = "tau lepton";
                particle2 -> ime = "tau lepton";
                }
	else if (rng >= 278 && rng < 304){
                particle1 -> ime = "Z bozon";
                particle2 -> ime = "Z bozon";
                }
	else{
                particle1 -> ime = "botoom kvark";
                particle2 -> ime = "bottom kvark";
                }
	}
