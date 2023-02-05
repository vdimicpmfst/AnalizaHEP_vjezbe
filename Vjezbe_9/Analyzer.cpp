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
	c1 -> Print ("LifetimeFit.pdf");
	
	cout << "Root: tau = " << exp -> GetParameter(1) << "±" << exp -> GetParError(1) << endl;
	
	mean = sum / nentries;
	error = mean / sqrt(nentries);
	C = exp -> GetParameter(1);
	//analiticki dobiven iz likelihood funkcije	
	cout << "Analiticki: tau = " << mean << "±" << error << endl;

	delete exp; 

	//likelihood
	
	Likelihood = new TF1 ("Likelihood", "([0] / x) * exp(-1.0 / x)", 0.1, 10.0);
	Likelihood -> SetParameter (0, C);
	c2 = new TCanvas ();
	c2 -> SetCanvasSize(600, 400);
	Likelihood -> GetXaxis() -> SetTitle ("#tau");
	Likelihood -> GetYaxis() -> SetTitle ("L(#tau)");
	Likelihood -> SetTitle ("Likelihood za t = 1s");
	Likelihood -> Draw();
	c2 -> Print("Likelihood.pdf");

	delete Likelihood;
}
