#include "TTree.h"

void StackPlot(TString name, TString name_title,TString name_axis, TString unit, TString binning, TString cut_plot)
{
	// Input users
	TCut cut_user = "fabs(IP_tran)<0.02 && fabs(IP_long)<0.02 && isolation_out<1 && fabs(IP_tran/IP_tran_error)<4 && fabs(IP_long/IP_long_error)<4 && n_layer_pixel>=3";
	float L = 200;
	float sigma_DY = 3*1921.8;
	float sigma_ttbar = 831.76;
	int n_DY = 309685;
	int n_ttbar = 100000;
	
	// open the file
   	TFile *f_MC = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_300_30_pileup.root");	
   	TFile *f_ttbar = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_ControlRegion_TT_tune.root");	
   	TFile *f_DY = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_ControlRegion_DY.root");	
   	TFile *f_SEL = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_SingleElectron.root");	
   	TFile *f_SMU = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_SingleMuon.root");	
	
	TTree *t_MC = (TTree*)f_MC->Get("pixelHits/treeAll");
	TTree *t_ttbar = (TTree*)f_ttbar->Get("pixelHits/treeAll");
	TTree *t_DY = (TTree*)f_DY->Get("pixelHits/treeAll");
	TTree *t_SEL = (TTree*)f_SEL->Get("pixelHits/treeAll");
	TTree *t_SMU = (TTree*)f_SMU->Get("pixelHits/treeAll");
	
	if (f_MC->IsOpen() && f_ttbar->IsOpen() && f_DY->IsOpen() && f_SEL->IsOpen() && f_SMU->IsOpen()) printf("Files opened successfully\n");
	
		
	t_DY->SetLineColor(kBlue);
	t_DY->SetFillColor(kAzure-4);
	t_ttbar->SetLineColor(kRed+2);
	t_ttbar->SetFillColor(kRed-6);
	t_MC->SetLineColor(kGreen+3);
	t_SEL->SetLineColor(kBlack);
	t_SMU->SetLineColor(kBlack);
	
	t_MC->SetLineWidth(3);
	t_DY->SetLineWidth(1);
	t_ttbar->SetLineWidth(1);
	// Get number of entries
	t_MC->Draw(name+">>hist_MC"+binning,cut_user&&cut_plot,"");
	t_ttbar->Draw(name+">>hist_ttbar"+binning,cut_user&&cut_invmass&&cut_plot,"");
	t_DY->Draw(name+">>hist_DY"+binning,cut_user&&cut_invmass&&cut_plot,"");
	t_SEL->Draw(name+">>hist_SEL"+binning,cut_user&&cut_invmass&&cut_plot,"");
	t_SMU->Draw(name+">>hist_SMU"+binning,cut_user&&cut_invmass&&cut_plot,"");

	TH1F* hist_MC = (TH1F*) gROOT->FindObject("hist_MC");
	TH1F* hist_ttbar = (TH1F*) gROOT->FindObject("hist_ttbar");
	TH1F* hist_DY = (TH1F*) gROOT->FindObject("hist_DY");
	TH1F* hist_SEL = (TH1F*) gROOT->FindObject("hist_SEL");
	TH1F* hist_SMU = (TH1F*) gROOT->FindObject("hist_SMU");
	TH1F* hist_data = new TH1F;
	*hist_data = (*hist_SEL)+(*hist_SMU);

	hist_MC->Sumw2();
	hist_ttbar->Sumw2();
	hist_DY->Sumw2();
	hist_data->Sumw2();

	double weight_DY = L*sigma_DY/n_DY;
	double weight_ttbar = L*sigma_ttbar/n_ttbar;
	
	// Scale the histograms
	hist_DY->Scale(weight_DY);
	hist_ttbar->Scale(weight_ttbar);
	double tot = hist_ttbar->Integral()+hist_DY->Integral();
	double scale = hist_data->Integral()/tot;
	hist_DY->Scale(scale);
        hist_ttbar->Scale(scale);
	hist_MC->Scale(hist_data->Integral()/hist_MC->Integral());
	// Plots the stacked histogram 
	THStack *a = new THStack("a","");
	
	a->Add(hist_DY,"hist");
	a->Add(hist_ttbar,"hist");

	// Plots 
	TCanvas * c1 = new TCanvas("c1", "Stack", 900, 600);
	auto legend = new TLegend(0.6,0.75,0.9,0.9);
        legend->SetHeader("Legend","C"); // option "C" allows to center the hea\
der                                                                            \
                                                                                
        legend->AddEntry(t_MC,"Signal (MC)","lep");
        legend->AddEntry(t_ttbar,"Background TTbar","l");
        legend->AddEntry(t_DY,"Background DY","l");
        legend->AddEntry(hist_data,"Data","lep");

	hist_data->SetMarkerStyle(21);

	a->Draw();
	hist_data->Draw("same E");
	hist_MC->Draw("same E"); 
        a->SetTitle(name_title+";"+name_axis+unit+"; Occurences");
	legend->Draw();
        gPad->Update();

	c1->Print("StackPlot/StackPlot_"+name+".png");

}
