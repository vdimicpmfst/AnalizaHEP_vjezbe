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
		
		theoreticalPDF -> FixParameter(1, 100.);

		for (int j = 10; j < 690; j += 5){

			m_H = (float)j;
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


void Analyzer::PValueScan(){

	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	
	expected_scan = new TGraph();

	float a_SM = -1., b_SM = -190., c_SM = 0.5, sigma_SM = 0.0236, m_H = 0;
	float chi2;
	
	for (int i = 10; i < 690; i+= 5){
	
		theoreticalPDF = new TF1("theoreticalPDF", "[0] / TMath::Exp(x / [1])", 0, 700);
		theoreticalPDF -> SetParameter(0, 1000.);
		theoreticalPDF -> SetParameter(1, 100.);
		
		TString ime = "toy_" + to_string(i);
		toy = new TH1F(ime, "toy", 200, 0., 700.);	
	
		m_H = (float)i;
		
		for (int j = 0; j < 10000; j++){

			if (rng -> Rndm() > a_SM * TMath::Power(m_H + b_SM, 2) + c_SM)
				toy -> Fill(rng -> Exp(100));
			else
				toy -> Fill(rng -> Gaus(m_H, sigma_SM * m_H));
		}
		theoreticalPDF -> FixParameter(1, 100.);
		toy -> Fit(theoreticalPDF, "Q", "", m_H - 10., m_H + 10.);
		chi2 = theoreticalPDF -> GetChisquare();
		
		expected_p_value = TestStatisticPDF -> Integral(TestStatisticPDF -> FindBin(chi2), TestStatisticPDF -> GetNbinsX()) / TestStatisticPDF -> Integral();
		expected_scan -> SetPoint(i / 5. - 2, m_H, expected_p_value);
	}

	gPad -> SetLogy();
	gPad -> SetGridx();
	gPad -> SetGridy();
	gPad -> SetLeftMargin(0.1);
	
	expected_scan -> SetLineColor(kBlack);
	expected_scan -> SetLineStyle(kDashed);
	expected_scan -> SetLineWidth(2);
	expected_scan -> SetMarkerColor(kBlack);
	expected_scan -> SetMarkerStyle(20);
	expected_scan -> SetMarkerSize(0.6);
	expected_scan -> SetTitle("Expected p-value scan");
	expected_scan -> GetXaxis() -> SetRangeUser(0, 700);
	expected_scan -> SetMinimum(0.00001);
	expected_scan -> GetXaxis() -> SetTitle("m_{H}");
	expected_scan -> GetYaxis() -> SetTitle("p-value");
	expected_scan -> GetYaxis() -> SetTitleOffset(0.7);
	expected_scan -> Draw();
	
	canvas -> Print("ExpectedPValueScan.pdf");
	
	

}
