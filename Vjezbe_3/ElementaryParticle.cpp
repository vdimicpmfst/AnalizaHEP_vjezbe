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
void ElementaryParticle::setInfo(string i, double m, bool b){
	ime = i;
	masa = m;
	bozon = b;
	}
void ElementaryParticle::bosonDecay(ElementaryParticle* particle1, ElementaryParticle* particle2){
	if (!bozon){
		cout << "Raspad nije moguc" << endl;
		return ;
		}
	//srand(time(0));
	int rng = rand () % 1001;
	if (rng <= 214){
		particle1 -> setInfo("W+", 80.4, true);
		particle2 -> setInfo("W-", 80.4, true);
		}
	else if (rng > 214 && rng <= 278){
                particle1 -> setInfo("tau+", 1.78, false);
                particle2 -> setInfo("tau-", 1.78, false);
                }
	else if (rng > 278 && rng <= 304){
                particle1 -> setInfo("Z", 91.2, true);
                particle2 -> setInfo("Z", 91.2, true);
                }
	else{
                particle1 -> setInfo("b-quark", 4.18, false);
                particle2 -> setInfo("b-quark", 4.18, false);
                }
	particle1 -> fourVector (-100 + rand() % 201, -100 + rand() % 201, -100 + rand() % 201);
	particle2 -> fourVector (this -> px - particle1 -> px, this -> py - particle1 -> py, this -> pz - particle1 -> pz);
	}
