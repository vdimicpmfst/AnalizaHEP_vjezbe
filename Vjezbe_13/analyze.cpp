#include"Analyzer.h" 

int main(void){

Analyzer *analyzer = new Analyzer();
analyzer -> GenerateTestStatistic_H0();
analyzer -> PValue();
analyzer -> ~Analyzer();

return 0;

}
