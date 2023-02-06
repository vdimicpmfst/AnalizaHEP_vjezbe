#include"Anylzer.h"

Analyzer::Analyzer(){


}

Analyzer::~Analyzer(){


}

double Analyzer::Binom(int r, double p, int N){

return Binomial(N, r) * pow(p, r) * pow (1.-p, N - r);

}
