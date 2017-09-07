#include "TTree.h"
double Max_value(double a, double b, double c)
{
	if (a>=b && a>=c) return a;
	if (b>=a && b>=c) return b;
	if (c>=a && c>=b) return c;
}


void AnalyzeInputs()
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

	TCut cut_pt = "pt>2";

	// open the file
   	TFile *f_MC = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_classifier_MC_1000037.root");	
   	TFile *f_minbias = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_classifier_minbias.root");	
   	TFile *f_data = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_classifier_data.root");	

	int palette[2]={632,418};
	gStyle->SetPalette(2,palette);	
	TTree *t_MC = (TTree*)f_MC->Get("pixelHits/treeAll");
	TTree *t_minbias = (TTree*)f_minbias->Get("pixelHits/treeAll");
	//TTree *t_data = (TTree*)f_data->Get("pixelHits/treeAll");
	
	if (f_MC->IsOpen() && f_minbias->IsOpen() && f_data->IsOpen()) printf("Files opened successfully\n");
	
	TCanvas * c1 = new TCanvas("c1", "Comp", 800, 600);
	c1->Print("Inputs.pdf[");//opens the file
		
	t_MC->SetLineColor(kGreen+3);
	t_minbias->SetLineColor(kRed+1);
	//t_data->SetLineColor(kBlue);
	t_MC->SetMarkerStyle(kFullCircle);
	t_minbias->SetMarkerStyle(kFullSquare);

	/* Plot of the charge_norm */
	TCut cut_charge = "hit1_charge_norm+hit2_charge_norm+hit3_charge_norm+hit4_charge_norm+hit5_charge_norm+hit6_charge_norm<300000 && hit1_charge_norm+hit2_charge_norm+hit3_charge_norm+hit4_charge_norm+hit5_charge_norm+hit6_charge_norm>0";

	t_minbias->Draw(TString("hit1_")+name1+TString("+hit2_")+name1+TString("+hit3_")+name1+TString("+hit4_")+name1+TString("+hit5_")+name1+TString("+hit6_")+name1,cut_charge&&cut_pt,"norm PLC PMC");
	t_MC->Draw(TString("hit1_")+name1+TString("+hit2_")+name1+TString("+hit3_")+name1+TString("+hit4_")+name1+TString("+hit5_")+name1+TString("+hit6_")+name1,cut_charge&&cut_pt,"norm same PLC PMC");
	//t_data->Draw(TString("hit1_")+name1+TString("+hit2_")+name1+TString("+hit3_")+name1+TString("+hit4_")+name1+TString("+hit5_")+name1+TString("+hit6_")+name1,cut_charge&&cut_pt,"norm same PLC PMC");
	TH2F *htemp = (TH2F*)gPad->GetPrimitive("htemp");	
	htemp->SetTitle(name1_off+"; "+name1+"; Occurences");
        gStyle->SetOptStat(0);
	gPad->Update();
	auto legend = new TLegend(0.6,0.75,0.9,0.9);
        legend->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend->AddEntry(t_MC,"Signal (MC)","l");
        legend->AddEntry(t_minbias,"Minimum Bias (MC)","l");
        //legend->AddEntry(t_data,"Data","l");
        legend->Draw();
	c1->Print("Inputs.pdf");
	
	/* Plot of the ratio_charge */
	TCut cut_ratio = "hit1_ratio_charge+hit2_ratio_charge+hit3_ratio_charge+hit4_ratio_charge+hit5_ratio_charge+hit6_ratio_charge<30 && hit1_ratio_charge+hit2_ratio_charge+hit3_ratio_charge+hit4_ratio_charge+hit5_ratio_charge+hit6_ratio_charge>0";

	t_minbias->Draw(TString("hit1_")+name2+TString("+hit2_")+name2+TString("+hit3_")+name2+TString("+hit4_")+name2+TString("+hit5_")+name2+TString("+hit6_")+name2,cut_ratio&&cut_pt,"norm PLC PMC");
	t_MC->Draw(TString("hit1_")+name2+TString("+hit2_")+name2+TString("+hit3_")+name2+TString("+hit4_")+name2+TString("+hit5_")+name2+TString("+hit6_")+name2,cut_ratio&&cut_pt,"norm same PLC PMC");
	//t_data->Draw(TString("hit1_")+name2+TString("+hit2_")+name2+TString("+hit3_")+name2+TString("+hit4_")+name2+TString("+hit5_")+name2+TString("+hit6_")+name2,cut_ratio&&cut_pt,"norm same PLC PMC");

        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle(name2_off+";"+name2+";Occurences");
        gPad->Update();

	legend->Draw();
	c1->Print("Inputs.pdf");

	/* Plot of the n_Pixel */
	TCut cut_npixel = "hit1_nPixel+hit2_nPixel+hit3_nPixel+hit4_nPixel+hit5_nPixel+hit6_nPixel<30";

	t_minbias->Draw(TString("hit1_")+name3+TString("+hit2_")+name3+TString("+hit3_")+name3+TString("+hit4_")+name3+TString("+hit5_")+name3+TString("+hit6_")+name3,cut_npixel&&cut_pt,"norm PLC PMC");
	t_MC->Draw(TString("hit1_")+name3+TString("+hit2_")+name3+TString("+hit3_")+name3+TString("+hit4_")+name3+TString("+hit5_")+name3+TString("+hit6_")+name3,cut_npixel&&cut_pt,"norm same PLC PMC");
	//t_data->Draw(TString("hit1_")+name3+TString("+hit2_")+name3+TString("+hit3_")+name3+TString("+hit4_")+name3+TString("+hit5_")+name3+TString("+hit6_")+name3,cut_npixel&&cut_pt,"norm same PLC PMC");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle(name3_off+";"+name3+";Occurences");
        gPad->Update();
	c1->Print("Inputs.pdf");
		
	/* Plot of the hit_sizeX */
	TCut cut_sizex = "hit1_hit_sizeX+hit2_hit_sizeX+hit3_hit_sizeX+hit4_hit_sizeX+hit5_hit_sizeX+hit6_hit_sizeX<15";

	t_minbias->Draw(TString("hit1_")+name4+TString("+hit2_")+name4+TString("+hit3_")+name4+TString("+hit4_")+name4+TString("+hit5_")+name4+TString("+hit6_")+name4,cut_sizex&&cut_pt,"norm PLC PMC");
	t_MC->Draw(TString("hit1_")+name4+TString("+hit2_")+name4+TString("+hit3_")+name4+TString("+hit4_")+name4+TString("+hit5_")+name4+TString("+hit6_")+name4,cut_sizex&&cut_pt,"norm same PLC PMC");
	//t_data->Draw(TString("hit1_")+name4+TString("+hit2_")+name4+TString("+hit3_")+name4+TString("+hit4_")+name4+TString("+hit5_")+name4+TString("+hit6_")+name4,cut_sizex&&cut_pt,"norm same PLC PMC");

        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle(name4_off+";"+name4+";Occurences");
        gPad->Update();

        legend->Draw();
	c1->Print("Inputs.pdf");
	
	/* Plot of the hit_sizeY */
	TCut cut_sizey = "hit1_hit_sizeY+hit2_hit_sizeY+hit3_hit_sizeY+hit4_hit_sizeY+hit5_hit_sizeY+hit6_hit_sizeY<25";

	TH2F *hframe_y = new TH2F("hframe_y",name5_off+";"+name5+";Occurences",40,0,25,40,0,0.1);
	hframe_y->GetYaxis()->SetRangeUser(0, 0.085);
	hframe_y->Draw();
	t_minbias->Draw(TString("hit1_")+name5+TString("+hit2_")+name5+TString("+hit3_")+name5+TString("+hit4_")+name5+TString("+hit5_")+name5+TString("+hit6_")+name5,cut_sizey&&cut_pt,"norm same PLC PMC");
	t_MC->Draw(TString("hit1_")+name5+TString("+hit2_")+name5+TString("+hit3_")+name5+TString("+hit4_")+name5+TString("+hit5_")+name5+TString("+hit6_")+name5,cut_sizey&&cut_pt,"norm same PLC PMC");
	//t_data->Draw(TString("hit1_")+name5+TString("+hit2_")+name5+TString("+hit3_")+name5+TString("+hit4_")+name5+TString("+hit5_")+name5+TString("+hit6_")+name5,cut_sizey&&cut_pt,"norm same PLC PMC");

        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle(name5_off+";"+name5+";Occurences");
        gPad->Update();

        legend->Draw();
	c1->Print("Inputs.pdf");

	/* Plot the number of hits */
	TH2F *hframe_n = new TH2F("hframe_n",name6_off+";"+name6+";Occurences",40,0,7,40,0,1);
	int nbin = 7;
	double min = 0.5;
	double max = 5.5;	
	t_MC->Draw(name6+TString(">>a(nbin,min,max"),cut_pt,"norm");
	t_minbias->Draw(name6+TString(">>b(nbin,min,max"),cut_pt,"norm same");
	//t_data->Draw(name6+TString(">>c(nbin,min,max"),cut_pt,"norm same");
        const TH1* a = (TH1*) gROOT->FindObject("a");
        const TH1* b = (TH1*) gROOT->FindObject("b");
//        const TH1* c = (TH1*) gROOT->FindObject("c");
        double max_a = a->GetMaximum();
        double max_b = b->GetMaximum();
//        double max_c = c->GetMaximum();
        double max_tot = std::max(max_a,max_b);


	hframe_n->GetYaxis()->SetRangeUser(0, 0.5);
	hframe_n->Draw();
	t_MC->Draw(name6,cut_pt,"norm same PLC PMC");
	t_minbias->Draw(name6,cut_pt,"norm same PLC PMC");
	//t_data->Draw(name6,cut_pt,"norm same PLC PMC");
	legend->Draw();
	
        c1->Print("Inputs.pdf");


	/* Close the pdf file */
	c1->Print("Inputs.pdf]");//closes the file
}
