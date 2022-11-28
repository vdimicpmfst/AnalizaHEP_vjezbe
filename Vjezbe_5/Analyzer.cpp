#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

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
	if (jentry%1000==0)
		fChain -> Show(jentry);
   }
}

void Analyzer::PlotHistogram(){
	TCanvas *canvas = new TCanvas ();
	canvas -> SetCanvasSize(1500, 700);
	TH1F *hist_pt1 = new TH1F("pT1", "pT1", 50, 0, 300);
	//TH1F *hist_pt2 = new TH1F("pT2", "pT2", 50, 0, 300);
	Long64_t entries = fChain -> GetEntriesFast();
	for (Long64_t i = 0; i < entries; i++){
		fChain -> GetEntry (i);
		hist_pt1 -> Fill (sqrt (DecayParticle1_px*DecayParticle1_px+DecayParticle1_py*DecayParticle1_py));
		//hist_pt2 -> Fill (sqrt (DecayParticle2_px*DecayParticle2_px+DecayParticle2_py*DecayParticle2_py));
	}
	gStyle->SetOptStat(0);
	hist_pt1 -> SetLineColor (kRed);
	hist_pt1 -> SetFillColor (kRed);
	hist_pt1 -> SetTitle ("Transverzalna kolicina gibanja za 1 cesticu iz raspada");
	//TLegend *legend = new TLegend (0.6, 0.75, 0.9, 0.9, "", "NB");
	TLegend *legend = new TLegend(0.6,0.75,0.9,0.9);
	legend -> SetHeader ("Simulacija", "C");
	legend -> AddEntry (hist_pt1, "Distribucija pT1", "l");
	hist_pt1 -> Draw();
	//hist_pt2 -> Draw ("same");
	canvas -> Print("hist_zad3.pdf");
	canvas -> Print("hist_zad3.png");
	canvas -> Print("hist_zad3.root");
}
