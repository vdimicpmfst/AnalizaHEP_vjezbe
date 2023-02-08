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

	hist -> Draw("HIST");
	canvas -> Print("test.pdf");

}
