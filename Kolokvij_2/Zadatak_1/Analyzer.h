#include<TROOT.h>
#include<TChain.h>
#include<TFile.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TMath.h>
#include<TStyle.h>
#include<TF1.h>
#include<iostream>


using namespace std;


class Analyzer{

 public:
	Analyzer();
	~Analyzer();
	void FitToy();

 private:
	TFile *file;
	TTree *tree;	
	Float_t var;
	TCanvas *canvas;
	TH1F *hist;
	TF1 *f;


};
