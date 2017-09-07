#include "TFile.h"
#include "TTree.h"

void AnalyzeEfficiencyLifetime()
{
	// Input choices	
	TString mass = "400";
        TString name ="gen_pt";
	TString name_off = "Pt";
	TString unit =" [GeV]";
	float axis_max = 1200;
	TCut cut="std::abs(gen_eta)<1.3";

        // open the file
        TFile *f_3 = TFile::Open("/home/florian/Documents/Part1/Decay_Mass/track_decay_"+mass+"_3.root");
	TFile *f_10 = TFile::Open("/home/florian/Documents/Part1/Decay_Mass/track_decay_"+mass+"_10.root");
	TFile *f_30 = TFile::Open("/home/florian/Documents/Part1/Decay_Mass/track_decay_"+mass+"_30.root");

        TTree *t_3 = (TTree*)f_3->Get("pixelHits/treeAll");
        TTree *t_10 = (TTree*)f_10->Get("pixelHits/treeAll");
        TTree *t_30 = (TTree*)f_30->Get("pixelHits/treeAll");

        if (f_3->IsOpen() && f_10->IsOpen() &&f_30->IsOpen()) printf("Files opened successfully\n");

        t_3->Draw(name+TString(">>passed_3(30,0,1200)"),"selected==1"&&cut);
        t_3->Draw(name+TString(">>not_passed_3(30,0,1200)"),"selected==0"&&cut,"same");
        t_3->Draw(name+TString(">>total_3(30,0,1200)"),cut,"same");
        const TH1* passed_3 = (TH1*) gROOT->FindObject("passed_3");
        const TH1* total_3 = (TH1*) gROOT->FindObject("total_3");
	float eff_3_avg = (passed_3->GetEntries())/(total_3->GetEntries());

        t_10->Draw(name+TString(">>passed_10(40,0,1200)"),"selected==1"&&cut);
        t_10->Draw(name+TString(">>not_passed_10(40,0,1200)"),"selected==0"&&cut,"same");
        t_10->Draw(name+TString(">>total_10(40,0,1200)"),cut,"same");
        const TH1* passed_10 = (TH1*) gROOT->FindObject("passed_10");
        const TH1* total_10 = (TH1*) gROOT->FindObject("total_10");
	float eff_10_avg = (passed_10->GetEntries())/(total_10->GetEntries());

        t_30->Draw(name+TString(">>passed_30(60,0,1200)"),"selected==1"&&cut);
        t_30->Draw(name+TString(">>not_passed_30(60,0,1200)"),"selected==0"&&cut,"same");
        t_30->Draw(name+TString(">>total_30(60,0,1200)"),cut,"same");
        const TH1* passed_30 = (TH1*) gROOT->FindObject("passed_30");
        const TH1* total_30 = (TH1*) gROOT->FindObject("total_30");
	float eff_30_avg = (passed_30->GetEntries())/(total_30->GetEntries());

        TEfficiency *eff_3=0;
        TEfficiency *eff_10=0;
        TEfficiency *eff_30=0;
        if (TEfficiency::CheckConsistency(*passed_3,*total_3) && TEfficiency::CheckConsistency(*passed_10,*total_10) && TEfficiency::CheckConsistency(*passed_30,*total_30))
        {
		TCanvas * c2 = new TCanvas("c2", "Efficiency", 800, 600);

		eff_3 = new TEfficiency(*passed_3,*total_3);
                eff_10 = new TEfficiency(*passed_10,*total_10);
                eff_30 = new TEfficiency(*passed_30,*total_30);
                eff_3->SetTitle("Efficiency in "+name_off+" (Mass = "+mass+" GeV);"+name_off+unit+";Efficiency");

		eff_30->SetLineColor(kRed+1);
		eff_30->SetLineWidth(2);
		eff_30->SetMarkerStyle(20);
		eff_30->SetMarkerColor(kRed+1);

		eff_3->SetLineColor(kGreen+2);
		eff_3->SetLineWidth(2);
		eff_3->SetMarkerStyle(21);
		eff_3->SetMarkerColor(kGreen+2);

		eff_10->SetLineColor(kBlue+1);
		eff_10->SetLineWidth(2);
		eff_10->SetMarkerStyle(22);
		eff_10->SetMarkerColor(kBlue+1);

		eff_3->Draw();
                eff_10->Draw("same");
                eff_30->Draw("same");
		eff_3->SetConfidenceLevel(0.01);
		eff_30->SetConfidenceLevel(0.01);
		eff_30->SetConfidenceLevel(0.01);
		gPad->SetLogy(0);
		gPad->Update();
		eff_3->GetPaintedGraph()->GetXaxis()->SetLimits(0,axis_max);
		eff_3->GetPaintedGraph()->GetYaxis()->SetRangeUser(0,1);

		auto legend = new TLegend(0.12,0.7,0.55,0.9);
   		legend->SetHeader("Legend","C"); // option "C" allows to center the header
   		legend->AddEntry(eff_3,Form("Lifetime = 3cm (average = %f)",eff_3_avg),"lep");
   		legend->AddEntry(eff_10,Form("Lifetime = 10cm (average = %f)",eff_10_avg),"lep");
   		legend->AddEntry(eff_30,Form("Lifetime = 30cm (average = %f)",eff_30_avg),"lep");
   		legend->Draw();
		
		c2->Print(name+"_"+mass+".png");
	 }
}

