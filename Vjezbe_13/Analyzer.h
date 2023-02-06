#include<TROOT.h>
#include<TChain.h>
#include<TFile.h>
#include<TRandom3.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TLine.h>
#include<TMath.h>
#include<TLegend.h>
#include<iostream>
#include<TStyle.h>

using namespace std;

class Analyzer
{
 public:
	TFile *file;
	TTree *tree;
	Float_t height;
	
	Analyzer();
	~Analyzer();
	void GenerateTestStatistic_H0();
	void PValue();
	void CompareHypothesis(TString, double, double);
 
 private:
	TRandom *rng;
	TH1F *testStatistic_PDF, *testStatistic_H0, *testStatistic_H1;
	double t;
	double Significance(double);
	TCanvas *canvas;
};
