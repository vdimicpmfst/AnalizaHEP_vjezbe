#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<TROOT.h>
#include<TChain.h>
#include<TFile.h>
#include<TApplication.h>
#include<TString.h>
#include<TH1F.h>
#include<TCanvas.h>

using namespace std;

class Generator{

	public:
	Generator ();
	void GeneratePDF();
	private:
	int i;
	TH1F *hist;
	float rng, f, rng2;
	TCanvas *canvas;
};
