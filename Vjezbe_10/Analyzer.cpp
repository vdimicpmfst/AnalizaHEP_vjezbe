#include"Analyzer.h"


Analyzer::Analyzer (){

}

Analyzer::~Analyzer(){

}


void Analyzer::ChiSquare(){

	c = new TCanvas ();
	c -> SetCanvasSize(600, 400);
	
	gStyle -> SetOptFit();

	double sila[5] = {1, 2, 3, 4, 5};
	double a[5] = {9.8, 21.2, 34.5, 39.9, 48.5};
	double sigma_sila[5] = {0., 0., 0., 0., 0.};
	double sigma_a[5] = {1.0, 1.9, 3.1, 3.9, 5.1};

	graph = new TGraphErrors(5, sila, a, sigma_sila, sigma_a);
	graph -> SetTitle ("Mjerenja mase kuglice;F [N];a [m/s^{2}]");
	//graph -> GetXAxis() -> SetTitle ("F [N]");
	//graph -> GetYAxis() -> SetTitle ("a [m/s^{2}]");
	graph -> SetMarkerColor(kBlack);
	graph -> SetMarkerStyle(21);
	graph -> Draw("AP");
	
	fit = new TF1 ("fit", "x / [0]", 0., 50.);
	fit -> SetParName(0, "masa");
	fit -> SetParameter(0, 0.1);
	graph -> Fit(fit);	

	c -> Print("Mjerenja.pdf");

	c -> Destructor();

	c = new TCanvas();
	c -> SetCanvasSize(600, 400);

	chi_square_fit = new TF1 ("Chi-Square", "pow(([0] - [1] * x) / [2], 2.0) + pow(([3] - [4] * x) / [5], 2.0) + pow(([6] - [7] * x) / [8], 2.0) + pow(([9] - [10] * x) / [11], 2.0) + pow(([12] - [13] * x) / [14], 2.0)", 9.4, 11.0);
	for (int i = 0; i < 3 * 5; i+=3){
		chi_square_fit -> SetParameter(i, a[i/3]);
		chi_square_fit -> SetParameter(i + 1, sila[i/3]);
		chi_square_fit -> SetParameter(i + 2, sigma_a[i/3]);
		
	}
	chi_square_fit -> SetTitle ("Chi-Square funkcija;m^{-1} [kg^{-1}];#chi^{2}");
	chi_square_fit -> Draw();

	Float_t theta, xy = 0, x2 = 0, y2 = 0;
	for (int i = 0; i < 5; i++){
		xy += a[i] * sila[i];
		x2 += sila[i] * sila[i];
		y2 += a[i] * a[i];
	}
	
	theta = xy / x2;
	Float_t sigma_theta = sqrt((y2 / x2 - theta * theta) / 5);
	Float_t masa = 1 / theta;
	Float_t sigma_masa = sigma_theta / theta / theta;

	cout << "Analiticki izracun mase: m = " << masa << endl;
	cout << "Analiticki izracun standardne devijacije: sigma = " << sigma_masa << endl;

	masa = chi_square_fit -> GetMinimumX();
	sigma_masa = masa - chi_square_fit -> GetX(chi_square_fit -> GetMinimum() + 1, masa - 5., masa - 0.01);
	Float_t sigma_masa_up = chi_square_fit -> GetX(chi_square_fit -> GetMinimum() + 1.0, masa + 0.01, masa + 5.0) - masa;
	
	cout << "Masa iz chi-square metode: m = " << 1. / masa << endl;
	cout << "Neodredenost iz chi-square metode: sigma_+ = " << sigma_masa_up / pow(masa, 2.) << '\t' << "sigma_- = " << sigma_masa / pow (masa, 2) << endl;
	
	chi_square_fit -> SetMinimum(1.0);
	
	line_h = new TLine (masa - sigma_masa, chi_square_fit -> GetMinimum() + 1.0, masa + sigma_masa_up, chi_square_fit -> GetMinimum() + 1.0);
	line_h -> SetLineColor(kBlack);
	line_h -> SetLineStyle(kDashed);
	line_h -> Draw();
	
	line_v1 = new TLine (masa - sigma_masa, 1.0, masa - sigma_masa, chi_square_fit -> GetMinimum() + 1.0);
	line_v1 -> SetLineColor(kBlack);
	line_v1 -> SetLineStyle(kDashed);
	line_v1 -> Draw();

	line_v2 = new TLine (masa, 1.0, masa, chi_square_fit -> GetMinimum());
	line_v2 -> SetLineColor(kBlack);
	line_v2 -> SetLineStyle(kDashed);
	line_v2 -> Draw();

	line_v3 = new TLine(masa + sigma_masa_up, 1.0, masa + sigma_masa_up, chi_square_fit -> GetMinimum() + 1.0);
	line_v3 -> SetLineColor(kBlack);
	line_v3 -> SetLineStyle(kDashed);
	line_v3 -> Draw();

	c -> Print("Chi_square.pdf");	

}
