#include<iostream>
#include<vector>
#include<TROOT.h>
#include<TChain.h>
#include<TFile.h>
#include<TH1F.h>
#include<TCanvas.h>
#include<TString.h>
#include<TLegend.h>
#include<TLorentzVector.h>
#include<THStack.h>
#include<TGraph.h>
#include<TH2F.h>
#include<TF1.h>
#include<TMath.h>
#include<TPad.h>
#include<TStyle.h>

using namespace std;

class Analyzer
{
	public:
	 Analyzer();
	 ~Analyzer();
	 void LifetimeFit();

	private:
	 TFile *file;
	 TTree *tree;
	 TF1 *exp, *Likelihood, *LogLikelihood;
	 TH1F *HistLifetime;
	 TCanvas *c1, *c2, *c3;
	 Float_t t, sum, mean, error, C, tau;
	 Int_t i, nentries;

};
