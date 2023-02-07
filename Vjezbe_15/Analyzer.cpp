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
