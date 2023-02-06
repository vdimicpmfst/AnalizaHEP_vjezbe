#include"Analyzer.h"


Analyzer::Analyzer(){


}

Analyzer::~Analyzer(){


}

double Analyzer::Binom(int r, double p, int N){

return TMath::Binomial(N, r) * pow(p, r) * pow(1 - p, N - r);

}

pair<double, double> Analyzer::CPinterval(double CL, int N, int m){

int r;
double sum_up = 0, sum_down = 0, p_up = 1., p_down = 0, dp = 0.001;

while (sum_up < (1 - CL) / 2.){
	sum_up = 0;
	for (r = 0; r <= m; r++)
		sum_up += Binom (r, p_up, N);
	p_up -= dp;
	
} 

while (sum_down < (1 - CL) / 2.){
	sum_down = 0;
	for (r = m; r <= N; r++)
		sum_down += Binom(r, p_down, N);
	p_down += dp;

}

if (p_down - 2 * dp < 0)
	return make_pair(0, p_up + 2 * dp);
else if (p_up + 2 * dp > 1.)
	return make_pair(p_down - 2 * dp, 1);
else
	return make_pair(p_down - 2 * dp, p_up + 2 * dp);

}

void Analyzer::CPpojas(int N, double CL){

	gStyle -> SetOptStat(0);
	THStack *hstack = new THStack("hs", "");
	TH1F *hist_up = new TH1F("up", "up", 11, 0, 11);
	TH1F *hist_down = new TH1F ("down", "down", 11, 0, 11);
	TCanvas *canvas = new TCanvas();
	canvas -> SetCanvasSize(1200, 800);
	for (int i = 0; i <= N; i++){
		hist_up -> SetBinContent(i + 1, CPinterval(CL, N, i).second - CPinterval(CL, N, i).first);
		hist_down -> SetBinContent(i + 1, CPinterval(CL, N, i).first);
		hist_up -> GetXaxis() -> SetBinLabel(i + 1, to_string(i).c_str());
		hist_down -> GetXaxis() -> SetBinLabel(i + 1, to_string(i).c_str());
	}

	hist_down -> SetFillColor(kWhite);
	hist_down -> GetXaxis() -> SetTitle("m");
	hist_up -> SetFillColor(kOrange + 7);
	hstack -> Add(hist_down);
	hstack -> Add(hist_up);
	hstack -> Draw();
	hstack -> GetXaxis() -> SetTitle("m");
	hstack -> GetYaxis() -> SetTitle("p");
	hstack -> SetTitle("Clopper-Pearson confidence belt");

	TLine *l1 = new TLine(6.5, 0, 6.5, CPinterval(CL, N, 6).second);
	TLine *l2 = new TLine(0, CPinterval(CL, N, 6).first, 6.5, CPinterval(CL, N, 6).first);
	TLine *l3 = new TLine(0, CPinterval(CL, N, 6).second, 6.5, CPinterval(CL, N, 6).second);
	l1 -> SetLineStyle(kDashed);
	l2 -> SetLineStyle(kDashed);
	l3 -> SetLineStyle(kDashed);
	l1 -> Draw("SAME");
	l2 -> Draw("SAME");
	l3 -> Draw("SAME"); 

	canvas -> Print("CPpojas.pdf"); 

}
