#include"Analyzer.h"

int main(void){
Analyzer* analyzer = new Analyzer();
analyzer -> LifetimeFit();
analyzer -> ~Analyzer();
return 0;
}
