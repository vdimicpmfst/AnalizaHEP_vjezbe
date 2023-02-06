#include"Analyzer.h"

int main(void){

Analyzer *analyzer = new Analyzer();
for (int i = 0; i <= 10; i++){
cout << analyzer -> CPinterval (0.6827, 10, i).first << endl;
cout << analyzer -> CPinterval (0.6827, 10, i).second << endl << endl;
}
analyzer -> CPpojas(10, 0.6827);
analyzer -> ~Analyzer(); 

return 0;
}
