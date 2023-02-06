#include"Analyzer.h"


Analyzer::Analyzer(){

	rng = new TRandom3();

}

Analyzer::~Analyzer(){



}

void Analyzer::PValue(){
	
	file = new TFile("/home/public/data/Height/Height.root");
	tree = (TTree*) file -> Get("Tree");
	tree -> SetBranchAddress("height", &height);
	Long64_t nentries = tree -> GetEntriesFast();
	for (int i = 0, t = 0; i < nentries; i++){
		tree -> GetEntry(i);
		t += height;
	}
	t = t / 100.;

}

void Analyzer::GenerateTestStatistic_H0(){

	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	gStyle -> SetOptStat(0);
	
	testStatistic_PDF = new TH1F("testStatistic_PDF", "Test Statistic PDF", 100, 160., 170.);
	double sum;
	
	for (int i = 0; i < 1000000; i++){
		for (int j = 0, sum = 0; j < 100; j++)
			sum += rng -> Gaus(164.7, 7.1);
		testStatistic_PDF -> Fill(sum / 100.);
	}
	
	canvas -> cd();
/*	testStatistic_PDF -> SetFillColor(kRed - 2);
	testStatistic_PDF -> SetLineColor(kRed - 2);
	
	testStatistic_PDF -> SetTitle("Test Statistic PDF distribution");
	testStatistic_PDF -> GetXaxis() -> SetTitle("#bar{h} [cm]");

	testStatistic_PDF -> Scale(1. / testStatistic_PDF -> Integral());
*/	testStatistic_PDF -> Draw("HIST");
	
	canvas -> Print("test.pdf");

}


double Analyzer::Significance(double p_value){

return TMath::Sqrt(2) * TMath::ErfcInverse(2 * p_value);
}
