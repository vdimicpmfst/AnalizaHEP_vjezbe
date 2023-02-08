#include"Analyzer.h"


Analyzer::Analyzer(){


}

Analyzer::~Analyzer(){


}


double Analyzer::Binom(int r, double p, int N){

	return TMath::Binomial(N, r) * pow(p, r) * pow(1 - p, N - r);
	
}


int Analyzer::R0(int N, double p, double epsilon){

	r = 0;
	double sum = 0.;
	while (sum < epsilon){
		//cout << "r = " << r << endl;
		sum += Binom(r, p, N);
		//cout << "P(r <= " << r << ") = " << sum << endl;
		r++;
	}
return r - 1;

}
