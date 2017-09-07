void trainMVA_2lss(TString name) {
    TString Path_out = "/afs/cern.ch/user/f/fbury/Deep_learning/TMVA/";
    TString Path_int = "/afs/cern.ch/work/f/fbury/private/";
    //gROOT->ProcessLine(".L ../../../python/plotter/functions.cc+");

    TFile *fOut = new TFile(Path_out+name+".root","RECREATE");
    TMVA::Factory *factory = new TMVA::Factory(name, fOut, "!V:!Color:Transformations=I");

    TFile *fSig = TFile::Open(Path_int+"hits_AOD_MC_1000037.root");
    TTree *tSig = (TTree *) fSig->Get("pixelHits/treeAll");
    factory->AddSignalTree(tSig, 1.0);

    TFile *fBkg = TFile::Open(Path_int+"hits_AOD_background.root");
    TTree *tBkg = (TTree *) fBkg->Get("pixelHits/treeAll");
    factory->AddBackgroundTree(tBkg, 1.0);    

    TCut all = "pt>20 && n_hit>0";

    // Dileptons

    factory->AddVariable("eta", 'F');
    
    factory->AddVariable("hit1_charge_norm", 'F');
    factory->AddVariable("hit1_ratio_charge", 'F');
    factory->AddVariable("hit1_nPixel", 'F');
    factory->AddVariable("hit1_hit_sizeX", 'F');
    factory->AddVariable("hit1_hit_sizeY", 'F');

    factory->AddVariable("hit2_charge_norm", 'F');
    factory->AddVariable("hit2_ratio_charge", 'F');
    factory->AddVariable("hit2_nPixel", 'F');
    factory->AddVariable("hit2_hit_sizeX", 'F');
    factory->AddVariable("hit2_hit_sizeY", 'F');
    
    factory->AddVariable("hit3_charge_norm", 'F');
    factory->AddVariable("hit3_ratio_charge", 'F');
    factory->AddVariable("hit3_nPixel", 'F');
    factory->AddVariable("hit3_hit_sizeX", 'F');
    factory->AddVariable("hit3_hit_sizeY", 'F');

    factory->AddVariable("hit4_charge_norm", 'F');
    factory->AddVariable("hit4_ratio_charge", 'F');
    factory->AddVariable("hit4_nPixel", 'F');
    factory->AddVariable("hit4_hit_sizeX", 'F');
    factory->AddVariable("hit4_hit_sizeY", 'F');

    factory->AddVariable("hit5_charge_norm", 'F');
    factory->AddVariable("hit5_ratio_charge", 'F');
    factory->AddVariable("hit5_nPixel", 'F');
    factory->AddVariable("hit5_hit_sizeX", 'F');
    factory->AddVariable("hit5_hit_sizeY", 'F');

    factory->AddVariable("hit6_charge_norm", 'F');
    factory->AddVariable("hit6_ratio_charge", 'F');
    factory->AddVariable("hit6_nPixel", 'F');
    factory->AddVariable("hit6_hit_sizeX", 'F');
    factory->AddVariable("hit6_hit_sizeY", 'F');

    factory->AddVariable("hit1_charge_norm + hit2_charge_norm + hit3_charge_norm + hit4_charge_norm + hit5_charge_norm + hit6_charge_norm/n_hit", 'F');
    factory->AddVariable("hit1_ratio_charge + hit2_ratio_charge + hit3_ratio_charge + hit4_ratio_charge + hit5_ratio_charge + hit6_ratio_charge", 'F');
    factory->AddVariable("hit1_nPixel + hit2_nPixel + hit3_nPixel + hit4_nPixel + hit5_nPixel + hit6_nPixel", 'F');
    factory->AddVariable("hit1_hit_sizeX + hit2_hit_sizeX + hit3_hit_sizeX + hit4_hit_sizeX + hit5_hit_sizeX + hit6_hit_sizeX/n_hit", 'F');
    factory->AddVariable("hit1_hit_sizeY + hit2_hit_sizeY + hit3_hit_sizeY + hit4_hit_sizeY + hit5_hit_sizeY + hit6_hit_sizeY/n_hit", 'F');

    factory->SetWeightExpression("1");
    factory->PrepareTrainingAndTestTree( all, all, "SplitMode=Random" );

    factory->BookMethod( TMVA::Types::kLD, "LD", "!H:!V:VarTransform=None:CreateMVAPdfs" );
    factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood", "!H:!V:!TransformOutput" );

    TString BDTGopt = "!H:!V:NTrees=200:BoostType=Grad:Shrinkage=0.10:!UseBaggedGrad:nCuts=200:nEventsMin=100:NNodesMax=5";

    BDTGopt = ":CreateMVAPdfs"; // Create Rarity distribution
    factory->BookMethod( TMVA::Types::kBDT, "BDTG", BDTGopt);

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    fOut->Close();
}
