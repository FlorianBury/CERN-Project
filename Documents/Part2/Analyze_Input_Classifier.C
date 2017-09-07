#include "TFile.h"
#include "TTree.h"

void Analyze_Input_Classifier(TString name, TString off_name, TString pdg_num, TString cut_pt)
{
	// Input users
	TString path = "/home/florian/Documents/Part2/MC_vs_Minbias/";
  	TString output_file = path+name+"_"+pdg_num+"_"+cut_pt+".pdf";
	
	// open the file
   	TFile *f_MC = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_classifier_MC_"+pdg_num+".root");	
   	TFile *f_minbias = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_classifier_minbias.root");	
	
	TTree *t_MC = (TTree*)f_MC->Get("pixelHits/treeAll");
	TTree *t_minbias = (TTree*)f_minbias->Get("pixelHits/treeAll");
	
	if (f_MC->IsOpen() && f_minbias->IsOpen() ) printf("Files opened successfully\n");
	
	TCanvas * c1 = new TCanvas("c1", "Comp", 800, 600);
	c1->Print(output_file+"[");//opens the file
		
	t_MC->SetLineColor(kRed);
	t_minbias->SetLineColor(kBlue);

	auto legend = new TLegend(0.1,0.82,0.3,0.9);
        legend->SetHeader("Legend","C"); // option "C" allows to center the header                                                
        legend->AddEntry(t_MC,"Signal","l");
        legend->AddEntry(t_minbias,"Background","l");

	TH2F *htemp = new TH2F;	

	/* Plots for each layer */
	for (int i=1 ; i<=6 ; i++) //goes through the hits
	{
		TString number = std::to_string(i);
		TCut cut=Form("hit%i_layer !=0",i);
		
		t_MC->Draw(TString("hit")+number+TString("_")+name,cut&&cut_pt,"norm");

		t_minbias->Draw(TString("hit")+number+TString("_")+name,cut&&cut_pt,"norm same");
	        htemp = (TH2F*)gPad->GetPrimitive("htemp");
	        htemp->SetTitle(Form(off_name+" on hit number %i"+";"+off_name+"; Occurences",i));
        	gPad->Update();
		
		gStyle->SetOptStat(0);
                legend->Draw();
		c1->Print(output_file);
	}
	
	/* All the layers combined */

	t_MC->Draw(TString("hit1_")+name+TString("+hit2_")+name+TString("+hit3_")+name+TString("+hit4_")+name+TString("+hit5_")+name+TString("+hit6_")+name,cut_pt,"norm");

	t_minbias->Draw(TString("hit1_")+name+TString("+hit2_")+name+TString("+hit3_")+name+TString("+hit4_")+name+TString("+hit5_")+name+TString("+hit6_")+name,cut_pt,"norm same");

	htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Sum of "+off_name+" over all hits"+";"+off_name+"; Occurences");
        gPad->Update();
	gStyle->SetOptStat(0);
        legend->Draw();
	c1->Print(output_file);

	/* Average over all the layers hit */
	
	TCut cut_num = "n_hit !=0";

	t_MC->Draw("("+TString("hit1_")+name+TString("+hit2_")+name+TString("+hit3_")+name+TString("+hit4_")+name+TString("+hit5_")+name+TString("+hit6_")+name+")/n_hit",cut_pt&&cut_num,"norm");
	t_minbias->Draw("("+TString("hit1_")+name+TString("+hit2_")+name+TString("+hit3_")+name+TString("+hit4_")+name+TString("+hit5_")+name+TString("+hit6_")+name+")/n_hit",cut_pt&&cut_num,"norm same");

 	htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Average of "+off_name+" over all hits"+";"+off_name+"; Occurences");
        gPad->Update();
 
	gStyle->SetOptStat(0);
	legend->Draw();
	c1->Print(output_file);

	/* Plots of the number of hits */
	t_minbias->Draw("n_hit",cut_pt,"norm");
	t_MC->Draw("n_hit",cut_pt,"norm same");
        
	htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Number of hits of the track;;Occurences");
        gPad->Update();
	legend->Draw();
	gStyle->SetOptStat(0);
	c1->Print(output_file);


	/* Closes the file */
	c1->Print(output_file+"]");//closes the file
}
