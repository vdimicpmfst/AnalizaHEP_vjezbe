#include<iostream>
#include<vector>
#include<TROOT.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<TString.h>
#include<TGraphErrors.h>
#include<TF1.h>
#include<TLine.h>
#include<TApplication.h>
#include<cmath>

using namespace std;

class Analyzer
{
 public:
	Analyzer();
	~Analyzer();

	void ChiSquare();
 private:
	TCanvas *c;
	TGraphErrors *graph;
	TF1 *fit, *chi_square_fit;
	TLine *line_h, *line_v1, *line_v2, *line_v3;


};
