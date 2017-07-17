#include "TFile.h"
#include "TTree.h"

void AnalyzeTrack()
{
	// open the file
   	TFile *f = TFile::Open("/home/florian/Documents/Decay_Mass/track_decay_200_3.root");	
	
	TTree *t = (TTree*)f->Get("pixelHits/treeAll");
	
	if (f->IsOpen()) printf("Files opened successfully\n");

	TCut cut="std::abs(gen_eta)<1.3";

	int nbin =100;
	int min =0;
	int max =1000;

	TString name ="decay_rho";


	t->SetLineColor(kGreen);
	t->Draw(name+TString(">>passed(nbin,min,max)"),"selected==1"&&cut);
	
        t->SetLineColor(kRed);
        t->Draw(name+TString(">>not_passed(nbin,min,max)"),"selected==0"&&cut,"same");
	
	t->SetLineColor(kBlue);
        t->Draw(name+TString(">>total(nbin,min,max)"),cut,"same");
	

	const TH1* passed = (TH1*) gROOT->FindObject("passed");
	const TH1* total = (TH1*) gROOT->FindObject("total");

	
	TEfficiency *eff=0;
	if (TEfficiency::CheckConsistency(*passed,*total))
	{
		eff = new TEfficiency(*passed,*total);
		eff->SetTitle("Efficiency in "+name+";"+name+";Efficiency");
		eff->Draw("AP");
	}
}
