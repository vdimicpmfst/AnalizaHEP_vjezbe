#include"Analyzer.h"

int main(void){
Analyzer* analyzer;
analyzer = new Analyzer();
analyzer -> ReadTextFile ("Analysis.txt");
analyzer -> ConvertTxtToRootFile ("Analysis.txt", "Analysis.root");
analyzer -> ~Analyzer();
return 0;
}
