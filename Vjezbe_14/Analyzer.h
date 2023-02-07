#include<TROOT.h>
#include<TChain.h>
#include<TFile.h>
#include<TCanvas.h>
#include<TH1F.h>
#include<TGraph.h>
#include<TRandom3.h>
#include<TLegend.h>
#include<iostream>
#include<TStyle.h>
#include<TF1.h>

using namespace std;

class Analyzer{
 
 public:
	Analyzer();
	~Analyzer();
	void GenerateTestStatisticPDF(int);
	void PValueScan();

 private:
	TCanvas *canvas;
	TH1F *TestStatisticPDF, *toy;
	TF1 *theoreticalPDF;
	TRandom3 *rng;
	double expected_p_value;
	TGraph *expected_scan;


};
