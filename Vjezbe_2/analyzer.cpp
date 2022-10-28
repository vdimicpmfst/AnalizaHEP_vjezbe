#include<iostream>
#include"ElementaryParticle.h"

using namespace std;

int main(void){
ElementaryParticle Higgs ("Higgs bozon", 125, 1);
ElementaryParticle *Z = new ElementaryParticle ("Z bozon", 90, 1);
ElementaryParticle top ("top kvark", 173, 0);
Higgs.printInfo();
top.printInfo();
Z -> printInfo();
delete Z;
return 0;
}
