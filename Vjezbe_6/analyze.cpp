#include "Analyzer.h"


int main(void){

Analyzer *analyzer = new Analyzer ();
analyzer -> PlotHistogram ();
analyzer -> ~Analyzer ();

return 0;
}
