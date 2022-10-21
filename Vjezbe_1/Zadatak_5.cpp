#include<iostream>

using namespace std;

double kub (double );
double kub (double broj){
return broj*broj*broj;
}

int main(void){
double broj;
cout << "Unesite broj: ";
cin >> broj;
cout << "Kub unesenog broja je " << kub(broj) << endl;
return 0;
}
