#include "TTree.h"

void CompareSelection(TString filename, TCut cut_selection)
{
	// Input users
	TString name1 = "charge_norm";
	TString name1_off = "Normalized charge";
	TString name2 = "ratio_charge";
	TString name2_off = "Ratio of the charge";
	TString name3 = "nPixel";
	TString name3_off = "Number of Pixel hits";
	TString name4 = "hit_sizeX";
	TString name4_off = "Size of the cluster in X direction";
	TString name5 = "hit_sizeY";
	TString name5_off = "Size of the cluster in Y direction";
	TString name6 = "n_hit";
	TString name6_off = "Number of hits in the tracker";

	TCut cut_pt = "pt>20";
	
	std::cout<<"\nSelection cut applied : "<<cut_selection<<std::endl;

	// open the file
   	TFile *f = TFile::Open("/home/florian/Documents/Part2/Root_files/"+filename);	

	TTree *t = (TTree*)f->Get("pixelHits/treeAll");
	
	if (f->IsOpen()) printf("File opened successfully\n");
	
	TCanvas * c1 = new TCanvas("c1", "Comp", 800, 600);
	c1->Print("Compare_Selection/CompareSelection.pdf[");//opens the file

	/* Plot of the charge_norm */
	TCut cut_charge = "hit1_charge_norm+hit2_charge_norm+hit3_charge_norm+hit4_charge_norm+hit5_charge_norm+hit6_charge_norm<300000 && hit1_charge_norm+hit2_charge_norm+hit3_charge_norm+hit4_charge_norm+hit5_charge_norm+hit6_charge_norm>0";
	TString bin_charge = "(50,0,300000)";
	t->Draw(TString("hit1_")+name1+TString("+hit2_")+name1+TString("+hit3_")+name1+TString("+hit4_")+name1+TString("+hit5_")+name1+TString("+hit6_")+name1+">>charge_1"+bin_charge,cut_charge&&cut_pt,"norm");
	t->Draw(TString("hit1_")+name1+TString("+hit2_")+name1+TString("+hit3_")+name1+TString("+hit4_")+name1+TString("+hit5_")+name1+TString("+hit6_")+name1+">>charge_2"+bin_charge,cut_charge&&cut_pt&&cut_selection,"norm");
	TH1F* charge_1 = (TH1F*) gROOT->FindObject("charge_1");
	TH1F* charge_2 = (TH1F*) gROOT->FindObject("charge_2");

	charge_1->SetLineColor(kBlue+2);
	charge_1->SetLineWidth(2);
	charge_1->SetMarkerColor(kBlue+2);
	charge_1->SetMarkerStyle(21);
	charge_2->SetLineColor(kRed+2);
	charge_2->SetLineWidth(2);
	charge_2->SetMarkerColor(kRed+2);
	charge_2->SetMarkerStyle(20);

	charge_1->SetTitle("Normalised charge; Charge; Occurences");
	charge_1->Draw();	
	charge_2->Draw("same");	
	
	auto legend_charge = new TLegend(0.6,0.75,0.9,0.9);
        legend_charge->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_charge->AddEntry(charge_1,"Before selection","l");
        legend_charge->AddEntry(charge_2,"After selection","l");
        legend_charge->Draw();
	gStyle->SetOptStat(0);
	c1->Print("Compare_Selection/CompareSelection.pdf");
	c1->Print("Compare_Selection/CompareSelection_charge.png");

	/* Plot of the ratio_charge */
	TCut cut_ratio = "hit1_ratio_charge+hit2_ratio_charge+hit3_ratio_charge+hit4_ratio_charge+hit5_ratio_charge+hit6_ratio_charge<30 && hit1_ratio_charge+hit2_ratio_charge+hit3_ratio_charge+hit4_ratio_charge+hit5_ratio_charge+hit6_ratio_charge>0";
	TString bin_ratio = "(20,0,30)";

	t->Draw(TString("hit1_")+name2+TString("+hit2_")+name2+TString("+hit3_")+name2+TString("+hit4_")+name2+TString("+hit5_")+name2+TString("+hit6_")+name2+">>ratio_1"+bin_ratio,cut_ratio&&cut_pt,"norm");
	t->Draw(TString("hit1_")+name2+TString("+hit2_")+name2+TString("+hit3_")+name2+TString("+hit4_")+name2+TString("+hit5_")+name2+TString("+hit6_")+name2+">>ratio_2"+bin_ratio,cut_ratio&&cut_pt&&cut_selection,"norm");
	TH1F* ratio_1 = (TH1F*) gROOT->FindObject("ratio_1");
	TH1F* ratio_2 = (TH1F*) gROOT->FindObject("ratio_2");
	ratio_1->SetLineColor(kBlue+2);
        ratio_1->SetLineWidth(2);
        ratio_1->SetMarkerColor(kBlue+2);
        ratio_1->SetMarkerStyle(21);
        ratio_2->SetLineColor(kRed+2);
        ratio_2->SetLineWidth(2);
        ratio_2->SetMarkerColor(kRed+2);
        ratio_2->SetMarkerStyle(20);
	
	ratio_1->SetTitle("Ratio of the charge; Ratio; Occurences");
        ratio_1->Draw();
        ratio_2->Draw("same");

        auto legend_ratio = new TLegend(0.6,0.75,0.9,0.9);
        legend_ratio->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_ratio->AddEntry(ratio_1,"Before selection","l");
        legend_ratio->AddEntry(ratio_2,"After selection","l");
        legend_ratio->Draw();

	c1->Print("Compare_Selection/CompareSelection.pdf");
	/* Plot of the n_Pixel */
	TString bin_nPixel = "(35,-0.5,34.5)";
	t->Draw(TString("hit1_")+name3+TString("+hit2_")+name3+TString("+hit3_")+name3+TString("+hit4_")+name3+TString("+hit5_")+name3+TString("+hit6_")+name3+">>nPixel_1"+bin_nPixel,cut_pt,"norm");
	t->Draw(TString("hit1_")+name3+TString("+hit2_")+name3+TString("+hit3_")+name3+TString("+hit4_")+name3+TString("+hit5_")+name3+TString("+hit6_")+name3+">>nPixel_2"+bin_nPixel,cut_pt &&cut_selection,"norm");
       	TH1F* nPixel_1 = (TH1F*) gROOT->FindObject("nPixel_1");
	TH1F* nPixel_2 = (TH1F*) gROOT->FindObject("nPixel_2");

	nPixel_1->SetLineColor(kBlue+2);
	nPixel_1->SetLineWidth(2);
	nPixel_1->SetMarkerColor(kBlue+2);
	nPixel_1->SetMarkerStyle(21);
	nPixel_2->SetLineColor(kRed+2);
	nPixel_2->SetLineWidth(2);
	nPixel_2->SetMarkerColor(kRed+2);
	nPixel_2->SetMarkerStyle(20);

	nPixel_2->SetTitle("Number of pixels hit; N; Occurences");
	nPixel_2->Draw();	
	nPixel_1->Draw("same");	

	auto legend_nPixel = new TLegend(0.6,0.75,0.9,0.9);
        legend_nPixel->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_nPixel->AddEntry(nPixel_1,"Before selection","l");
        legend_nPixel->AddEntry(nPixel_2,"After selection","l");
        legend_nPixel->Draw();
	c1->Print("Compare_Selection/CompareSelection.pdf");

	/* Plot of the hit_sizeX */
	TString bin_sizeX = "(16,-0.5,15.5)";
	t->Draw(TString("hit1_")+name4+TString("+hit2_")+name4+TString("+hit3_")+name4+TString("+hit4_")+name4+TString("+hit5_")+name4+TString("+hit6_")+name4+">>sizeX_1"+bin_sizeX,cut_pt,"norm");
	t->Draw(TString("hit1_")+name4+TString("+hit2_")+name4+TString("+hit3_")+name4+TString("+hit4_")+name4+TString("+hit5_")+name4+TString("+hit6_")+name4+">>sizeX_2"+bin_sizeX,cut_pt&&cut_selection,"norm");
	TH1F* sizeX_1 = (TH1F*) gROOT->FindObject("sizeX_1");
        TH1F* sizeX_2 = (TH1F*) gROOT->FindObject("sizeX_2");

        sizeX_1->SetLineColor(kBlue+2);
        sizeX_1->SetLineWidth(2);
        sizeX_1->SetMarkerColor(kBlue+2);
        sizeX_1->SetMarkerStyle(21);
        sizeX_2->SetLineColor(kRed+2);
        sizeX_2->SetLineWidth(2);
        sizeX_2->SetMarkerColor(kRed+2);
        sizeX_2->SetMarkerStyle(20);

        sizeX_2->SetTitle("Size of the cluster in X direction; N; Occurences");
        sizeX_2->Draw();       
        sizeX_1->Draw("same"); 

        auto legend_sizeX = new TLegend(0.1,0.75,0.4,0.9);
        legend_sizeX->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_sizeX->AddEntry(sizeX_1,"Before selection","l");
        legend_sizeX->AddEntry(sizeX_2,"After selection","l");
        legend_sizeX->Draw();
	c1->Print("Compare_Selection/CompareSelection.pdf");
	
	/* Plot of the hit_sizeY */
        TString bin_sizeY = "(35,-0.5,34.5)";

	t->Draw(TString("hit1_")+name5+TString("+hit2_")+name5+TString("+hit3_")+name5+TString("+hit4_")+name5+TString("+hit5_")+name5+TString("+hit6_")+name5+">>sizeY_1"+bin_sizeY,cut_pt,"norm");
	t->Draw(TString("hit1_")+name5+TString("+hit2_")+name5+TString("+hit3_")+name5+TString("+hit4_")+name5+TString("+hit5_")+name5+TString("+hit6_")+name5+">>sizeY_2"+bin_sizeY,cut_pt&&cut_selection,"norm");
	TH1F* sizeY_1 = (TH1F*) gROOT->FindObject("sizeY_1");
        TH1F* sizeY_2 = (TH1F*) gROOT->FindObject("sizeY_2");

        sizeY_1->SetLineColor(kBlue+2);
        sizeY_1->SetLineWidth(2);
        sizeY_1->SetMarkerColor(kBlue+2);
        sizeY_1->SetMarkerStyle(21);
        sizeY_2->SetLineColor(kRed+2);
        sizeY_2->SetLineWidth(2);
        sizeY_2->SetMarkerColor(kRed+2);
        sizeY_2->SetMarkerStyle(20);

        sizeY_2->SetTitle("Size of the cluster in Y direction; N; Occurences");
        sizeY_2->Draw(); 
        sizeY_1->Draw("same"); 

        auto legend_sizeY = new TLegend(0.6,0.75,0.9,0.9);
        legend_sizeY->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_sizeY->AddEntry(sizeY_1,"Before selection","l");
        legend_sizeY->AddEntry(sizeY_2,"After selection","l");
        legend_sizeY->Draw();

	c1->Print("Compare_Selection/CompareSelection.pdf");

	/* Plot the number of hits */
	TString bin_n = "(28,2.5,30.5)";
	TString cut_n = "n_hit!=0";
	t->Draw(name6+">>n_1"+bin_n,cut_pt&&cut_n,"norm");
	t->Draw(name6+">>n_2"+bin_n,cut_pt&&cut_n&&cut_selection,"norm");
	TH1F* n_1 = (TH1F*) gROOT->FindObject("n_1");
        TH1F* n_2 = (TH1F*) gROOT->FindObject("n_2");

        n_1->SetLineColor(kBlue+2);
        n_1->SetLineWidth(2);
        n_1->SetMarkerColor(kBlue+2);
        n_1->SetMarkerStyle(21);
        n_2->SetLineColor(kRed+2);
        n_2->SetLineWidth(2);
        n_2->SetMarkerColor(kRed+2);
        n_2->SetMarkerStyle(20);

        n_2->SetTitle("Number of hits; N; Occurences");
        n_2->Draw();
        n_1->Draw("same");

        auto legend_n = new TLegend(0.6,0.75,0.9,0.9);
        legend_n->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_n->AddEntry(n_1,"Before selection","l");
        legend_n->AddEntry(n_2,"After selection","l");
        legend_n->Draw();
	
        c1->Print("Compare_Selection/CompareSelection.pdf");

	/* Close the pdf file */
	c1->Print("Compare_Selection/CompareSelection.pdf]");//closes the file
}
