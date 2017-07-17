#include "TFile.h"
#include "TTree.h"

void AnalyzeHits()
{
	// open the file
   	TFile *f_gen = TFile::Open("/home/florian/Documents/hits_gen (cut in pt).root");	
   	TFile *f_data = TFile::Open("/home/florian/Documents/hits_data (cut in pt).root");	
	
	TTree *t_gen = (TTree*)f_gen->Get("pixelHits/treeAll");
	TTree *t_data = (TTree*)f_data->Get("pixelHits/treeAll");
	
	if (f_gen->IsOpen() && f_data->IsOpen() ) printf("Files opened successfully\n");
	int nbin = 100;
	
	TCut cut="charge_norm>45000 && detector==1 && layer!=1 && nPixel<6 && hit_sizeX<4 && hit_sizeY<4";

	t_gen->SetLineColor(kRed);
	t_gen->Draw("charge_norm>>hsig(nbin,60000,200000)","mass>100"&&cut,"norm");
	

	TH1 * hsig = (TH1*) gROOT->FindObject("hsig");
	int n_HSCP = hsig->GetEntries();	
	cout <<"number of entries of HSCP (signal) = "<<n_HSCP<<endl;



	t_gen->SetLineColor(kBlue);
	t_gen->Draw("charge_norm>>gsig(nbin,60000,200000)","mass<100"&&cut,"norm same");


	TH1 * gsig = (TH1*) gROOT->FindObject("gsig");
	int n_min = gsig->GetEntries();	
	cout <<"number of entries of minimum bias (background) = "<<n_min<<endl;




	t_data->SetLineColor(kGreen);
	t_data->Draw("charge_norm",cut,"norm same");
}
