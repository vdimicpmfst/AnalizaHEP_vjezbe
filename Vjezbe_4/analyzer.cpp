#include"Analyzer.h"

int main(void){
Analyzer* analyzer;
analyzer = new Analyzer();
analyzer -> ReadTextFile ("Analysis.txt");
analyzer -> ~Analyzer();
return 0;
}
