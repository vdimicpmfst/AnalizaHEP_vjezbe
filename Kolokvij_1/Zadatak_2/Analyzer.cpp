#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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

void Analyzer::Plot2DHistogram(){
	canvas = new TCanvas ();
	canvas -> SetCanvasSize (900, 900);
	canvas -> SetTitle ("dR vs J/#psi reconstructed mass");
	hist = new TH2F ("dR vs J/#psi reconstructed mass", "dR vs J/#psi reconstructed mass", 100, 2., 4., 100, 0., 1.5);
	entries = fChain -> GetEntriesFast ();
	for (Long64_t i = 0; i < entries; i++){
		fChain -> GetEntry (i);
		elektron.SetPtEtaPhiM (ele_pt -> at (0), ele_eta -> at (0), ele_phi -> at (0), 0);
		pozitron.SetPtEtaPhiM (ele_pt -> at (1), ele_eta -> at (1), ele_phi -> at (1), 0);
		Jpsi = elektron + pozitron;
		hist -> Fill (Jpsi.M(), dR);	
	}
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);
	gStyle -> SetPalette (kRainBow);
	hist -> Draw ("COLZ");
	hist -> SetStats (0);
	hist -> SetContour (100);
	hist -> GetXaxis () -> SetTitle ("J/#psi reconstructed mass / 0.02 GeV");
	hist -> GetXaxis () -> SetLabelSize (0.03);
	hist -> GetYaxis () -> SetTitle ("dR / 0.015");
        hist -> GetYaxis () -> SetLabelSize (0.03);
	
	canvas -> Print ("zad2.pdf");
	canvas -> Print ("zad2.png");
	canvas -> Print ("zad2.root");


}
