#include<iostream>
#include"ElementaryParticle.h"

using namespace std;

int main(void){
ElementaryParticle Higgs ("Higgs bozon", 125, 1);
ElementaryParticle *Z = new ElementaryParticle ("Z bozon", 90, 1);
ElementaryParticle top ("top kvark", 173, 0);
ElementaryParticle* decayParticle_1 = new ElementaryParticle();
ElementaryParticle* decayParticle_2 = new ElementaryParticle();
Higgs.printInfo();
Higgs.fourVector(1,1,1);
Higgs.transverzalno();
Higgs.bosonDecay (decayParticle_1, decayParticle_2);
decayParticle_1 -> printInfo();
decayParticle_2 -> printInfo();
top.printInfo();
Z -> printInfo();
delete Z;
delete decayParticle_1;
delete decayParticle_2;
return 0;
}
