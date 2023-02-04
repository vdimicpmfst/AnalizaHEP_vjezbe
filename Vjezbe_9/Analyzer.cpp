#include"Analyzer.h"

Analyzer::Analyzer(){


}

Analyzer::~Analyzer(){


}

void Analyzer::LifetimeFit(){

	file = new TFile ("/home/public/data/Lifetime/Lifetime.root");
	tree = (TTree*)file -> Get("Tree");
	tree -> SetBranchAddress ("t", &t);
	HistLifetime = new TH1F ("Lifetime", "Lifetime", 24, 0.0, 10.0);
	exp = new TF1 ("exp", "[0] / [1] * exp(-x / [1])", 0.0, 10.0);
	exp -> SetParameter (0, 100.);
	exp -> SetParameter (1, 1.);
	nentries = tree -> GetEntriesFast();
	sum = 0;
	for (i = 0; i < nentries; i++){
		tree -> GetEntry(i);
		HistLifetime -> Fill(t);
		sum += t;
	}

	HistLifetime -> Fit(exp, "L");
	gStyle -> SetOptStat(0);
	c1 = new TCanvas();
	c1 -> SetCanvasSize(600,400);
	HistLifetime -> GetXaxis () -> SetTitle ("t / s");
	HistLifetime -> GetYaxis () -> SetTitle ("N");
	HistLifetime -> Draw ();
	HistLifetime -> Print ("LifetimeFit.pdf");


}
