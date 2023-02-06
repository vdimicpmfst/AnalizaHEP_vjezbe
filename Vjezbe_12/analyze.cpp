#include"Analyzer.h"

int main(void){

Analyzer *analyzer = new Analyzer();

analyzer -> Loop();
//analyzer -> MVATraining("GBDT");
//analyzer -> MVATraining("kMLP");
analyzer -> PlotMVAScore("GBDT");
analyzer -> PlotMVAScore("kMLP");
analyzer -> ~Analyzer();

return 0;
}
