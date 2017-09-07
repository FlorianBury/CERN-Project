#include "TTree.h"

void CompareSigBackAOD()
{
	// Input users
	TCut cut_user = ""; // -> Signal
	TCut cut_user_back = "";//"jet_sum_pt>200 && n_jet>3 && jet_pt>100";//"fabs(IP_tran)<0.02 && fabs(IP_long)<0.02 && isolation_out<1 && fabs(IP_tran/IP_tran_error)<4 && fabs(IP_long/IP_long_error)<4 && n_layer_pixel>=3";
	std::cout<<"Cut applied on Signal : "<<cut_user<<std::endl;
	std::cout<<"Cut applied on Background : "<<cut_user_back<<"\n"<<std::endl;
	TCut cut_pt = "pt>20";
	// open the file
   	TFile *f_MC = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_300_30_pileup.root");	
   	TFile *f_ttbar = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_ControlRegion_TT_tune.root");	
   	TFile *f_QCD = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_QCD.root");	
   	TFile *f_DY = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_AOD_ControlRegion_DY.root");	
   	TFile *f_SEL = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_SingleElectron.root");	
   	TFile *f_SMU = TFile::Open("/home/florian/Documents/Part2/Root_files/hits_SingleMuon.root");	
	
	TTree *t_MC = (TTree*)f_MC->Get("pixelHits/treeAll");
	TTree *t_ttbar = (TTree*)f_ttbar->Get("pixelHits/treeAll");
	TTree *t_QCD = (TTree*)f_QCD->Get("pixelHits/treeAll");
	TTree *t_DY = (TTree*)f_DY->Get("pixelHits/treeAll");
	TTree *t_SEL = (TTree*)f_SEL->Get("pixelHits/treeAll");
	TTree *t_SMU = (TTree*)f_SMU->Get("pixelHits/treeAll");
	
	if (f_MC->IsOpen() && f_ttbar->IsOpen() && f_QCD->IsOpen() && f_DY->IsOpen() && f_SEL->IsOpen() && f_SMU->IsOpen()) printf("Files opened successfully\n");
	
	TCanvas * c1 = new TCanvas("c1", "Comp", 800, 600);
	c1->Print("CompareAOD.pdf[");//opens the file
		
        t_MC->SetLineColor(kBlack);
        t_ttbar->SetLineColor(kRed+2);
        t_DY->SetLineColor(kGreen+2);
        t_SEL->SetLineColor(kOrange-3);
        t_SMU->SetLineColor(kBlue+2);

        t_MC->SetLineWidth(3);
        t_ttbar->SetLineWidth(3);
        t_DY->SetLineWidth(3);
        t_SEL->SetLineWidth(3);
        t_SMU->SetLineWidth(3);
	
	TH2F *htemp = new TH2F;
 
	/* Plot of the Pt */
	TH2F *hframe = new TH2F("hframe","Transverse momentum; Pt; Occurences",50,0,100000,100,0,0.3);
	hframe->Draw();
	t_MC->Draw("pt>>hist_MC(100,0,100000)","pt<1000000"&&cut_user&&cut_pt,"norm same");
	t_ttbar->Draw("pt>>hist_ttbar(100,0,100000)","pt<1000000"&&cut_user_back&&cut_pt,"norm same");
	//t_QCD->Draw("pt>>hist_QCD(100,0,100000)","pt<1000000"&&cut_user_back&&cut_pt,"norm same");
	t_DY->Draw("pt>>hist_DY(100,0,100000)","pt<1000000"&&cut_user_back&&cut_pt,"norm same");
	t_SEL->Draw("pt>>hist_SEL(100,0,100000)","pt<1000000"&&cut_user_back&&cut_pt,"norm same");
	t_SMU->Draw("pt>>hist_SMU(100,0,100000)","pt<1000000"&&cut_user_back&&cut_pt,"norm same");
	const TH1* hist_MC = (TH1*) gROOT->FindObject("hist_MC");
        const TH1* hist_ttbar = (TH1*) gROOT->FindObject("hist_ttbar");
        //const TH1* hist_QCD = (TH1*) gROOT->FindObject("hist_QCD");
        const TH1* hist_DY = (TH1*) gROOT->FindObject("hist_DY");
        const TH1* hist_SEL = (TH1*) gROOT->FindObject("hist_SEL");
        const TH1* hist_SMU = (TH1*) gROOT->FindObject("hist_SMU");
	int entries_MC = hist_MC->GetEntries();
	int entries_ttbar = hist_ttbar->GetEntries();
	//int entries_QCD = hist_QCD->GetEntries();
	int entries_DY = hist_DY->GetEntries();
	int entries_SEL = hist_SEL->GetEntries();
	int entries_SMU = hist_SMU->GetEntries();

	auto legend_right = new TLegend(0.6,0.75,0.9,0.9);
        legend_right->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_right->AddEntry(t_MC,Form("  Signal (entries = %d)",entries_MC),"l");
        legend_right->AddEntry(t_ttbar,Form("  TTbar (entries = %d)",entries_ttbar),"l");
        //legend_right->AddEntry(t_QCD,Form("  QCD (entries = %d)",entries_QCD),"l");
        legend_right->AddEntry(t_DY,Form("  DY (entries = %d)",entries_DY),"l");
        legend_right->AddEntry(t_SEL,Form("  SEL (entries = %d)",entries_SEL),"l");
        legend_right->AddEntry(t_SMU,Form("  SMU (entries = %d)",entries_SMU),"l");

	auto legend_left = new TLegend(0.1,0.75,0.4,0.9);
        legend_left->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_left->AddEntry(t_MC,Form("  Signal (entries = %d)",entries_MC),"l");
        legend_left->AddEntry(t_ttbar,Form("  TTbar (entries = %d)",entries_ttbar),"l");
        //legend_left->AddEntry(t_QCD,Form("  QCD (entries = %d)",entries_QCD),"l");
        legend_left->AddEntry(t_DY,Form("  DY (entries = %d)",entries_DY),"l");
        legend_left->AddEntry(t_SEL,Form("  SEL (entries = %d)",entries_SEL),"l");
        legend_left->AddEntry(t_SMU,Form("  SMU (entries = %d)",entries_SMU),"l");
	
	legend_right->Draw();
	gStyle->SetOptStat(0);
	c1->Print("CompareAOD.pdf");
	/* Plot of the Pt log*/
	t_DY->Draw("pt","pt<1000000"&&cut_user_back&&cut_pt,"");
	t_MC->Draw("pt","pt<1000000"&&cut_user&&cut_pt,"same");
	t_ttbar->Draw("pt","pt<1000000"&&cut_user_back&&cut_pt,"same");
	//t_QCD->Draw("pt","pt<1000000"&&cut_user_back&&cut_pt,"same");
	t_SEL->Draw("pt","pt<1000000"&&cut_user_back&&cut_pt,"same");
	t_SMU->Draw("pt","pt<1000000"&&cut_user_back&&cut_pt,"same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
	htemp->SetTitle("Transverse momentum (log scale); Pt; Occurences");
        gPad->SetLogy(1);
	gPad->Update();
	legend_right->Draw();
	c1->Print("CompareAOD.pdf");
	/* Plot Pt_error/Pt */
        t_MC->Draw("pt_error/pt","pt_error/pt<4"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("pt_error/pt","pt_error/pt<4"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("pt_error/pt","pt_error/pt<4"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("pt_error/pt","pt_error/pt<4"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("pt_error/pt","pt_error/pt<4"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("pt_error/pt","pt_error/pt<4"&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Relative Pt error; Pt_error/Pt; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

	
	/* Plot dxy */
        t_DY->Draw("max(min(IP_tran,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm");
        t_MC->Draw("max(min(IP_tran,0.01),-0.01)",""&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("max(min(IP_tran,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("max(min(IP_tran,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("max(min(IP_tran,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("max(min(IP_tran,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Transverse Impact Parameter; IP transverse; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");
	
	/* Plot dz */
        t_MC->Draw("max(min(IP_long,0.01),-0.01)",""&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("max(min(IP_long,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("max(min(IP_long,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("max(min(IP_long,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("max(min(IP_long,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("max(min(IP_long,0.01),-0.01)",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Longitudinal Impact Parameter; IP longitudinal; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot dxy/dxy_error */
        t_MC->Draw("IP_tran/IP_tran_error","fabs(IP_tran/IP_tran_error)<5"&&cut_user&&cut_pt,"norm");
        //t_QCD->Draw("IP_tran/IP_tran_error","fabs(IP_tran/IP_tran_error)<5"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("IP_tran/IP_tran_error","fabs(IP_tran/IP_tran_error)<5"&&cut_user_back&&cut_pt,"norm same");
        t_ttbar->Draw("IP_tran/IP_tran_error","fabs(IP_tran/IP_tran_error)<5"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("IP_tran/IP_tran_error","fabs(IP_tran/IP_tran_error)<5"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("IP_tran/IP_tran_error","fabs(IP_tran/IP_tran_error)<5"&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Transverse Impact Parameter divided by the error; IP_tran/IP_tran_error; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot dz/dz_error */
	t_DY->Draw("IP_long/IP_long_error","fabs(IP_long/IP_long_error)<5"&&cut_user_back&&cut_pt,"norm");
	t_ttbar->Draw("IP_long/IP_long_error","fabs(IP_long/IP_long_error)<5"&&cut_user_back&&cut_pt,"norm same");
	//t_QCD->Draw("IP_long/IP_long_error","fabs(IP_long/IP_long_error)<5"&&cut_user_back&&cut_pt,"norm same");
	t_MC->Draw("IP_long/IP_long_error","fabs(IP_long/IP_long_error)<5"&&cut_user&&cut_pt,"norm same");
	t_SEL->Draw("IP_long/IP_long_error","fabs(IP_long/IP_long_error)<5"&&cut_user_back&&cut_pt,"norm same");
	t_SMU->Draw("IP_long/IP_long_error","fabs(IP_long/IP_long_error)<5"&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Longitudinal Impact Parameter divided by the error; IP_long/IP_long_error; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot Isolation_int (=Iso/pt actually) */
        t_DY->Draw("isolation_int","isolation_int<2"&&cut_user_back&&cut_pt,"norm");
        t_MC->Draw("isolation_int","isolation_int<2"&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("isolation_int","isolation_int<2"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("isolation_int","isolation_int<2"&&cut_user_back&&cut_pt,"same");
        t_SEL->Draw("isolation_int","isolation_int<2"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("isolation_int","isolation_int<2"&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Relative isolation (of the track); Isolation; Occurences");
	gPad->SetLogy(1);        
	gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");
        c1->Print("Compare_iso_int.png");
	
	/* Plot Isolation_out (=Iso/pt actually) */
        t_MC->Draw("isolation_out","isolation_out<5"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("isolation_out","isolation_out<5"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("isolation_out","isolation_out<5"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("isolation_out","isolation_out<5"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("isolation_out","isolation_out<5"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("isolation_out","isolation_out<5"&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Relative isolation (inside the cone without the main track); Isolation; Occurences");
	gPad->SetLogy(1);        
	gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");
        c1->Print("Compare_iso_out.png");

	/* Plot Isolation*pt (=Iso actually) */
        t_MC->Draw("isolation_out*pt",""&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("isolation_out*pt",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("isolation_out*pt",""&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("isolation_out*pt",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("isolation_out*pt",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("isolation_out*pt",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Absolute isolation; Isolation; Occurences");
	gPad->SetLogy(1);        
	gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot n_hit */
        t_MC->Draw("n_hit",""&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("n_hit",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("n_hit",""&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("n_hit",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("n_hit",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("n_hit",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Number of hits; N; Occurences");
	gPad->SetLogy(0);        
	gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot n_hit_pixel */
        t_DY->Draw("n_hit_pixel",""&&cut_user_back&&cut_pt,"norm");
	//t_QCD->Draw("n_hit_pixel",""&&cut_user_back&&cut_pt,"norm same");
        t_MC->Draw("n_hit_pixel",""&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("n_hit_pixel",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("n_hit_pixel",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("n_hit_pixel",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Number of hits in pixel detector; N; Occurences");
	gPad->SetLogy(0);        
	gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");
        c1->Print("Compare_n_pixel.png");

	/* Plot n_hit_strip */
        t_MC->Draw("n_hit_strip",""&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("n_hit_strip",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("n_hit_strip",""&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("n_hit_strip",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("n_hit_strip",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("n_hit_strip",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Number of hits in strip detector; N; Occurences");
	gPad->SetLogy(0);        
	gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot n_layer_pixel */
        t_DY->Draw("n_layer_pixel",""&&cut_user_back&&cut_pt,"norm");
        //t_QCD->Draw("n_layer_pixel",""&&cut_user_back&&cut_pt,"norm same");
        t_MC->Draw("n_layer_pixel",""&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("n_layer_pixel",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("n_layer_pixel",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("n_layer_pixel",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Number of layers hit in pixel detector; N; Occurences");
	gPad->SetLogy(0);        
	gPad->Update();
        legend_left->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot n_layer_strip */
        t_DY->Draw("n_layer_strip",""&&cut_user_back&&cut_pt,"norm");
        //t_QCD->Draw("n_layer_strip",""&&cut_user_back&&cut_pt,"norm same");
        t_MC->Draw("n_layer_strip",""&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("n_layer_strip",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("n_layer_strip",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("n_layer_strip",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Number of layers hit in strip detector; N; Occurences");
	gPad->SetLogy(0);        
	gPad->Update();
        legend_left->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot n_miss_outer */
        t_MC->Draw("n_miss_outer",""&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("n_miss_outer",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("n_miss_outer",""&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("n_miss_outer",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("n_miss_outer",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("n_miss_outer",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Number of hits missed after the track; N; Occurences");
	gPad->SetLogy(0);        
	gPad->Update();
        legend_left->Draw();
        c1->Print("CompareAOD.pdf");
        c1->Print("Compare_outer.png");

	/* Plot n_miss_inner */
        t_MC->Draw("n_miss_inner",""&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("n_miss_inner",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("n_miss_inner",""&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("n_miss_inner",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("n_miss_inner",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("n_miss_inner",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Number of hits missed before the track; N; Occurences");
	gPad->SetLogy(0);        
	gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

	/* Plot quality */
        t_MC->Draw("quality",""&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("quality",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("quality",""&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("quality",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("quality",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("quality",""&&cut_user_back&&cut_pt,"norm same");
	htemp = (TH2F*)gPad->GetPrimitive("htemp");	
        htemp->SetTitle("Quality of the selection;; Occurences");
	gPad->SetLogy(0);        
	gPad->Update();
        legend_left->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot met_pt */
        t_MC->Draw("met_pt","met_pt<300"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("met_pt","met_pt<300"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("met_pt","met_pt<300"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("met_pt","met_pt<300"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("met_pt","met_pt<300"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("met_pt","met_pt<300"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Pt of the MET;Pt; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot met_phi */
        t_MC->Draw("met_phi",""&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("met_phi",""&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("met_phi",""&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("met_phi",""&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("met_phi",""&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("met_phi",""&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Azimutal angle of the MET;Phi; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot e_near_pt */
        t_ttbar->Draw("e_near_pt>>e_near_ttbar(100,0,5000)","e_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_MC->Draw("e_near_pt>>e_near_MC(100,0,5000)","e_near_pt>0"&&cut_user&&cut_pt,"same");
        //t_QCD->Draw("e_near_pt>>e_near_QCD(100,0,5000)","e_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_DY->Draw("e_near_pt>>e_near_DY(100,0,5000)","e_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_SEL->Draw("e_near_pt>>e_near_SEL(100,0,5000)","e_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_SMU->Draw("e_near_pt>>e_near_SMU(100,0,5000)","e_near_pt>0"&&cut_user_back&&cut_pt,"");
        const TH1* e_near_ttbar = (TH1*) gROOT->FindObject("e_near_ttbar");
        const TH1* e_near_MC = (TH1*) gROOT->FindObject("e_near_MC");
        //const TH1* e_near_QCD = (TH1*) gROOT->FindObject("e_near_QCD");
        const TH1* e_near_DY = (TH1*) gROOT->FindObject("e_near_DY");
        const TH1* e_near_SEL = (TH1*) gROOT->FindObject("e_near_SEL");
        const TH1* e_near_SMU = (TH1*) gROOT->FindObject("e_near_SMU");
	int n_e_near_MC = e_near_MC->GetEntries(); 
	int n_e_near_ttbar = e_near_ttbar->GetEntries(); 
	//int n_e_near_QCD = e_near_QCD->GetEntries(); 
	int n_e_near_DY = e_near_DY->GetEntries(); 
	int n_e_near_SEL = e_near_SEL->GetEntries(); 
	int n_e_near_SMU = e_near_SMU->GetEntries(); 
	std::cout<<"\tNumber of  near electron in Signal MC: "<<n_e_near_MC<<"\tFraction: "<<double(n_e_near_MC)/double(entries_MC)*100<<"%"<<std::endl; 	
	std::cout<<"\tNumber of  near electron in Background ttbar: "<<n_e_near_ttbar<<"\tFraction: "<<double(n_e_near_ttbar)/double(entries_ttbar)*100<<"%"<<std::endl; 	
	//std::cout<<"\tNumber of  near electron in Background QCD: "<<n_e_near_QCD<<"\tFraction: "<<double(n_e_near_QCD)/double(entries_QCD)*100<<"%"<<std::endl; 	
	std::cout<<"\tNumber of  near electron in Background DY: "<<n_e_near_DY<<"\tFraction: "<<double(n_e_near_DY)/double(entries_DY)*100<<"%"<<std::endl; 	
	std::cout<<"\tNumber of  near electron in Background SEL: "<<n_e_near_SEL<<"\tFraction: "<<double(n_e_near_SEL)/double(entries_SEL)*100<<"%"<<std::endl; 	
	std::cout<<"\tNumber of  near electron in Background SMU: "<<n_e_near_SMU<<"\tFraction: "<<double(n_e_near_SMU)/double(entries_SMU)*100<<"%"<<std::endl; 	
	auto legend_e_near = new TLegend(0.55,0.75,0.9,0.9);
        legend_e_near->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_e_near->AddEntry(t_MC,Form("Signal (fraction of near electron = %f%%)",double(n_e_near_MC)/double(entries_MC)*100),"l");
        legend_e_near->AddEntry(t_ttbar,Form("TTbar (fraction of near electron = %f%%)",double(n_e_near_ttbar)/double(entries_ttbar)*100),"l");
        //legend_e_near->AddEntry(t_QCD,Form("QCD (fraction of near electron = %f%%)",double(n_e_near_QCD)/double(entries_QCD)*100),"l");
        legend_e_near->AddEntry(t_DY,Form("DY (fraction of near electron = %f%%)",double(n_e_near_DY)/double(entries_DY)*100),"l");
        legend_e_near->AddEntry(t_SEL,Form("SEL (fraction of near electron = %f%%)",double(n_e_near_SEL)/double(entries_SEL)*100),"l");
        legend_e_near->AddEntry(t_SMU,Form("SMU (fraction of near electron = %f%%)",double(n_e_near_SMU)/double(entries_SMU)*100),"l");


        t_DY->Draw("e_near_pt","e_near_pt>0 && e_near_pt<300"&&cut_user_back&&cut_pt,"");
        t_ttbar->Draw("e_near_pt","e_near_pt>0 && e_near_pt<300"&&cut_user_back&&cut_pt,"same");
        t_MC->Draw("e_near_pt","e_near_pt>0 && e_near_pt<300"&&cut_user&&cut_pt,"same");
        //t_QCD->Draw("e_near_pt","e_near_pt>0 && e_near_pt<300"&&cut_user_back&&cut_pt,"same");
        t_SEL->Draw("e_near_pt","e_near_pt>0 && e_near_pt<300"&&cut_user_back&&cut_pt,"same");
        t_SMU->Draw("e_near_pt","e_near_pt>0 && e_near_pt<300"&&cut_user_back&&cut_pt,"same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Pt of the nearest electron; Pt; Occurences");
        gPad->SetLogy(1);
        gPad->Update();
        legend_e_near->Draw();
        c1->Print("CompareAOD.pdf");


        /* Plot e_far_pt */
        t_ttbar->Draw("e_far_pt>>e_far_ttbar(100,0,5000)","e_far_pt>0"&&cut_user_back&&cut_pt,"");
        t_MC->Draw("e_far_pt>>e_far_MC(100,0,5000)","e_far_pt>0"&&cut_user&&cut_pt,"");
        //t_QCD->Draw("e_far_pt>>e_far_QCD(100,0,5000)","e_far_pt>0"&&cut_user_back&&cut_pt,"");
        t_DY->Draw("e_far_pt>>e_far_DY(100,0,5000)","e_far_pt>0"&&cut_user_back&&cut_pt,"");
        t_SEL->Draw("e_far_pt>>e_far_SEL(100,0,5000)","e_far_pt>0"&&cut_user_back&&cut_pt,"");
        t_SMU->Draw("e_far_pt>>e_far_SMU(100,0,5000)","e_far_pt>0"&&cut_user_back&&cut_pt,"");
        const TH1* e_far_ttbar = (TH1*) gROOT->FindObject("e_far_ttbar");
        const TH1* e_far_MC = (TH1*) gROOT->FindObject("e_far_MC");
        //const TH1* e_far_QCD = (TH1*) gROOT->FindObject("e_far_QCD");
        const TH1* e_far_DY = (TH1*) gROOT->FindObject("e_far_DY");
        const TH1* e_far_SEL = (TH1*) gROOT->FindObject("e_far_SEL");
        const TH1* e_far_SMU = (TH1*) gROOT->FindObject("e_far_SMU");
	int n_e_far_MC = e_far_MC->GetEntries(); 
	int n_e_far_ttbar = e_far_ttbar->GetEntries(); 
	//int n_e_far_QCD = e_far_QCD->GetEntries(); 
	int n_e_far_DY = e_far_DY->GetEntries(); 
	int n_e_far_SEL = e_far_SEL->GetEntries(); 
	int n_e_far_SMU = e_far_SMU->GetEntries(); 
	std::cout<<"\tNumber of  far electron in Signal MC: "<<n_e_far_MC<<"\tFraction: "<<double(n_e_far_MC)/double(entries_MC)*100<<"%"<<std::endl; 	
	std::cout<<"\tNumber of  far electron in Background ttbar: "<<n_e_far_ttbar<<"\tFraction: "<<double(n_e_far_ttbar)/double(entries_ttbar)*100<<"%"<<std::endl; 	
	//std::cout<<"\tNumber of  far electron in Background QCD: "<<n_e_far_QCD<<"\tFraction: "<<double(n_e_far_QCD)/double(entries_QCD)*100<<"%"<<std::endl; 	
	std::cout<<"\tNumber of  far electron in Background DY: "<<n_e_far_DY<<"\tFraction: "<<double(n_e_far_DY)/double(entries_DY)*100<<"%"<<std::endl; 	
	std::cout<<"\tNumber of  far electron in Background SEL: "<<n_e_far_SEL<<"\tFraction: "<<double(n_e_far_SEL)/double(entries_SEL)*100<<"%"<<std::endl; 	
	std::cout<<"\tNumber of  far electron in Background SMU: "<<n_e_far_SMU<<"\tFraction: "<<double(n_e_far_SMU)/double(entries_SMU)*100<<"%"<<std::endl; 	
	auto legend_e_far = new TLegend(0.5,0.7,0.9,0.9);
        legend_e_far->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_e_far->AddEntry(t_MC,Form("Signal (fraction of far electron = %f%%)",double(n_e_far_MC)/double(entries_MC)*100),"l");
        legend_e_far->AddEntry(t_ttbar,Form("TTbar (fraction of far electron = %f%%)",double(n_e_far_ttbar)/double(entries_ttbar)*100),"l");
        //legend_e_far->AddEntry(t_QCD,Form("QCD (fraction of far electron = %f%%)",double(n_e_far_QCD)/double(entries_QCD)*100),"l");
        legend_e_far->AddEntry(t_DY,Form("DY (fraction of far electron = %f%%)",double(n_e_far_DY)/double(entries_DY)*100),"l");
        legend_e_far->AddEntry(t_SEL,Form("SEL (fraction of far electron = %f%%)",double(n_e_far_SEL)/double(entries_SEL)*100),"l");
        legend_e_far->AddEntry(t_SMU,Form("SMU (fraction of far electron = %f%%)",double(n_e_far_SMU)/double(entries_SMU)*100),"l");


        t_MC->Draw("e_far_pt","e_far_pt>0 && e_far_pt<100"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("e_far_pt","e_far_pt>0 && e_far_pt<100"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("e_far_pt","e_far_pt>0 && e_far_pt<100"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("e_far_pt","e_far_pt>0 && e_far_pt<100"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("e_far_pt","e_far_pt>0 && e_far_pt<100"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("e_far_pt","e_far_pt>0 && e_far_pt<100"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Pt of the most energetic electron; Pt; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_e_far->Draw();
        c1->Print("CompareAOD.pdf");
        c1->Print("Compare_e_pt.png");

        /* Plot e_near_deltaR */
        t_DY->Draw("e_near_deltaR","e_near_deltaR<0.2"&&cut_user&&cut_pt,"");
        t_MC->Draw("e_near_deltaR","e_near_deltaR<0.2"&&cut_user_back&&cut_pt,"same");
        t_ttbar->Draw("e_near_deltaR","e_near_deltaR<0.2"&&cut_user_back&&cut_pt,"same");
        //t_QCD->Draw("e_near_deltaR","e_near_deltaR<0.2"&&cut_user_back&&cut_pt,"same");
        t_SEL->Draw("e_near_deltaR","e_near_deltaR<0.2"&&cut_user_back&&cut_pt,"same");
        t_SMU->Draw("e_near_deltaR","e_near_deltaR<0.2"&&cut_user_back&&cut_pt,"same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("DeltaR of the nearest electron; DeltaR; Occurences");
        gPad->SetLogy(1);
        gPad->Update();
        legend_e_near->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot e_far_deltaR */
        t_DY->Draw("e_far_deltaR","e_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm");
        t_MC->Draw("e_far_deltaR","e_far_deltaR>0.4"&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("e_far_deltaR","e_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("e_far_deltaR","e_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("e_far_deltaR","e_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("e_far_deltaR","e_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("DeltaR of the most energetic far electron; DeltaR; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_e_far->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot e_near_tight */
       	t_MC->Draw("e_near_tight","e_near_pt>0 && e_near_tight>=0"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("e_near_tight","e_near_pt>0 && e_near_tight>=0"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("e_near_tight","e_near_pt>0 && e_near_tight>=0"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("e_near_tight","e_near_pt>0 && e_near_tight>=0"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("e_near_tight","e_near_pt>0 && e_near_tight>=0"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("e_near_tight","e_near_pt>0 && e_near_tight>=0"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Tight selection bit for the nearest electron; Selection; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_e_near->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot e_far_tight */
 /*       t_MC->Draw("e_far_tight>>e_MC(2,-0.5,1.5)","e_far_pt>0"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("e_far_tight>>e_ttbar(2,-0.5,1.5)","e_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("e_far_tight","e_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("e_far_tight>>e_DY(2,-0.5,1.5)","e_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("e_far_tight>>e_SEL(2,-0.5,1.5)","e_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("e_far_tight>>e_SMU(2,-0.5,1.5)","e_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        TH1F* e_MC = (TH1F*) gROOT->FindObject("e_MC");
        TH1F* e_ttbar = (TH1F*) gROOT->FindObject("e_ttbar");
        TH1F* e_DY = (TH1F*) gROOT->FindObject("e_DY");
        TH1F* e_SEL = (TH1F*) gROOT->FindObject("e_SEL");
        TH1F* e_SMU = (TH1F*) gROOT->FindObject("e_SMU");
	e_MC->SetLineColor(kBlack);
        e_ttbar->SetLineColor(kRed+2);
        e_DY->SetLineColor(kGreen+2);
        e_SEL->SetLineColor(kOrange-3);
        e_SMU->SetLineColor(kBlue+2);
	e_MC->SetLineWidth(3);
	e_ttbar->SetLineWidth(3);
	e_DY->SetLineWidth(3);
	e_SEL->SetLineWidth(3);
	e_SMU->SetLineWidth(3);

	e_MC->SetTitle("Tight selection bit for the most energetic electron; Selection; Occurences");	
	e_MC->GetYaxis()->SetRangeUser(0,1.4);
	e_MC->Draw();
	e_ttbar->Draw("same");
	e_DY->Draw("same");
	e_SEL->Draw("same");
	e_SMU->Draw("same");
	
	auto legend_e_tight = new TLegend(0.10,0.70,0.9,0.9);
        legend_e_tight->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_e_tight->AddEntry(e_MC,Form("Signal  (fraction of far electron = %f%%)",double(n_e_far_MC)/double(entries_MC)*100),"l");
        legend_e_tight->AddEntry(e_ttbar,Form("TTbar  (fraction of far electron = %f%%)",double(n_e_far_ttbar)/double(entries_ttbar)*100),"l");
        //legend_e_tight->AddEntry(e_QCD,Form("QCD\t(fraction of far electron = %f%%)",double(n_e_far_QCD)/double(entries_QCD)*100),"l");
        legend_e_tight->AddEntry(e_DY,Form("DY       (fraction of far electron = %f%%)",double(n_e_far_DY)/double(entries_DY)*100),"l");
        legend_e_tight->AddEntry(e_SEL,Form("SEL    (fraction of far electron = %f%%)",double(n_e_far_SEL)/double(entries_SEL)*100),"l");
        legend_e_tight->AddEntry(e_SMU,Form("SMU   (fraction of far electron = %f%%)",double(n_e_far_SMU)/double(entries_SMU)*100),"l");
	legend_e_tight->Draw();
	
        c1->Print("Compare_e_tight.png");
        c1->Print("CompareAOD.pdf");*/
        /* Plot e_far_invmass */
        t_DY->Draw("e_far_invmass","e_far_invmass<200 && e_far_invmass>0"&&cut_user_back&&cut_pt,"norm");
        t_MC->Draw("e_far_invmass","e_far_invmass<200 && e_far_invmass>0"&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("e_far_invmass","e_far_invmass<200 && e_far_invmass>0"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("e_far_invmass","e_far_invmass<200 && e_far_invmass>0"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("e_far_invmass","e_far_invmass<200 && e_far_invmass>0"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("e_far_invmass","e_far_invmass<200 && e_far_invmass>0"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Invariant mass of the far electron and the track; Invmass; Occurences");
        gPad->SetLogy(1);
        //gPad->Update();
        legend_e_far->Draw();
        c1->Print("Compare_e_invmass.png");
        c1->Print("CompareAOD.pdf");

        /* Plot mu_near_pt */
        t_ttbar->Draw("mu_near_pt>>mu_near_ttbar(100,0,5000)","mu_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_MC->Draw("mu_near_pt>>mu_near_MC(100,0,5000)","mu_near_pt>0"&&cut_user&&cut_pt,"");
        //t_QCD->Draw("mu_near_pt>>mu_near_QCD(100,0,5000)","mu_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_DY->Draw("mu_near_pt>>mu_near_DY(100,0,5000)","mu_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_SEL->Draw("mu_near_pt>>mu_near_SEL(100,0,5000)","mu_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_SMU->Draw("mu_near_pt>>mu_near_SMU(100,0,5000)","mu_near_pt>0"&&cut_user_back&&cut_pt,"");
        const TH1* mu_near_ttbar = (TH1*) gROOT->FindObject("mu_near_ttbar");
        const TH1* mu_near_MC = (TH1*) gROOT->FindObject("mu_near_MC");
        //const TH1* mu_near_QCD = (TH1*) gROOT->FindObject("mu_near_QCD");
        const TH1* mu_near_DY = (TH1*) gROOT->FindObject("mu_near_DY");
        const TH1* mu_near_SEL = (TH1*) gROOT->FindObject("mu_near_SEL");
        const TH1* mu_near_SMU = (TH1*) gROOT->FindObject("mu_near_SMU");
        int n_mu_near_MC = mu_near_MC->GetEntries();
        int n_mu_near_ttbar = mu_near_ttbar->GetEntries();
        //int n_mu_near_QCD = mu_near_QCD->GetEntries();
        int n_mu_near_DY = mu_near_DY->GetEntries();
        int n_mu_near_SEL = mu_near_SEL->GetEntries();
        int n_mu_near_SMU = mu_near_SMU->GetEntries();
        std::cout<<"\tNumber of  near muon in Signal MC: "<<n_mu_near_MC<<"\tFraction: "<<double(n_mu_near_MC)/double(entries_MC)*100<<"%"<<std::endl;
        std::cout<<"\tNumber of  near muon in Background ttbar: "<<n_mu_near_ttbar<<"\tFraction: "<<double(n_mu_near_ttbar)/double(entries_ttbar)*100<<"%"<<std::endl;
        //std::cout<<"\tNumber of  near muon in Background QCD: "<<n_mu_near_QCD<<"\tFraction: "<<double(n_mu_near_QCD)/double(entries_QCD)*100<<"%"<<std::endl;
        std::cout<<"\tNumber of  near muon in Background DY: "<<n_mu_near_DY<<"\tFraction: "<<double(n_mu_near_DY)/double(entries_DY)*100<<"%"<<std::endl;
        std::cout<<"\tNumber of  near muon in Background SEL: "<<n_mu_near_SEL<<"\tFraction: "<<double(n_mu_near_SEL)/double(entries_SEL)*100<<"%"<<std::endl;
        std::cout<<"\tNumber of  near muon in Background SMU: "<<n_mu_near_SMU<<"\tFraction: "<<double(n_mu_near_SMU)/double(entries_SMU)*100<<"%"<<std::endl;
        auto legend_mu_near = new TLegend(0.55,0.75,0.9,0.9);
        legend_mu_near->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_mu_near->AddEntry(t_MC,Form("Signal (fraction of near muon = %f%%)",double(n_mu_near_MC)/double(entries_MC)*100),"l");
        legend_mu_near->AddEntry(t_ttbar,Form("TTbar (fraction of near muon = %f%%)",double(n_mu_near_ttbar)/double(entries_ttbar)*100),"l");
        //legend_mu_near->AddEntry(t_QCD,Form("QCD (fraction of near muon = %f%%)",double(n_mu_near_QCD)/double(entries_QCD)*100),"l");
        legend_mu_near->AddEntry(t_DY,Form("DY (fraction of near muon = %f%%)",double(n_mu_near_DY)/double(entries_DY)*100),"l");
        legend_mu_near->AddEntry(t_SEL,Form("SEL (fraction of near muon = %f%%)",double(n_mu_near_SEL)/double(entries_SEL)*100),"l");
        legend_mu_near->AddEntry(t_SMU,Form("SMU (fraction of near muon = %f%%)",double(n_mu_near_SMU)/double(entries_SMU)*100),"l");

        t_DY->Draw("mu_near_pt","mu_near_pt>0"&&cut_user_back&&cut_pt,"");
        t_ttbar->Draw("mu_near_pt","mu_near_pt>0"&&cut_user_back&&cut_pt,"same");
        t_MC->Draw("mu_near_pt","mu_near_pt>0"&&cut_user&&cut_pt,"same");
        //t_QCD->Draw("mu_near_pt","mu_near_pt>0"&&cut_user_back&&cut_pt,"same");
        t_SEL->Draw("mu_near_pt","mu_near_pt>0"&&cut_user_back&&cut_pt,"same");
        t_SMU->Draw("mu_near_pt","mu_near_pt>0"&&cut_user_back&&cut_pt,"same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Pt of the nearest muon; Pt; Occurences");
        gPad->SetLogy(1);
        gPad->Update();
        legend_mu_near->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot mu_far_pt */
        t_ttbar->Draw("mu_far_pt>>mu_far_ttbar(100,0,5000)","mu_far_pt>0"&&cut_user_back&&cut_pt,"");
        t_MC->Draw("mu_far_pt>>mu_far_MC(100,0,5000)","mu_far_pt>0"&&cut_user&&cut_pt,"");
        //t_QCD->Draw("mu_far_pt>>mu_far_QCD(100,0,5000)","mu_far_pt>0"&&cut_user_back&&cut_pt,"");
        t_DY->Draw("mu_far_pt>>mu_far_DY(100,0,5000)","mu_far_pt>0"&&cut_user_back&&cut_pt,"");
        t_SEL->Draw("mu_far_pt>>mu_far_SEL(100,0,5000)","mu_far_pt>0"&&cut_user_back&&cut_pt,"");
        t_SMU->Draw("mu_far_pt>>mu_far_SMU(100,0,5000)","mu_far_pt>0"&&cut_user_back&&cut_pt,"");
        const TH1* mu_far_ttbar = (TH1*) gROOT->FindObject("mu_far_ttbar");
        const TH1* mu_far_MC = (TH1*) gROOT->FindObject("mu_far_MC");
        //const TH1* mu_far_QCD = (TH1*) gROOT->FindObject("mu_far_QCD");
        const TH1* mu_far_DY = (TH1*) gROOT->FindObject("mu_far_DY");
        const TH1* mu_far_SEL = (TH1*) gROOT->FindObject("mu_far_SEL");
        const TH1* mu_far_SMU = (TH1*) gROOT->FindObject("mu_far_SMU");
        int n_mu_far_MC = mu_far_MC->GetEntries();
        int n_mu_far_ttbar = mu_far_ttbar->GetEntries();
        //int n_mu_far_QCD = mu_far_QCD->GetEntries();
        int n_mu_far_DY = mu_far_DY->GetEntries();
        int n_mu_far_SEL = mu_far_SEL->GetEntries();
        int n_mu_far_SMU = mu_far_SMU->GetEntries();
        std::cout<<"\tNumber of  far muon in Signal MC: "<<n_mu_far_MC<<"\tFraction: "<<double(n_mu_far_MC)/double(entries_MC)*100<<"%"<<std::endl;
        std::cout<<"\tNumber of  far muon in Background ttbar: "<<n_mu_far_ttbar<<"\tFraction: "<<double(n_mu_far_ttbar)/double(entries_ttbar)*100<<"%"<<std::endl;
        //std::cout<<"\tNumber of  far muon in Background QCD: "<<n_mu_far_QCD<<"\tFraction: "<<double(n_mu_far_QCD)/double(entries_QCD)*100<<"%"<<std::endl;
        std::cout<<"\tNumber of  far muon in Background DY: "<<n_mu_far_DY<<"\tFraction: "<<double(n_mu_far_DY)/double(entries_DY)*100<<"%"<<std::endl;
        std::cout<<"\tNumber of  far muon in Background SEL: "<<n_mu_far_SEL<<"\tFraction: "<<double(n_mu_far_SEL)/double(entries_SEL)*100<<"%"<<std::endl;
        std::cout<<"\tNumber of  far muon in Background SMU: "<<n_mu_far_SMU<<"\tFraction: "<<double(n_mu_far_SMU)/double(entries_SMU)*100<<"%"<<std::endl;
        auto legend_mu_far = new TLegend(0.55,0.75,0.9,0.9);
        legend_mu_far->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_mu_far->AddEntry(t_MC,Form("Signal (fraction of far muon = %f%%)",double(n_mu_far_MC)/double(entries_MC)*100),"l");
        //legend_mu_far->AddEntry(t_ttbar,Form("TTbar (fraction of far muon = %f%%)",double(n_mu_far_ttbar)/double(entries_ttbar)*100),"l");
        //legend_mu_far->AddEntry(t_QCD,Form("QCD (fraction of far muon = %f%%)",double(n_mu_far_QCD)/double(entries_QCD)*100),"l");
        legend_mu_far->AddEntry(t_DY,Form("DY (fraction of far muon = %f%%)",double(n_mu_far_DY)/double(entries_DY)*100),"l");
        legend_mu_far->AddEntry(t_SEL,Form("SEL (fraction of far muon = %f%%)",double(n_mu_far_SEL)/double(entries_SEL)*100),"l");
        legend_mu_far->AddEntry(t_SMU,Form("SMU (fraction of far muon = %f%%)",double(n_mu_far_SMU)/double(entries_SMU)*100),"l");

        t_MC->Draw("mu_far_pt","mu_far_pt>0 && mu_far_pt<140"&&cut_user&&cut_pt,"norm");
        t_DY->Draw("mu_far_pt","mu_far_pt>0 && mu_far_pt<140"&&cut_user_back&&cut_pt,"norm same");
        t_ttbar->Draw("mu_far_pt","mu_far_pt>0 && mu_far_pt<140"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("mu_far_pt","mu_far_pt>0 && mu_far_pt<140"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("mu_far_pt","mu_far_pt>0 && mu_far_pt<140"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("mu_far_pt","mu_far_pt>0 && mu_far_pt<140"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Pt of the most energetic muon; Pt; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_mu_far->Draw();
        c1->Print("CompareAOD.pdf");
        c1->Print("Compare_mu_pt.png");

        /* Plot mu_near_deltaR */

        t_MC->Draw("mu_near_deltaR","mu_near_deltaR<0.4"&&cut_user&&cut_pt,"");
        t_ttbar->Draw("mu_near_deltaR","mu_near_deltaR<0.4"&&cut_user_back&&cut_pt,"same");
        //t_QCD->Draw("mu_near_deltaR","mu_near_deltaR<0.4"&&cut_user_back&&cut_pt,"same");
        t_DY->Draw("mu_near_deltaR","mu_near_deltaR<0.4"&&cut_user_back&&cut_pt,"same");
        t_SEL->Draw("mu_near_deltaR","mu_near_deltaR<0.4"&&cut_user_back&&cut_pt,"same");
        t_SMU->Draw("mu_near_deltaR","mu_near_deltaR<0.4"&&cut_user_back&&cut_pt,"same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("DeltaR of the nearest muon; DeltaR; Occurences");
        gPad->SetLogy(1);
        gPad->Update();
        legend_mu_near->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot mu_far_deltaR */
        t_DY->Draw("mu_far_deltaR","mu_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm");
        t_MC->Draw("mu_far_deltaR","mu_far_deltaR>0.4"&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("mu_far_deltaR","mu_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("mu_far_deltaR","mu_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("mu_far_deltaR","mu_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("mu_far_deltaR","mu_far_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("DeltaR of the most energetic far muon; DeltaR; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_mu_far->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot mu_near_tight */
        t_MC->Draw("mu_near_tight","mu_near_pt>0"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("mu_near_tight","mu_near_pt>0"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("mu_near_tight","mu_near_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("mu_near_tight","mu_near_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("mu_near_tight","mu_near_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("mu_near_tight","mu_near_pt>0"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Tight selection bit for the nearest muon; Selection; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_mu_near->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot mu_far_tight */
	/*       t_MC->Draw("mu_far_tight>>m_MC(2,-0.5,1.5)","mu_far_pt>0"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("mu_far_tight>>m_ttbar(2,-0.5,1.5)","mu_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("mu_far_tight","mu_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("mu_far_tight>>m_DY(2,-0.5,1.5)","mu_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("mu_far_tight>>m_SEL(2,-0.5,1.5)","mu_far_pt>0"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("mu_far_tight>>m_SMU(2,-0.5,1.5)","mu_far_pt>0"&&cut_user_back&&cut_pt,"norm same");

	TH1F* m_MC = (TH1F*) gROOT->FindObject("m_MC");
        TH1F* m_ttbar = (TH1F*) gROOT->FindObject("m_ttbar");
        TH1F* m_DY = (TH1F*) gROOT->FindObject("m_DY");
        TH1F* m_SEL = (TH1F*) gROOT->FindObject("m_SEL");
        TH1F* m_SMU = (TH1F*) gROOT->FindObject("m_SMU");
        m_MC->SetLineColor(kBlack);
        m_ttbar->SetLineColor(kRed+2);
        m_DY->SetLineColor(kGreen+2);
        m_SEL->SetLineColor(kOrange-3);
        m_SMU->SetLineColor(kBlue+2);
        m_MC->SetLineWidth(3);
        m_ttbar->SetLineWidth(3);
        m_DY->SetLineWidth(3);
        m_SEL->SetLineWidth(3);
        m_SMU->SetLineWidth(3);

        m_MC->SetTitle("Tight selection bit for the most energetic muon; Selection; Occurences");
        m_MC->GetYaxis()->SetRangeUser(0,1.4);
        m_MC->Draw();
        m_ttbar->Draw("same");
        m_DY->Draw("same");
        m_SEL->Draw("same");
        m_SMU->Draw("same");
	auto legend_m_tight = new TLegend(0.10,0.70,0.9,0.9);
        legend_m_tight->SetHeader("Legend","C"); // option "C" allows to center the header                                                                               
        legend_m_tight->AddEntry(m_MC,Form("Signal (fraction of far muon = %f%%)",double(n_mu_far_MC)/double(entries_MC)*100),"l");
        legend_m_tight->AddEntry(m_ttbar,Form("TTbar (fraction of far muon = %f%%)",double(n_mu_far_ttbar)/double(entries_ttbar)*100),"l");
        //legend_m_tight->AddEntry(m_QCD,Form("QCD (fraction of far muon = %f%%)",double(n_mu_far_QCD)/double(entries_QCD)*100),"l");
        legend_m_tight->AddEntry(m_DY,Form("DY     (fraction of far muon = %f%%)",double(n_mu_far_DY)/double(entries_DY)*100),"l");
        legend_m_tight->AddEntry(m_SEL,Form("SEL   (fraction of far muon = %f%%)",double(n_mu_far_SEL)/double(entries_SEL)*100),"l");
        legend_m_tight->AddEntry(m_SMU,Form("SMU  (fraction of far muon = %f%%)",double(n_mu_far_SMU)/double(entries_SMU)*100),"l");
	legend_m_tight->Draw();
	

        c1->Print("Compare_mu_tight.png");
        c1->Print("CompareAOD.pdf");*/
        /* Plot mu_far_invmass */
        t_DY->Draw("mu_far_invmass","mu_far_invmass<200 && mu_far_invmass>0"&&cut_user_back&&cut_pt,"norm");
        t_MC->Draw("mu_far_invmass","mu_far_invmass<200 && mu_far_invmass>0"&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("mu_far_invmass","mu_far_invmass<200 && mu_far_invmass>0"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("mu_far_invmass","mu_far_invmass<200 && mu_far_invmass>0"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("mu_far_invmass","mu_far_invmass<200 && mu_far_invmass>0"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("mu_far_invmass","mu_far_invmass<200 && mu_far_invmass>0"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Invariant mass of the far muon and the track; Invmass; Occurences");
        gPad->SetLogy(1);
        gPad->Update();
        legend_mu_far->Draw();
        c1->Print("CompareAOD.pdf");
        c1->Print("CompareAOD.pdf");

        /* Plot jet_pt */
        t_MC->Draw("jet_pt","jet_pt<400"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("jet_pt","jet_pt<400"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("jet_pt","jet_pt<400"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("jet_pt","jet_pt<400"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("jet_pt","jet_pt<400"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("jet_pt","jet_pt<400"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Pt of the far most energetic jet; Pt; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot jet_deltaR */
        t_DY->Draw("jet_deltaR","jet_deltaR>0.4"&&cut_user_back&&cut_pt,"norm");
        t_MC->Draw("jet_deltaR","jet_deltaR>0.4"&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("jet_deltaR","jet_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("jet_deltaR","jet_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("jet_deltaR","jet_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("jet_deltaR","jet_deltaR>0.4"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("DeltaR of the far most energetic jet; DeltaR; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot n_jet */
        t_DY->Draw("n_jet","n_jet>0"&&cut_user_back&&cut_pt,"norm");
        t_MC->Draw("n_jet","n_jet>0"&&cut_user&&cut_pt,"norm same");
        t_ttbar->Draw("n_jet","n_jet>0"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("n_jet","n_jet>0"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("n_jet","n_jet>0"&&cut_user_back&&cut_pt,"norm same");
	t_SMU->Draw("n_jet","n_jet>0"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Number of jets with Pt>30; N; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");

        /* Plot jet_sum_pt */
        t_MC->Draw("jet_sum_pt","jet_sum_pt<800 &&jet_sum_pt>30"&&cut_user&&cut_pt,"norm");
        t_ttbar->Draw("jet_sum_pt","jet_sum_pt<800 &&jet_sum_pt>30"&&cut_user_back&&cut_pt,"norm same");
        //t_QCD->Draw("jet_sum_pt","jet_sum_pt<800 &&jet_sum_pt>30"&&cut_user_back&&cut_pt,"norm same");
        t_DY->Draw("jet_sum_pt","jet_sum_pt<800 &&jet_sum_pt>30"&&cut_user_back&&cut_pt,"norm same");
        t_SEL->Draw("jet_sum_pt","jet_sum_pt<800 &&jet_sum_pt>30"&&cut_user_back&&cut_pt,"norm same");
        t_SMU->Draw("jet_sum_pt","jet_sum_pt<800 &&jet_sum_pt>30"&&cut_user_back&&cut_pt,"norm same");
        htemp = (TH2F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Sum of the Pt of all the jets with Pt>30 GeV; Pt; Occurences");
        gPad->SetLogy(0);
        gPad->Update();
        legend_right->Draw();
        c1->Print("CompareAOD.pdf");



	/* Close the pdf file */
	c1->Print("CompareAOD.pdf]");//closes the file
}
