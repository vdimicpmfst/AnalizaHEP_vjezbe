#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}


void Analyzer::ReconstructHiggs(){

	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	
	RecMass = new TH1F("RecoMass", "RecoMass", 200, 0., 700.);

	if (fChain == 0)
		return;
	Long64_t nentries = fChain -> GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	for (Long64_t jentry = 0; jentry < nentries; jentry ++){
		
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;
		nb = fChain -> GetEntry(jentry);
		nbytes += nb;
		
		p1.SetXYZM(particle1_px, particle1_py, particle1_pz, 0);
		p2.SetXYZM(particle2_px, particle2_py, particle2_pz, 0);
		RecMass -> Fill((p1 + p2).M());
	}
	
	gStyle -> SetOptStat(0);
	RecMass -> SetTitle("Reconstructed invariant mass");
	RecMass -> GetXaxis() -> SetTitle("m_{#gamma#gamma}");
	RecMass -> GetYaxis() -> SetTitle("Events / 3.5 GeV");
	RecMass -> SetMarkerStyle(20);
	RecMass -> SetMarkerSize(0.6);
	RecMass -> SetMarkerColor(kBlack);
	RecMass -> Draw("EP");

	canvas -> Print("ReconstructedMass.pdf");

}

void Analyzer::GenerateTestStatisticPDF(int n){

	
	canvas = new TCanvas();
	canvas -> SetCanvasSize(700, 700);
	
	TestStatisticPDF = new TH1F("TestStatisticPDF", "TestStatisticPDF", 300, 0, 30);

	theoreticalPDF = new TF1("theoreticalPDF", "[0] / TMath::Exp(x / [1])", 0, 700);
	theoreticalPDF -> SetParameter(0, 1000.);
	theoreticalPDF -> SetParameter(1, 100.);
	
	float chi2, m_H = 0.;
	
	for (int i = 0; i < n; i++){

		TString ime = "toy_" + to_string(i);
		toy = new TH1F(ime, "toy", 200, 0., 700.);
		for (int j = 0; j < 100000; j++)
			toy -> Fill(rng -> Exp(100));

		theoreticalPDF -> FixParameter(1, 100.);
		for (int j = 10; j < 690; j+=5){

			m_H = j / 1.;
			toy -> Fit(theoreticalPDF, "Q", "", m_H - 10., m_H + 10.);
			chi2 = theoreticalPDF -> GetChisquare();
			//cout << chi2 << endl;
			TestStatisticPDF -> Fill(chi2);

		}
		//delete toy;
	/*  for(int i = 0; i < n; i++)
  		{
    			TString name = "toy_" + std::to_string(i);
    			toy = new TH1F(name,"toy",200,0.,700.);

    			for(int j = 0; j < 100000; j++) toy->Fill(rng->Exp(100));

    			theoreticalPDF->FixParameter(1,100.); //fix the parameter to theoretical value

    			for(int i = 10; i < 690; i+=5) // do the fit doing 5 GeV steps in 10-690 GeV region
    			{
      				m_H = i/1.0;

      				toy->Fit(theoreticalPDF,"Q","",m_H-10,m_H+10); // perform the fit in the 20 GeV window
      				chi2 = theoreticalPDF->GetChisquare();
      				TestStatisticPDF->Fill(chi2);
    			}
  		}*/

	}

	gStyle -> SetOptStat(0);
	gPad -> SetBottomMargin(0.2);
	TestStatisticPDF -> SetTitle("Test Statistic PDF");
	TestStatisticPDF -> GetXaxis() -> SetTitle("#chi^{2}(N, #zeta_{SM})");
	TestStatisticPDF -> GetXaxis() -> SetTitleOffset(1.5);
	TestStatisticPDF -> Scale(1. / TestStatisticPDF -> Integral());
	TestStatisticPDF -> Draw("HIST");

	canvas -> Print("TestStatisticPDF.pdf");
	delete canvas;

}
