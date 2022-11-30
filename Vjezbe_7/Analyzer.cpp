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

void Analyzer::PlotHistogram (TString input_name){
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
//	Mass_hist_signal = new TH1F ("Mass_hist_signal", "Rekonstruirana masa 4 leptona", 50, 70., 170.);
//	Mass_hist_background = new TH1F ("Mass_hist_background", "Rekonstruirana masa 4 leptona", 50, 70., 170.);
	entries = fChain -> GetEntriesFast();
	input_file = new TFile (input_name);
	hCounters = (TH1F*) input_file -> Get ("ZZTree/Counters");
	sum_weight = (Float_t)hCounters -> GetBinContent (40);
	input_tree = (TTree*) input_file -> Get ("ZZTree/candTree");
	Init (input_tree, input_name);
	for (int i=0; i < entries;i++){
		fChain -> GetEntry (i);
		event_weight = (137. * 1000 * xsec * overallEventWeight) / sum_weight;
		for (int j = 0; j < 4; j++){
			LeptonPt_hist[j] -> Fill (LepPt -> at (j), event_weight);
			LeptonEta_hist[j] -> Fill (LepEta -> at (j), event_weight);
			LeptonPhi_hist[j] -> Fill (LepPhi -> at (j), event_weight);
			LeptonBDT_hist[j] -> Fill (LepBDT -> at (j), event_weight);
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
		if (input_name.Contains("ggH125")){
			Mass_hist_signal -> Fill (Higgs.M(), event_weight);
			
		}
		if (input_name.Contains("qqZZ")){
                        Mass_hist_background -> Fill (Higgs.M(), event_weight);

                }
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
	if (input_name.Contains("ggH125")){
	canvas -> Print ("Leptons_signal.pdf");
	canvas -> Print ("Leptons_signal.png");
	canvas -> Print ("Leptons_signal.root");
	}
	if (input_name.Contains("qqZZ")){
        canvas -> Print ("Leptons_background.pdf");
        canvas -> Print ("Leptons_background.png");
        canvas -> Print ("Leptons_background.root");
        }

/*	canvas = new TCanvas ();
	canvas -> SetCanvasSize (900,900);
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);
	Mass_hist -> GetXaxis () -> SetTitle ("m_{4l} [GeV]");
	Mass_hist -> GetYaxis () -> SetTitle ("Events / 2 GeV");	
	Mass_hist -> SetMaximum(1.5 * Mass_hist -> GetMaximum ());
	Mass_hist -> Draw ("HIST");
	legend = new TLegend (0.5, 0.8, 0.9, 0.9);
	legend -> AddEntry (Mass_hist, "gluon-gluon fuzija", "f");
	legend -> SetTextSize (0.03);
	legend -> Draw ();
	if (input_name.Contains("ggH125")){
	canvas -> Print ("Mass_hist_sig.pdf");
	canvas -> Print ("Mass_hist_sig.png");
	canvas -> Print ("Mass_hist_sig.root");
	}
	if (input_name.Contains("qqZZ")){
        canvas -> Print ("Mass_hist_back.pdf");
        canvas -> Print ("Mass_hist_back.png");
        canvas -> Print ("Mass_hist_back.root");
        }
*/
	cout << Mass_hist_signal -> Integral () << endl;
	cout << Mass_hist_background -> Integral () << endl;
}

TLegend* Analyzer::CreateLegend (TH1F *lepton1, TH1F *lepton2, TH1F *lepton3, TH1F *lepton4){
	TLegend *leg = new TLegend (0.5, 0.7, 0.9, 0.9);
	leg -> AddEntry (lepton1, "1. lepton", "f");
	leg -> AddEntry (lepton2, "2. lepton", "f");
	leg -> AddEntry (lepton3, "3. lepton", "f");
	leg -> AddEntry (lepton4, "4. lepton", "f");
	
	return leg;

}

void Analyzer::PlotMass(){
        canvas = new TCanvas ();
        canvas -> SetCanvasSize (900,900);
        gPad -> SetLeftMargin (0.15);
        gPad -> SetBottomMargin (0.15);
	Mass_hist_signal -> SetStats(0);
	Mass_hist_signal -> SetLineColor (kGreen);
	Mass_hist_signal -> SetFillColorAlpha (kGreen, 0.35);
	Mass_hist_background -> SetStats (0);
	Mass_hist_background -> SetLineColor (kRed);
	Mass_hist_background -> SetFillColorAlpha (kRed, 0.35);
	Mass_hist = new THStack ("stack", "stack");
        Mass_hist -> Add (Mass_hist_signal);
	Mass_hist -> Add (Mass_hist_background);
	//Mass_hist -> GetXaxis () -> SetTitle ("m_{4l} [GeV]");
        //Mass_hist -> GetYaxis () -> SetTitle ("Events / 2 GeV");
        Mass_hist -> SetMaximum(1.4 * Mass_hist -> GetMaximum ());
        Mass_hist -> Draw ("HIST");
        legend = new TLegend (0.5, 0.8, 0.9, 0.9);
        legend -> AddEntry (Mass_hist_signal, "gluon-gluon fuzija", "f");
	legend -> AddEntry (Mass_hist_background, "q#bar{q} #rightarrow Z", "f");
        legend -> SetTextSize (0.03);
        legend -> Draw ();
        canvas -> Print ("Mass_hist.pdf");
        canvas -> Print ("Mass_hist.png");
        canvas -> Print ("Mass_hist.root");

        cout << "Ocekivani broj Higgs bozona za 137/fb je " << Mass_hist_signal -> Integral () << endl;
	cout << "Ocekivani broj pozadinskih Higgs bozona za 137/fb je " << Mass_hist_background -> Integral () << endl;

}
