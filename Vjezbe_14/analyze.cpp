#include"Analyzer.h"

int main(void){

Analyzer *analyzer = new Analyzer();
analyzer -> GenerateTestStatisticPDF(1000);
analyzer -> ~Analyzer();

return 0;
}
