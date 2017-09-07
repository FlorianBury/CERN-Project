#include "TTree.h"
#include "TFile.h"

void AnalyzeEfficiency(TString cut_user, TString length)
{
        // Input users
        std::cout<<"Cut applied : "<<cut_user<<"\n\n"<<std::endl;
        TCut cut_pt = "pt>20";
	TCut cut_invmass ="(e_far_invmass>70 && e_far_invmass<110) || (mu_far_invmass>70 && mu_far_invmass<110)";
        // open the file
        TFile *f_MC = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_300_"+length+".root");
        TFile *f_DY = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_ControlRegion_DY.root");
        TFile *f_TT = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_ControlRegion_TT_tune.root");
        TFile *f_SEL = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_SingleElectron.root");
        TFile *f_SMU = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_SingleMuon.root");

        TTree *t_MC = (TTree*)f_MC->Get("pixelHits/treeAll");
        TTree *t_DY = (TTree*)f_DY->Get("pixelHits/treeAll");
        TTree *t_TT = (TTree*)f_TT->Get("pixelHits/treeAll");
        TTree *t_SEL = (TTree*)f_SEL->Get("pixelHits/treeAll");
        TTree *t_SMU = (TTree*)f_SMU->Get("pixelHits/treeAll");

        if (f_MC->IsOpen() && f_TT->IsOpen() && f_DY->IsOpen() && f_SEL->IsOpen() && f_SMU->IsOpen()) printf("Files opened successfully\n");


	t_MC->Draw("pt>>total_MC(50,0,1000)",cut_pt);	
	t_DY->Draw("pt>>total_DY(50,0,1000)",cut_pt&&cut_invmass);	
	t_TT->Draw("pt>>total_TT(50,0,1000)",cut_pt&&cut_invmass);
	t_SEL->Draw("pt>>total_SEL(50,0,1000)",cut_pt&&cut_invmass);	
	t_SMU->Draw("pt>>total_SMU(50,0,1000)",cut_pt&&cut_invmass);	
	
	t_MC->Draw("pt>>passed_MC(50,0,1000)",cut_pt&&cut_user);	
	t_DY->Draw("pt>>passed_DY(50,0,1000)",cut_pt&&cut_invmass&&cut_user);	
	t_TT->Draw("pt>>passed_TT(50,0,1000)",cut_pt&&cut_invmass&&cut_user);
	t_SEL->Draw("pt>>passed_SEL(50,0,1000)",cut_pt&&cut_invmass&&cut_user);	
	t_SMU->Draw("pt>>passed_SMU(50,0,1000)",cut_pt&&cut_invmass&&cut_user);	

	TH1F* passed_MC = (TH1F*) gROOT->FindObject("passed_MC");
        TH1F* total_MC = (TH1F*) gROOT->FindObject("total_MC");
	TH1F* passed_DY = (TH1F*) gROOT->FindObject("passed_DY");
        TH1F* total_DY = (TH1F*) gROOT->FindObject("total_DY");
	TH1F* passed_TT = (TH1F*) gROOT->FindObject("passed_TT");
        TH1F* total_TT = (TH1F*) gROOT->FindObject("total_TT");
	TH1F* passed_SEL = (TH1F*) gROOT->FindObject("passed_SEL");
        TH1F* total_SEL = (TH1F*) gROOT->FindObject("total_SEL");
	TH1F* passed_SMU = (TH1F*) gROOT->FindObject("passed_SMU");
        TH1F* total_SMU = (TH1F*) gROOT->FindObject("total_SMU");
	
	TH1F* passed_data = new TH1F;
	TH1F* total_data = new TH1F;
	*passed_data = (*passed_SEL)+(*passed_SMU);
	*total_data = (*total_SEL)+(*total_SMU);
	int n_passed_MC = passed_MC->GetEntries(); 
	int n_passed_DY = passed_DY->GetEntries(); 
	int n_passed_TT = passed_TT->GetEntries(); 
	int n_passed_SEL = passed_SEL->GetEntries(); 
	int n_passed_SMU = passed_SMU->GetEntries(); 
	int n_passed_data = passed_data->GetEntries(); 
	int n_total_data = total_data->GetEntries(); 

	float eff_MC_avg = (passed_MC->GetEntries())/(total_MC->GetEntries());
	float eff_DY_avg = (passed_DY->GetEntries())/(total_DY->GetEntries());
	float eff_TT_avg = (passed_TT->GetEntries())/(total_TT->GetEntries());
	float eff_SEL_avg = (passed_SEL->GetEntries())/(total_SEL->GetEntries());
	float eff_SMU_avg = (passed_SMU->GetEntries())/(total_SMU->GetEntries());
	float eff_data_avg = (passed_data->GetEntries())/(total_data->GetEntries());

        TEfficiency *eff_MC=0;
        TEfficiency *eff_TT=0;
        TEfficiency *eff_DY=0;
        TEfficiency *eff_data=0;
        TEfficiency *eff_SEL=0;
        TEfficiency *eff_SMU=0;

	TCanvas * c1 = new TCanvas("c1", "Efficiency", 800, 600);

	if (TEfficiency::CheckConsistency(*passed_MC,*total_MC) && TEfficiency::CheckConsistency(*passed_DY,*total_DY) && TEfficiency::CheckConsistency(*passed_TT,*total_TT) && TEfficiency::CheckConsistency(*passed_data,*total_data) && TEfficiency::CheckConsistency(*passed_SEL,*total_SEL) && TEfficiency::CheckConsistency(*passed_SMU,*total_SMU))
	{
		eff_MC = new TEfficiency(*passed_MC,*total_MC);
		eff_DY = new TEfficiency(*passed_DY,*total_DY);
		eff_TT = new TEfficiency(*passed_TT,*total_TT);
		eff_SEL = new TEfficiency(*passed_SEL,*total_SEL);
		eff_SMU = new TEfficiency(*passed_SMU,*total_SMU);
		eff_data = new TEfficiency(*passed_data,*total_data);
	
                eff_MC->SetLineColor(kGreen+2);
                eff_DY->SetLineColor(kBlue+1);
                eff_TT->SetLineColor(kRed+1);
                eff_SEL->SetLineColor(kMagenta+2);
                eff_SMU->SetLineColor(kMagenta+2);
                eff_data->SetLineColor(kMagenta+2);

		eff_MC->SetTitle(cut_user);

		eff_MC->Draw("AP");
                eff_DY->Draw("P same");
                eff_TT->Draw("P same");
                eff_SEL->Draw("P same");
                eff_SMU->Draw("P same");
                eff_data->Draw("P same");
                gPad->SetLogy(0);
                gPad->Update();
		eff_MC->GetPaintedGraph()->GetYaxis()->SetRangeUser(0,0.2);
	
		auto legend = new TLegend(0.1,0.1,0.9,0.9);
                legend->SetHeader("Legend","C"); // option "C" allows to center the header
                legend->AddEntry(eff_MC,Form("MC (average = %f)\n -> Entries : %d",eff_MC_avg,n_passed_MC),"lep");
                legend->AddEntry(eff_DY,Form("DY (average = %f)\n -> Entries : %d",eff_DY_avg, n_passed_DY),"lep");
                legend->AddEntry(eff_TT,Form("TT (average = %f)\n -> Entries : %d",eff_TT_avg, n_passed_TT),"lep");
                legend->AddEntry(eff_SEL,Form("SEL (average = %f)\n -> Entries : %d",eff_SEL_avg, n_passed_SEL),"lep");
                legend->AddEntry(eff_SMU,Form("SMU (average = %f)\n -> Entries : %d",eff_SMU_avg, n_passed_SMU),"lep");
                legend->AddEntry(eff_data,Form("data (average = %f)\n -> Entries : %d",eff_data_avg, n_passed_data),"lep");
		legend->Draw();

		c1->Print("Effiency_CR/"+length+"cm_"+cut_user+"_invmass.png");
	}
}	
