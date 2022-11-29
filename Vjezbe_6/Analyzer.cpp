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

void Analyzer::PlotHistogram (){
	canvas = new TCanvas();
	canvas -> SetCanvasSize (900,900);
	canvas -> Divide (2,2);
	canvas -> cd (1);
	for (int i = 0; i < 4; i++){
		hist_ime = "LeptonPt_hist" + to_string (i+1);
		LeptonPt_hist[i] = new TH1F (hist_ime, "Transverzalni moment", 50, 0., 150.);
		hist_ime = "LeptonEta_hist" + to_string (i+1);
                LeptonEta_hist[i] = new TH1F (hist_ime, "Rapiditet", 50, -2.5, 2.5);
		hist_ime = "LeptonPhi_hist" + to_string (i+1);
                LeptonPhi_hist[i] = new TH1F (hist_ime, "Azimutalni kut", 40, -4., 4.);
		hist_ime = "LeptonBDT_hist" + to_string (i+1);
                LeptonBDT_hist[i] = new TH1F (hist_ime, "BDT score", 20, -1., 1.);
	}
	Mass_hist = new TH1F ("Mass_hist", "Rekonstruirana masa 4 leptona", 25, 90., 140.);
	entries = fChain -> GetEntriesFast();
	for (int i=0; i < entries;i++){
		fChain -> GetEntry (i);
		for (int j = 0; j < 4; j++){
			LeptonPt_hist[j] -> Fill (LepPt -> at (j));
			LeptonEta_hist[j] -> Fill (LepEta -> at (j));
			LeptonPhi_hist[j] -> Fill (LepPhi -> at (j));
			LeptonBDT_hist[j] -> Fill (LepBDT -> at (j));
		}
		lept1.SetPtEtaPhiM(LepPt -> at (0), LepEta -> at (0), LepPhi -> at (0), 0.);
		lept2.SetPtEtaPhiM(LepPt -> at (1), LepEta -> at (1), LepPhi -> at (1), 0.);
		lept3.SetPtEtaPhiM(LepPt -> at (2), LepEta -> at (2), LepPhi -> at (2), 0.);
		lept4.SetPtEtaPhiM(LepPt -> at (3), LepEta -> at (3), LepPhi -> at (3), 0.);

		if (LepLepId -> at (0) + LepLepId -> at (1) == 0 && LepLepId -> at (2)+ LepLepId -> at (3) == 0){
			Z1 = lept1 + lept2;
			Z2 = lept3 + lept4;
			Higgs = Z1 + Z2;
		}
		Mass_hist -> Fill (Higgs.M());
	}
	for (int i = 0; i < 4; i++){
		LeptonPt_hist[i] -> SetStats (0);
                LeptonEta_hist[i] -> SetStats (0);
                LeptonPhi_hist[i] -> SetStats (0);
                LeptonBDT_hist[i] -> SetStats (0);
		
		LeptonPt_hist[i] -> GetXaxis() -> SetTitle ("p_{T} [GeV]");
                LeptonPt_hist[i] -> GetYaxis() -> SetTitle ("Events / 3 GeV");
		LeptonPt_hist[i] -> GetXaxis() -> SetLabelSize (0.04);
		LeptonPt_hist[i] -> GetYaxis() -> SetLabelSize (0.04);
		LeptonPt_hist[i] -> GetXaxis() -> SetTitleOffset (1.9);
		LeptonPt_hist[i] -> SetMaximum (1.6 * LeptonPt_hist[3] -> GetMaximum());		

		LeptonEta_hist[i] -> GetXaxis() -> SetTitle ("#Eta");
                LeptonEta_hist[i] -> GetYaxis() -> SetTitle ("Events / 0.1");
		LeptonEta_hist[i] -> GetXaxis() -> SetLabelSize (0.04);
                LeptonEta_hist[i] -> GetYaxis() -> SetLabelSize (0.04);
                LeptonEta_hist[i] -> GetXaxis() -> SetTitleOffset (1.8);
                LeptonEta_hist[i] -> SetMaximum (1.8 * LeptonEta_hist[3] -> GetMaximum());

		LeptonPhi_hist[i] -> GetXaxis() -> SetTitle ("#Phi");
                LeptonPhi_hist[i] -> GetYaxis() -> SetTitle ("Events / 0.2");
		LeptonPhi_hist[i] -> GetXaxis() -> SetLabelSize (0.04);
                LeptonPhi_hist[i] -> GetYaxis() -> SetLabelSize (0.04);
                LeptonPhi_hist[i] -> GetXaxis() -> SetTitleOffset (1.8);
                LeptonPhi_hist[i] -> SetMaximum (1.8 * LeptonPhi_hist[3] -> GetMaximum());

		LeptonBDT_hist[i] -> GetXaxis() -> SetTitle ("BDT score");
                LeptonBDT_hist[i] -> GetYaxis() -> SetTitle ("Events / 0.1");
		LeptonBDT_hist[i] -> GetXaxis() -> SetLabelSize (0.04);
                LeptonBDT_hist[i] -> GetYaxis() -> SetLabelSize (0.04);
                LeptonBDT_hist[i] -> GetXaxis() -> SetTitleOffset (1.8);
                LeptonBDT_hist[i] -> SetMaximum (200 * LeptonBDT_hist[3] -> GetMaximum());
	}
	LeptonPt_hist[0] -> SetLineColor (kRed);
	LeptonEta_hist[0] -> SetLineColor (kRed);
        LeptonPhi_hist[0] -> SetLineColor (kRed);
        LeptonBDT_hist[0] -> SetLineColor (kRed);	
	
	LeptonPt_hist[0] -> SetFillColorAlpha (kRed,0.35);
        LeptonEta_hist[0] -> SetFillColorAlpha (kRed,0.35);
        LeptonPhi_hist[0] -> SetFillColorAlpha (kRed,0.35);
        LeptonBDT_hist[0] -> SetFillColorAlpha (kRed,0.35);

/*	LeptonPt_hist[0] -> SetFillStyle (4050);
        LeptonEta_hist[0] -> SetFillStyle (4050);
        LeptonPhi_hist[0] -> SetFillStyle (4050);
        LeptonBDT_hist[0] -> SetFillStyle (4050);*/

	LeptonPt_hist[1] -> SetLineColor (kBlue);
        LeptonEta_hist[1] -> SetLineColor (kBlue);
        LeptonPhi_hist[1] -> SetLineColor (kBlue);
        LeptonBDT_hist[1] -> SetLineColor (kBlue);

	LeptonPt_hist[1] -> SetFillColorAlpha (kBlue,0.35);
        LeptonEta_hist[1] -> SetFillColorAlpha (kBlue,0.35);
        LeptonPhi_hist[1] -> SetFillColorAlpha (kBlue,0.35);
        LeptonBDT_hist[1] -> SetFillColorAlpha (kBlue,0.35);

/*	LeptonPt_hist[1] -> SetFillStyle (4050);
        LeptonEta_hist[1] -> SetFillStyle (4050);
        LeptonPhi_hist[1] -> SetFillStyle (4050);
        LeptonBDT_hist[1] -> SetFillStyle (4050);*/

	LeptonPt_hist[2] -> SetLineColor (kGreen);
        LeptonEta_hist[2] -> SetLineColor (kGreen);
        LeptonPhi_hist[2] -> SetLineColor (kGreen);
        LeptonBDT_hist[2] -> SetLineColor (kGreen);

	LeptonPt_hist[2] -> SetFillColorAlpha (kGreen,0.35);
        LeptonEta_hist[2] -> SetFillColorAlpha (kGreen,0.35);
        LeptonPhi_hist[2] -> SetFillColorAlpha (kGreen,0.35);
        LeptonBDT_hist[2] -> SetFillColorAlpha (kGreen,0.35);

/*	LeptonPt_hist[2] -> SetFillStyle (4050);
        LeptonEta_hist[2] -> SetFillStyle (4050);
        LeptonPhi_hist[2] -> SetFillStyle (4050);
        LeptonBDT_hist[2] -> SetFillStyle (4050);*/
	
	LeptonPt_hist[3] -> SetLineColor (kBlack);
        LeptonEta_hist[3] -> SetLineColor (kBlack);
        LeptonPhi_hist[3] -> SetLineColor (kBlack);
        LeptonBDT_hist[3] -> SetLineColor (kBlack);

	LeptonPt_hist[3] -> SetFillColorAlpha (kBlack,0.35);
        LeptonEta_hist[3] -> SetFillColorAlpha (kBlack,0.35);
        LeptonPhi_hist[3] -> SetFillColorAlpha (kBlack,0.35);
        LeptonBDT_hist[3] -> SetFillColorAlpha (kBlack,0.35);

/*	LeptonPt_hist[3] -> SetFillStyle (4050);
        LeptonEta_hist[3] -> SetFillStyle (4050);
        LeptonPhi_hist[3] -> SetFillStyle (4050);
        LeptonBDT_hist[3] -> SetFillStyle (4050);*/
	
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);	

	LeptonPt_hist[0] -> Draw ("HIST");
	LeptonPt_hist[1] -> Draw ("HIST SAME");
	LeptonPt_hist[2] -> Draw ("HIST SAME");
	LeptonPt_hist[3] -> Draw ("HIST SAME");

	legend = CreateLegend (LeptonPt_hist[0], LeptonPt_hist[1], LeptonPt_hist[2], LeptonPt_hist[3]);
	legend -> Draw ();

	canvas -> cd (2);
	gPad -> SetLeftMargin(0.15);
	gPad -> SetBottomMargin (0.15);
	LeptonEta_hist[0] -> Draw ("HIST");
        LeptonEta_hist[1] -> Draw ("HIST SAME");
        LeptonEta_hist[2] -> Draw ("HIST SAME");
        LeptonEta_hist[3] -> Draw ("HIST SAME");

        legend = CreateLegend (LeptonEta_hist[0], LeptonEta_hist[1], LeptonEta_hist[2], LeptonEta_hist[3]);
        legend -> Draw ();

	canvas -> cd (3);
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);
	LeptonPhi_hist[0] -> Draw ("HIST");
        LeptonPhi_hist[1] -> Draw ("HIST SAME");
        LeptonPhi_hist[2] -> Draw ("HIST SAME");
        LeptonPhi_hist[3] -> Draw ("HIST SAME");

        legend = CreateLegend (LeptonPhi_hist[0], LeptonPhi_hist[1], LeptonPhi_hist[2], LeptonPhi_hist[3]);
        legend -> Draw ();

	canvas -> cd (4);
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);
	gPad -> SetLogy();
	LeptonBDT_hist[0] -> Draw ("HIST");
        LeptonBDT_hist[1] -> Draw ("HIST SAME");
        LeptonBDT_hist[2] -> Draw ("HIST SAME");
        LeptonBDT_hist[3] -> Draw ("HIST SAME");

        legend = CreateLegend (LeptonBDT_hist[0], LeptonBDT_hist[1], LeptonBDT_hist[2], LeptonBDT_hist[3]);
        legend -> Draw ();

	canvas -> Print ("hist_zad2.pdf");
	canvas -> Print ("hist_zad2.png");
	canvas -> Print ("hist_zad2.root");

	canvas = new TCanvas ();
	canvas -> SetCanvasSize (900,900);
	Mass_hist -> GetXaxis () -> SetTitle ("m_{4l} [GeV]");
	Mass_hist -> GetYaxis () -> SetTitle ("Events / 2 GeV");	
	Mass_hist -> SetMaximum(1.5 * Mass_hist -> GetMaximum ());
	Mass_hist -> SetStats (0);
	Mass_hist -> SetLineColor (kRed);
	Mass_hist -> SetFillColor (kRed);
	Mass_hist -> Draw ("HIST");
	legend = new TLegend (0.5, 0.7, 0.9, 0.9);
	legend -> AddEntry (Mass_hist, "gluon-gluon fuzija", "f");
	legend -> SetTextSize (0.03);
	legend -> Draw ();
	canvas -> Print ("hist_zad3.pdf");
	canvas -> Print ("hist_zad3.png");
	canvas -> Print ("hist_zad3.root");
}

TLegend* Analyzer::CreateLegend (TH1F *lepton1, TH1F *lepton2, TH1F *lepton3, TH1F *lepton4){
	TLegend *leg = new TLegend (0.5, 0.7, 0.9, 0.9);
	leg -> AddEntry (lepton1, "1. lepton", "f");
	leg -> AddEntry (lepton2, "2. lepton", "f");
	leg -> AddEntry (lepton3, "3. lepton", "f");
	leg -> AddEntry (lepton4, "4. lepton", "f");
	
	return leg;

}
