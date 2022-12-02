#include "Generator.h"

Generator::Generator(){

}

void Generator::GeneratePDF(){
	srand((unsigned)1);
	i = 0;
	canvas = new TCanvas ();
	hist = new TH1F ("GeneratePDF", "GeneratePDF", 48, -3., 9.);
	int j=0;
	while (i < 1E5){
		rng = -3 + 12 * (float)rand () / RAND_MAX;
		f = (-rng * rng + 6 * rng + 27) / 36.;
		rng2 = -3 + 12 * (float)rand () /RAND_MAX;
		if (rng2 < f){
			hist -> Fill (rng);
			i++;
		}
//	j++;
	}
//	cout << j << endl;
//	cout << i << endl;
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);
	canvas -> SetCanvasSize (900, 900);
	canvas -> SetTitle ("GeneratePDF");
	hist -> Draw ("HIST");
	hist -> GetXaxis () -> SetTitle ("Generated value");
	hist -> GetYaxis () -> SetTitle ("Events / 0.25");
	hist -> GetXaxis () -> SetLabelSize (0.04);
	hist -> GetYaxis () -> SetLabelSize (0.04);
	hist -> SetFillColor (kGreen);
	hist -> SetLineColor (kGreen);
	
	canvas -> Print ("zad1.pdf");
	canvas -> Print ("zad1.png");
	canvas -> Print ("zad1.root");

}
