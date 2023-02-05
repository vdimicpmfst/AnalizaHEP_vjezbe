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
	graph -> SetTitle ("Mjerenja mase kuglice;F [N];a [m/s^2]");
	//graph -> GetXAxis() -> SetTitle ("F [N]");
	//graph -> GetYAxis() -> SetTitle ("a [m/s^2]");
	graph -> SetMarkerColor(kBlack);
	graph -> SetMarkerStyle(21);
	graph -> Draw("AP");
	
	fit = new TF1 ("fit", "x / [0]", 0., 50.);
	fit -> SetParName(0, "masa");
	fit -> SetParameter(0, 0.1);
	graph -> Fit(fit);	

	c -> Print("Mjerenja.pdf");
	

}
