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
	t = 0.;
	for (int i = 0; i < nentries; i++){
		tree -> GetEntry(i);
		t += height;
	}
	t = t / 100.;
	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	gStyle -> SetOptStat(0);
	double p_value = 0;
	
	testStatistic_PDF -> SetFillColor(kRed - 2);
	testStatistic_PDF -> SetLineColor(kRed - 2);
	testStatistic_PDF -> SetTitle("Test Statistic PDF distribution");
	testStatistic_PDF -> GetXaxis() -> SetTitle("#bar{h} [cm]");
	testStatistic_PDF -> Scale(1. / testStatistic_PDF -> Integral());
	testStatistic_PDF -> Draw("HIST");

	TLine *l = new TLine(t, 0., t, 0.04);
	l -> SetLineWidth(3);
	l -> Draw();
	
	canvas -> Print("TestStatistic_PDF.pdf");

	p_value = testStatistic_PDF -> Integral(testStatistic_PDF -> FindBin(t), 100);
	cout << "p-value za H0 je: p = "<< p_value << endl;
	cout << "Signifikantnost je: z = " << Significance(p_value) << endl;
	
	
	
}

void Analyzer::GenerateTestStatistic_H0(){

/*	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	gStyle -> SetOptStat(0);
*/	
	testStatistic_PDF = new TH1F("testStatistic_PDF", "Test Statistic PDF", 100, 160., 170.);
	double sum;
	
	for (int i = 0; i < 1000000; i++){
		sum = 0.;
		for (int j = 0; j < 100; j++)
			sum += rng -> Gaus(164.7, 7.1);
		testStatistic_PDF -> Fill(sum / 100.);
			//cout << sum  << endl; 
	}
	
/*	canvas -> cd();
	testStatistic_PDF -> SetFillColor(kRed - 2);
	testStatistic_PDF -> SetLineColor(kRed - 2);
	
	testStatistic_PDF -> SetTitle("Test Statistic PDF distribution");
	testStatistic_PDF -> GetXaxis() -> SetTitle("#bar{h} [cm]");

	testStatistic_PDF -> Scale(1. / testStatistic_PDF -> Integral());
	testStatistic_PDF -> Draw("HIST");
	
	canvas -> Print("test.pdf");
*/
}


double Analyzer::Significance(double p_value){

return TMath::Sqrt(2) * TMath::ErfcInverse(2 * p_value);
}

void Analyzer::CompareHypothesis(TString drzava, double mu, double sigma){
	
	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	gStyle -> SetOptStat(0);
	testStatistic_H0 = new TH1F("testStatistic_H0" + drzava, "H0 Test Statistic PDF", 150, 160., 175.);
	testStatistic_H1 = new TH1F("testStatistic_H1" + drzava, "H1 Test Statistic PDF", 150, 160., 175.);

	double sumh0, sumh1;

	for (int i = 0; i < 1000000; i++){
		sumh0 = 0.;
		sumh1 = 0.;
		for (int j = 0; j < 100; j++){
			sumh0 += rng -> Gaus(168.0, 7.0);
			sumh1 += rng -> Gaus(mu, sigma);
		}
		testStatistic_H0 -> Fill(sumh0 / 100.);
		testStatistic_H1 -> Fill(sumh1 / 100.);
	}
	
	testStatistic_H0 -> SetFillColor(kRed - 2);
	testStatistic_H0 -> SetLineColor(kRed - 2);
	testStatistic_H0 -> SetTitle("Hypothesis testing");
	testStatistic_H0 -> GetXaxis() -> SetTitle("#bar{h} [cm]");

	testStatistic_H0 -> Scale(1. / testStatistic_H0 -> Integral());
	testStatistic_H0 -> Draw("HIST");

	testStatistic_H1 -> SetFillColor(kBlue - 4);
        testStatistic_H1 -> SetLineColor(kBlue - 4);
        testStatistic_H1 -> SetTitle("Hypothesis testing");
        testStatistic_H1 -> GetXaxis() -> SetTitle("#bar{h} [cm]");

        testStatistic_H1 -> Scale(1. / testStatistic_H1 -> Integral());
        testStatistic_H1 -> Draw("HIST SAME");

	TLine *l = new TLine(t, 0., t, 0.4);
	l -> SetLineWidth(3);
	l -> Draw();

	TLegend *legend = new TLegend(0.7, 0.6, 0.9, 0.9);
	legend -> AddEntry(testStatistic_H0, "Spain", "f");
	legend -> AddEntry(testStatistic_H1, drzava, "f");
	legend -> Draw();

	canvas -> Print("TestStatistic_SpainVs" + drzava + ".pdf");

	double p_H0, p_H1;
	
	if (mu < 168){
		p_H0 = testStatistic_H0 -> Integral(0, testStatistic_H0 -> FindBin(t));
		p_H1 = testStatistic_H1 -> Integral(testStatistic_H1 -> FindBin(t), 150);
	}
	else{
		p_H0 = testStatistic_H0 -> Integral(testStatistic_H0 -> FindBin(t), 100);
		p_H1 = testStatistic_H1 -> Integral(0, testStatistic_H1 -> FindBin(t));
	}

	cout << "Iskljucujemo alternativnu hipotezu o drzavi " << drzava << " s " << (1 - p_H1 / p_H0) * 100 << "\% CL." << endl;


}
