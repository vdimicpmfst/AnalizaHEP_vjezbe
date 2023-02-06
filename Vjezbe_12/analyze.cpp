#include"Analyzer.h"

int main(void){

Analyzer *analyzer = new Analyzer();

analyzer -> Loop();
analyzer -> ~Analyzer();

return 0;
}
