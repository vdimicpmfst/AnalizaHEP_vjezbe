#include"Analyzer.h"


Analyzer::Analyzer(){


}

Analyzer::~Analyzer(){



}

void Analyzer::PValue(){
	
	file = new TFile("/home/public/data/Height/Height.root");
	tree = (TTree*) file -> Get("Tree");
	tree -> SetBranchAddress("height", &height);
	testStatistic_PDF = new TH1F("height", "height", 100, 160., 170.);
	Long64_t nentries = tree -> GetEntriesFast();
	for (int i = 0, t = 0; i < nentries; i++){
		tree -> GetEntry(i);
		testStatistic_PDF -> Fill(height);
		t += height;
	}
	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	testStatistic_PDF -> Draw("HIST");
	canvas -> Print("test.pdf");

}

void Analyzer::GenerateTestStatistic_H0(){


}
