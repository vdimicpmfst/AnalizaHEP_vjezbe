#include<iostream>
#include<vector>

using namespace std;

class ElementaryParticle {
        public:
        string ime;
        double masa;
        bool bozon;
	double px,py,pz,E;
        ElementaryParticle (string , double , bool );
	ElementaryParticle (void);
	void bosonDecay (ElementaryParticle*, ElementaryParticle*);
	void setInfo(string, double, bool);
        void printInfo (void);
	void fourVector (double , double , double);
        void transverzalno (void);
	};
