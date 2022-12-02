#include "Generator.h"


int main (void){
	Generator *generator;
	generator = new Generator ();
	generator -> GeneratePDF ();
	delete generator;
	return 0;
}
