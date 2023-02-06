#include<iostream>
#include<TROOT.h>
#include<TH1F.h>
#include<TMath.h>
#include<THStack.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<TLine.h>

using namespace std;

class Analyzer
{
 public:
	Analyzer();
	~Analyzer();
	double Binom(int r, double p, int N);
	pair<double, double> CPinterval(double CL, int N, int m);
	void CPpojas(int N, double CL);
	void Igra();	

};
