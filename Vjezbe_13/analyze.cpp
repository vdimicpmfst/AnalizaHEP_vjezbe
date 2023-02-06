#include"Analyzer.h" 

int main(void){

Analyzer *analyzer = new Analyzer();
analyzer -> GenerateTestStatistic_H0();
analyzer -> PValue();
analyzer -> CompareHypothesis("France", 164.7, 7.1);
analyzer -> CompareHypothesis("Italy", 166.1, 6.5);
analyzer -> CompareHypothesis("Netherlands", 170.3, 7.5);
analyzer -> ~Analyzer();

return 0;

}
