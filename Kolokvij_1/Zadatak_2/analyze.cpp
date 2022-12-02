#include "Analyzer.h"

int main (void){
	Analyzer *analyze;
	analyze = new Analyzer ();
	analyze -> Plot2DHistogram ();
	analyze -> ~Analyzer ();

	return 0;
}
