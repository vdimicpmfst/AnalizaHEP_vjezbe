#include"Analyzer.h"

int main(void){

Analyzer *analyzer = new Analyzer();
analyzer -> ReconstructHiggs();
analyzer -> ~Analyzer();

return 0;
}
