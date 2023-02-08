#include"Analyzer.h"


Analyzer::Analyzer(){



}


Analyzer::~Analyzer(){



}


void Analyzer::FitToy(){

	file = new TFile("/home/public/data/Toy/ToyTree.root");
	tree = (TTree*)file -> Get("tree");
	tree -> SetBranchAddress("var", &var);
	Long64_t nentries = tree -> GetEntriesFast();
	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	hist = new TH1F("hist", "hist", 100, 0., 10.);
	for (int i = 0; i < nentries; i++){

		tree -> GetEntry(i);
		hist -> Fill(var);
	
	}
	f = new TF1("fit funkcija", "[0] * (TMath::Exp(-x / [1]) + TMath::Exp(-(x - [2]) * (x - [2]) / 2. / [3]))");
	f -> SetParameter(0, 250.);
	f -> SetParameter(1, 4.);
	f -> SetParameter(2, 3.);
	f -> SetParameter(3, 0.3);

	hist -> Fit(f, "L", "", 0, 10);
	
	hist -> Draw("HIST");
	f -> Draw("");
	canvas -> Print("test.pdf");

}
