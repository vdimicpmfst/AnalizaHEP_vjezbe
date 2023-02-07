#include"Analyzer.h"


Analyzer::Analyzer(){

	rng = new TRandom3();

}

Analyzer::~Analyzer(){


}

void Analyzer::GenerateTestStatisticPDF(int n){

	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	
	TestStatisticPDF = new TH1F("Test_StatisticPDF", "TestStatisticPDF", 400, 0, 40);
	
	theoreticalPDF = new TF1("theoreticalPDF", "[0] / TMath::Exp(x / [1])", 0, 700);
	theoreticalPDF -> SetParameter(0, 1000.);
	theoreticalPDF -> SetParameter(1, 100.);

	float chi2;
	float m_H = 0;

	for (int i = 0; i < n; i++){
		
		TString ime = "toy_" + to_string(i);
		toy = new TH1F(ime, "toy", 200, 0., 700.);
	
		for (int j = 0; j < 100000; j++){
			toy -> Fill(rng -> Exp(100));
		}
		
		theoreticalPDF -> SetParameter(1, 100.);

		for (int j = 10; j < 690; j += 5){

			m_H = (float)i;
			toy -> Fit(theoreticalPDF, "Q", "", m_H - 10, m_H + 10);
			chi2 = theoreticalPDF -> GetChisquare();
			TestStatisticPDF -> Fill(chi2);
		}
	
	}

	gStyle -> SetOptStat(0);
	gPad -> SetBottomMargin(0.2);
	TestStatisticPDF -> SetTitle("Test Statistic PDF");
	TestStatisticPDF -> GetXaxis() -> SetTitle("#chi^{2}(N, #zeta_{SM})");
	TestStatisticPDF -> GetXaxis() -> SetTitleOffset(1.5);
	TestStatisticPDF -> Scale(1. / TestStatisticPDF -> Integral());
	TestStatisticPDF -> Draw("HIST");
	
	canvas -> Print("TestStatisticPDF.pdf");
}
