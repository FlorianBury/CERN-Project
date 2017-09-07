// system include files
#include <memory>
#include <cmath>
#include <TTree.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Provenance/interface/EventID.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHit.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/DeDxHitInfo.h" 
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/CommonTopologies/interface/PixelTopology.h"
#include "Geometry/Records/interface/TrackerTopologyRcd.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <TTree.h>


class PixelHitOnTrackStudiesAOD : public edm::one::EDAnalyzer<edm::one::SharedResources> {
    public:
        explicit PixelHitOnTrackStudiesAOD(const edm::ParameterSet&);
        ~PixelHitOnTrackStudiesAOD();

    private:
        virtual void analyze(const edm::Event&, const edm::EventSetup&);

        // token that we use to get the data (in this case, tracks) from the event
        const edm::EDGetTokenT<std::vector<reco::Track>> tracks_;    
        const edm::EDGetTokenT<reco::DeDxHitInfoAss> dedx_;
        const edm::EDGetTokenT<std::vector<reco::Vertex>> vertices_;
        const edm::EDGetTokenT<std::vector<reco::PFCandidate>> candidates_;
        const edm::EDGetTokenT<std::vector<reco::PFMET>> MET_;
        const edm::EDGetTokenT<std::vector<reco::GenParticle>> generate_;
        const edm::EDGetTokenT<std::vector<reco::Muon>> muons_;
        const edm::EDGetTokenT<std::vector<reco::GsfElectron>> electrons_;
        const edm::EDGetTokenT<std::vector<reco::PFJet>> jets_;
        const edm::EDGetTokenT<edm::ValueMap<bool>> electronRef_;
	
        // TrackerTopology: something that maps detector ids into logical arrangements within the detctor (e.g. which subdetector, layer, ...)
        edm::ESHandle<TrackerTopology> theTrkTopo;
        // TrackerGeometry: contains C++ objects for each detector telling how they are arranged geometrically in space (i.e. precise position and orientation of each module)
        edm::ESHandle<TrackerGeometry> theGeometry;

        // output ROOT tree for all hits
        TTree *treeAll_;
        // define a structure to hold variables about a hit to be put in the tree
 	struct Hit_variables
	{
            float charge; 
            float charge_norm; 
            float ratio_charge; 
            int detector;
	    int layer;
            int nPixel;
            float hit_r;
	    float hit_phi;
	    float hit_z;
            int hit_sizeX;
	    int hit_sizeY;
	}  hit_[6];		// records the information of each layer

	struct Track_variables 
	{
	    int signal; //1 if signal, 0 if background 
	    float mass; 
            float eta;
	    float pt;
	    float pt_error;
	    float p;
	    float theta;
	    int n_hit;
	    int n_hit_pixel;
	    int n_hit_strip;
	    int n_layer_pixel;
	    int n_layer_strip;
	    int n_miss_outer;
	    int n_miss_inner;
	    int quality;
	    float IP_tran;
	    float IP_long;
	    float IP_tran_error;
	    float IP_long_error;
	    float isolation_out;
	    float isolation_int;
	    float met_pt;
	    float met_phi;
	    long int run;
	    long int lumisection;
	    long long int event;
	} track_;       
	struct lepton_variables 
	{
	    float near_deltaR;
	    float far_deltaR;
	    float near_pt;
	    float far_pt;
 	    float far_invmass;	
	    int near_tight;
	    int far_tight;
	}e_,mu_;
	struct jet_varaibles
	{
	    float pt;
	    float deltaR;
	    float sum_pt;
	    int n_jet;
	}jet_; 
};

//
// constructors and destructor
//
PixelHitOnTrackStudiesAOD::PixelHitOnTrackStudiesAOD(const edm::ParameterSet& iConfig):
    tracks_(consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("tracks"))),
    dedx_(consumes<reco::DeDxHitInfoAss>(iConfig.getParameter<edm::InputTag>("dedxInfo"))),
    vertices_(consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("vertices"))),  
    candidates_(consumes<std::vector<reco::PFCandidate>>(iConfig.getParameter<edm::InputTag>("candidates"))),
    MET_(consumes<std::vector<reco::PFMET>>(iConfig.getParameter<edm::InputTag>("pfMet"))),
    generate_(consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("gen"))),
    muons_(consumes<std::vector<reco::Muon>>(iConfig.getParameter<edm::InputTag>("muons"))),
    electrons_(consumes<std::vector<reco::GsfElectron>>(iConfig.getParameter<edm::InputTag>("electrons"))),
    jets_(consumes<std::vector<reco::PFJet>>(iConfig.getParameter<edm::InputTag>("jets"))),
    electronRef_(consumes<edm::ValueMap<bool>>(iConfig.getParameter<edm::InputTag>("electronRef")))
{
    usesResource("TFileService");
    edm::Service<TFileService> fs;
    // we create a ROOT tree 
    treeAll_ = fs->make<TTree>("treeAll","treeAll");

    // now we define each variable in the tree, and give the addess of the C++ variable to read the contents, and the type (I = int, F = float)
    // see https://root.cern.ch/doc/master/classTTree.html
    treeAll_->Branch("run", &track_.run, "run/I");
    treeAll_->Branch("lumisection", &track_.lumisection, "lumisection/I");
    treeAll_->Branch("event", &track_.event, "event/l");

    treeAll_->Branch("mass", &track_.mass, "mass/F");
    treeAll_->Branch("signal", &track_.signal, "signal/I");
    treeAll_->Branch("eta", &track_.eta, "eta/F");
    treeAll_->Branch("pt", &track_.pt, "pt/F");
    treeAll_->Branch("pt_error", &track_.pt_error, "pt_error/F");
    treeAll_->Branch("p", &track_.p, "p/F");
    treeAll_->Branch("theta", &track_.theta, "theta/F");
    treeAll_->Branch("n_hit", &track_.n_hit, "n_hit/I");
    treeAll_->Branch("n_hit_pixel", &track_.n_hit_pixel, "n_hit_pixel/I");
    treeAll_->Branch("n_hit_strip", &track_.n_hit_strip, "n_hit_strip/I");
    treeAll_->Branch("n_layer_pixel", &track_.n_layer_pixel, "n_layer_pixel/I");
    treeAll_->Branch("n_layer_strip", &track_.n_layer_strip, "n_layer_strip/I");
    treeAll_->Branch("n_miss_outer", &track_.n_miss_outer, "n_miss_outer/I");
    treeAll_->Branch("n_miss_inner", &track_.n_miss_inner, "n_miss_inner/I");
    treeAll_->Branch("quality", &track_.quality, "quality/I");
    treeAll_->Branch("IP_tran", &track_.IP_tran, "IP_tran/F");
    treeAll_->Branch("IP_long", &track_.IP_long, "IP_long/F");
    treeAll_->Branch("IP_tran_error", &track_.IP_tran_error, "IP_tran_error/F");
    treeAll_->Branch("IP_long_error", &track_.IP_long_error, "IP_long_error/F");
    treeAll_->Branch("isolation_out", &track_.isolation_out, "isolation_out/F");
    treeAll_->Branch("isolation_int", &track_.isolation_int, "isolation_int/F");
    treeAll_->Branch("met_pt", &track_.met_pt, "met_pt/F");
    treeAll_->Branch("met_phi", &track_.met_phi, "met_phi/F");
    treeAll_->Branch("e_near_pt", &e_.near_pt, "e_near_pt/F");
    treeAll_->Branch("e_far_pt", &e_.far_pt, "e_far_pt/F");
    treeAll_->Branch("e_near_deltaR", &e_.near_deltaR, "e_near_deltaR/F");
    treeAll_->Branch("e_far_deltaR", &e_.far_deltaR, "e_far_deltaR/F");
    treeAll_->Branch("e_near_tight", &e_.near_tight, "e_near_tight/I");
    treeAll_->Branch("e_far_tight", &e_.far_tight, "e_far_tight/I");
    treeAll_->Branch("e_far_invmass", &e_.far_invmass, "e_far_invmass/F");

    treeAll_->Branch("mu_near_pt", &mu_.near_pt, "mu_near_pt/F");
    treeAll_->Branch("mu_far_pt", &mu_.far_pt, "mu_far_pt/F");
    treeAll_->Branch("mu_near_deltaR", &mu_.near_deltaR, "mu_near_deltaR/F");
    treeAll_->Branch("mu_far_deltaR", &mu_.far_deltaR, "mu_far_deltaR/F");
    treeAll_->Branch("mu_near_tight", &mu_.near_tight, "mu_near_tight/I");
    treeAll_->Branch("mu_far_tight", &mu_.far_tight, "mu_far_tight/I");
    treeAll_->Branch("mu_far_invmass", &mu_.far_invmass, "mu_far_invmass/F");

    treeAll_->Branch("jet_pt", &jet_.pt, "jet_pt/F");
    treeAll_->Branch("jet_sum_pt", &jet_.sum_pt, "jet_sum_pt/F");
    treeAll_->Branch("jet_deltaR", &jet_.deltaR, "jet_deltaR/F");
    treeAll_->Branch("n_jet", &jet_.n_jet, "n_jet/I");

    treeAll_->Branch("hit1_layer", &hit_[0].layer, "hit1_layer/I");
    treeAll_->Branch("hit1_charge_norm", &hit_[0].charge_norm, "hit1_charge_norm/F");
    treeAll_->Branch("hit1_ratio_charge", &hit_[0].ratio_charge, "hit1_ratio_charge/F");
    treeAll_->Branch("hit1_nPixel", &hit_[0].nPixel, "hit1_nPixel/I");
    treeAll_->Branch("hit1_hit_sizeX", &hit_[0].hit_sizeX, "hit1_hit_sizeX/I");
    treeAll_->Branch("hit1_hit_sizeY", &hit_[0].hit_sizeY, "hit1_hit_sizeY/I" );
   
    treeAll_->Branch("hit2_layer", &hit_[1].layer, "hit2_layer/I");
    treeAll_->Branch("hit2_charge_norm", &hit_[1].charge_norm, "hit2_charge_norm/F");
    treeAll_->Branch("hit2_ratio_charge", &hit_[1].ratio_charge, "hit2_ratio_charge/F");
    treeAll_->Branch("hit2_nPixel", &hit_[1].nPixel, "hit2_nPixel/I");
    treeAll_->Branch("hit2_hit_sizeX", &hit_[1].hit_sizeX, "hit2_hit_sizeX/I");
    treeAll_->Branch("hit2_hit_sizeY", &hit_[1].hit_sizeY, "hit2_hit_sizeY/I" );

    treeAll_->Branch("hit3_layer", &hit_[2].layer, "hit3_layer/I");
    treeAll_->Branch("hit3_charge_norm", &hit_[2].charge_norm, "hit3_charge_norm/F");
    treeAll_->Branch("hit3_ratio_charge", &hit_[2].ratio_charge, "hit3_ratio_charge/F");
    treeAll_->Branch("hit3_nPixel", &hit_[2].nPixel, "hit3_nPixel/I");
    treeAll_->Branch("hit3_hit_sizeX", &hit_[2].hit_sizeX, "hit3_hit_sizeX/I");
    treeAll_->Branch("hit3_hit_sizeY", &hit_[2].hit_sizeY, "hit3_hit_sizeY/I" );

    treeAll_->Branch("hit4_layer", &hit_[3].layer, "hit4_layer/I");
    treeAll_->Branch("hit4_charge_norm", &hit_[3].charge_norm, "hit4_charge_norm/F");
    treeAll_->Branch("hit4_ratio_charge", &hit_[3].ratio_charge, "hit4_ratio_charge/F");
    treeAll_->Branch("hit4_nPixel", &hit_[3].nPixel, "hit4_nPixel/I");
    treeAll_->Branch("hit4_hit_sizeX", &hit_[3].hit_sizeX, "hit4_hit_sizeX/I");
    treeAll_->Branch("hit4_hit_sizeY", &hit_[3].hit_sizeY, "hit4_hit_sizeY/I" );

    treeAll_->Branch("hit5_layer", &hit_[4].layer, "hit5_layer/I");
    treeAll_->Branch("hit5_charge_norm", &hit_[4].charge_norm, "hit5_charge_norm/F");
    treeAll_->Branch("hit5_ratio_charge", &hit_[4].ratio_charge, "hit5_ratio_charge/F");
    treeAll_->Branch("hit5_nPixel", &hit_[4].nPixel, "hit5_nPixel/I");
    treeAll_->Branch("hit5_hit_sizeX", &hit_[4].hit_sizeX, "hit5_hit_sizeX/I");
    treeAll_->Branch("hit5_hit_sizeY", &hit_[4].hit_sizeY, "hit5_hit_sizeY/I" );

    treeAll_->Branch("hit6_layer", &hit_[5].layer, "hit6_layer/I");
    treeAll_->Branch("hit6_charge_norm", &hit_[5].charge_norm, "hit6_charge_norm/F");
    treeAll_->Branch("hit6_ratio_charge", &hit_[5].ratio_charge, "hit6_ratio_charge/F");
    treeAll_->Branch("hit6_nPixel", &hit_[5].nPixel, "hit6_nPixel/I");
    treeAll_->Branch("hit6_hit_sizeX", &hit_[5].hit_sizeX, "hit6_hit_sizeX/I");
    treeAll_->Branch("hit6_hit_sizeY", &hit_[5].hit_sizeY, "hit6_hit_sizeY/I" );
}

PixelHitOnTrackStudiesAOD::~PixelHitOnTrackStudiesAOD()
{
}

void
PixelHitOnTrackStudiesAOD::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // read conditions
    iSetup.get<TrackerTopologyRcd>().get(theTrkTopo);
    iSetup.get<TrackerDigiGeometryRecord>().get(theGeometry);

    // read data
    edm::Handle<std::vector<reco::Track>> tracks;
    iEvent.getByToken(tracks_, tracks);

    edm::Handle<reco::DeDxHitInfoAss> dedxMap;
    iEvent.getByToken(dedx_, dedxMap);

    edm::Handle<std::vector<reco::Vertex>> vertices;
    iEvent.getByToken(vertices_, vertices);
    
    edm::Handle<std::vector<reco::PFCandidate>> candidates;
    iEvent.getByToken(candidates_, candidates);
    
    edm::Handle<std::vector<reco::PFMET>> MET;
    iEvent.getByToken(MET_, MET);
   
    edm::Handle<std::vector<reco::GenParticle>> gen_tracks;
    iEvent.getByToken(generate_, gen_tracks);
 
    edm::Handle<std::vector<reco::Muon>> muons;
    iEvent.getByToken(muons_, muons);
    
    edm::Handle<std::vector<reco::GsfElectron>> electrons;
    iEvent.getByToken(electrons_, electrons);
    
    edm::Handle<std::vector<reco::PFJet>> jets;
    iEvent.getByToken(jets_, jets);

    edm::Handle<edm::ValueMap<bool>> electronRef;
    iEvent.getByToken(electronRef_, electronRef);

    // loop on tracks 
    for (unsigned int itrack = 0, ntracks = tracks->size(); itrack < ntracks; ++itrack) {
        const reco::Track & track = (*tracks)[itrack];
	//std::cout<<"Run : "<<iEvent.id().run()<<"\tLumisection : "<<iEvent.id().luminosityBlock()<<"\tEvent : "<<iEvent.id().event()<<std::endl;
	// Event information
	track_.run = iEvent.id().run(); 
	track_.lumisection = iEvent.id().luminosityBlock(); 
	track_.event = iEvent.id().event(); 
        // Track information
	track_.pt=track.pt();
	if (track_.pt<20)	//rejects background
		continue;
	track_.mass=0;
	track_.signal=0;
	track_.pt_error=track.ptError();
	track_.eta=track.eta();
	track_.p=track.p();
	track_.theta=track.theta();
	track_.n_hit=track.hitPattern().numberOfValidTrackerHits();
	track_.n_hit_pixel=track.hitPattern().numberOfValidPixelHits();
	track_.n_hit_strip=track.hitPattern().numberOfValidStripHits();
	track_.n_layer_pixel=track.hitPattern().pixelLayersWithMeasurement();
	track_.n_layer_strip=track.hitPattern().stripLayersWithMeasurement();
	track_.n_miss_outer=track.hitPattern().numberOfLostHits(reco::HitPattern::MISSING_OUTER_HITS);
	track_.n_miss_inner=track.hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
	track_.quality=int(track.quality(reco::Track::highPurity));
	
	// Lepton tight selected vector creation
	std::vector<reco::Particle::LorentzVector> leptons; 

	// Vertex information
	const reco::Vertex & vertex = (*vertices)[0]; // first vertex => signal (others => pile up)

	track_.IP_tran=track.dxy(vertex.position());
	track_.IP_long=track.dz(vertex.position());
	track_.IP_tran_error=track.dxyError();
	track_.IP_long_error=track.dzError();

	// Muon information
	mu_.near_deltaR=0;
        mu_.near_pt=0;
        mu_.near_tight=0;
        mu_.far_deltaR=0;
        mu_.far_pt=0;
        mu_.far_tight=0;
        mu_.far_invmass=0;

	float near_diff=1;
	float far_pt=0;
	int tight_selected = 0;
	for (const reco::Muon & muon : *muons)
	{
		float diff_angle =  deltaR(track.eta(), track.phi(), muon.eta(), muon.phi());
		// loose selection 
		if (muon.pt()<10) continue;
		if ((muon.isPFMuon() && (muon.isGlobalMuon() || muon.isTrackerMuon()))==false) continue;
		if (muon.track().isNonnull()==false)  continue;
		if (fabs(muon.track()->dxy(vertex.position()))>0.3 || fabs(muon.track()->dz(vertex.position()))>0.3) continue;
		if (muon::isMediumMuon(muon) && muon.pfIsolationR03().sumChargedHadronPt/muon.pt() < 0.15)  // Checks the tight selection
		{
			tight_selected = 1;
			leptons.push_back(muon.p4());
		}
		else
			tight_selected = 0;		
		
		if (diff_angle<0.4) // finds the closest
		{
			if (diff_angle<near_diff)
			{
				near_diff = diff_angle; // holds the minimal value
				mu_.near_pt = muon.pt();
				mu_.near_deltaR = diff_angle;
				mu_.near_tight = tight_selected;
			}
		} 	
		else // find the far highest Pt
		{
			if (muon.pt()>far_pt)
			{
				far_pt = muon.pt(); // holds the maximal value
                                mu_.far_pt = muon.pt();
                                mu_.far_deltaR = diff_angle;
				mu_.far_invmass = std::sqrt(std::pow(muon.energy()+track.p(),2)-std::pow(muon.px()+track.px(),2)-std::pow(muon.py()+track.py(),2)-std::pow(muon.pz()+track.pz(),2));
				mu_.far_tight = tight_selected;
			}
		}
	}

	// Electron information
	e_.near_deltaR=0;
        e_.near_pt=0;
        e_.near_tight=0;
        e_.far_deltaR=0;
        e_.far_pt=0;
        e_.far_tight=0;
        e_.far_invmass=0;

	near_diff=1;
	far_pt=0;
	tight_selected = 0;
        for (unsigned int ielectron = 0, nelectrons = electrons->size(); ielectron < nelectrons; ++ielectron)
        {
                const reco::GsfElectron & electron = (*electrons)[ielectron];
		float diff_angle =  deltaR(track.eta(), track.phi(), electron.eta(), electron.phi());
		// loose selection 
		if (electron.pt()<10) continue;
		if (electron.full5x5_sigmaIetaIeta() > (electron.isEB() ? 0.012 : 0.04)) continue;
		if (electron.gsfTrack().isNonnull()==false) continue;
		if (fabs(electron.gsfTrack()->dxy(vertex.position()))>0.3 || fabs(electron.gsfTrack()->dz(vertex.position()))>0.3) continue;
		tight_selected = (*electronRef)[reco::GsfElectronRef (electrons,ielectron)]; //Checks the tight selection
		if ( tight_selected == 1)
			leptons.push_back(electron.p4());	

		if (diff_angle<0.4) // finds the closest
		{
			if (diff_angle<near_diff)
			{
				near_diff = diff_angle; // holds the minimal value
				e_.near_pt = electron.pt();
				e_.near_deltaR = diff_angle;
        			e_.near_tight = tight_selected; 
			}
		} 	
		else // find the far highest Pt
		{
			if (electron.pt()>far_pt)
			{
				far_pt = electron.pt(); // holds the maximal value
                                e_.far_pt = electron.pt();
                                e_.far_deltaR = diff_angle;
				e_.far_invmass = std::sqrt(std::pow(electron.energy()+track.p(),2)-std::pow(electron.px()+track.px(),2)-std::pow(electron.py()+track.py(),2)-std::pow(electron.pz()+track.pz(),2));
                                e_.far_tight = tight_selected; 
			}
		}
	}

	// Conditions for trigger selection
	//if (e_.far_tight == 0 && mu_.far_tight==0) continue; //rejects events without a far e or mu
	//if (e_.far_pt<35 && mu_.far_pt<27) continue; //rejects events where e or mu is too low energetic
/*
        // Generated Particles loop
	float min_angle = 1;  //records the minimal value of the angle difference
	float min_pt = 1;   //records the minimal value of the Pt difference
	for (const reco::GenParticle & gptrack : *gen_tracks){
		if (gptrack.status() != 62 || std::abs(gptrack.pdgId()) != 1000037 || gptrack.numberOfDaughters() != 3)
			continue; // if not the SUSY particle we are looking for	
	 
		float diff_angle =  deltaR(track.eta(), track.phi(), gptrack.eta(), gptrack.phi());
		float diff_pt =  std::abs((gptrack.pt()-track.pt())/gptrack.pt());

		// Search for the closest generated particle for the track
	
               if (diff_angle > 0.1)
  			continue;  // the two tracks are not close
               if (diff_pt>0.1 && (gptrack.pt()<5 || track.pt()<5))   // if pt>5GeV => huge uncertainty on pt
 			continue; // the two tracks have different Pt
		
		if (diff_angle < min_angle && diff_pt < min_pt) //records the minimum value and assign the mass to the track
		{
			min_angle = diff_angle;
			min_pt = diff_pt;
			
			track_.mass = gptrack.mass();	//records the mass for the minimum 
			track_.signal = 1; 	// records the signal behaviour		
		}  

	 }

	if (track_.signal==0)
		continue; // keeps only signal
*/
	// Particle flow candidates information
	double A_int=0, A_out=0;	//A->charged from the vertex
	double B_out=0;		//B->charged from the pile-up
	double C_int=0, C_out=0; //C->neutral (can't be tracked to the vertex)
	for (unsigned int icandidate = 0, ncandidates = candidates->size(); icandidate < ncandidates; ++icandidate)
	{
		const reco::PFCandidate & candidate = (*candidates)[icandidate];
		// Selection of the closest particles 
		float diff_angle =  deltaR(track.eta(), track.phi(), candidate.eta(), candidate.phi());
		if (diff_angle>0.3) //rejects the far candidates
			continue;
		// Differentiation into groups
		if (diff_angle>0.01) // not the track itself
		{
			if (candidate.trackRef().isNull())
				C_out += candidate.pt();
			else
			{
				if(fabs(candidate.trackRef()->dz(vertex.position())<0.3))
					A_out += candidate.pt();
				else
					B_out += candidate.pt(); 
			}
		}
		else 	//track itself
		{
			if (candidate.trackRef().isNull())
                                C_int += candidate.pt();
                        else
                        {
                                if(fabs(candidate.trackRef()->dz(vertex.position())<0.3))
                                        A_int += candidate.pt();
                        }
		}
	}
	track_.isolation_out = (A_out + std::max(C_out-0.5*B_out,0.))/track.pt();
	track_.isolation_int = (A_int + std::max(C_int,0.))/track.pt();

	// MET information
	const reco::PFMET & met = (*MET)[0];
	track_.met_pt = met.pt();
	track_.met_phi = met.phi();


	//Jet information 
	jet_.pt = 0;
	jet_.deltaR = 0;
	jet_.sum_pt = 0;
	jet_.n_jet = 0;
	float pt_max = 0;
	for (const reco::PFJet & jet : *jets)
	{
		if (fabs(jet.eta())>2.4) continue;  // good jet detection
		float diff_angle_track =  deltaR(track.eta(), track.phi(), jet.eta(), jet.phi()); //if the track itself
		if (diff_angle_track<0.4) continue; 
		
		for (int unsigned i=0; i<leptons.size(); i++) // discards jets being tight lepton
		{
			float diff_angle_lep = deltaR(jet.eta(),jet.phi(),leptons[i].Eta(),leptons[i].Phi());
			if (diff_angle_lep<0.4)
				continue;	
		}
		if (jet.pt()>pt_max)
		{
			pt_max = jet.pt(); ///holds maximum values
			jet_.pt = jet.pt();
			jet_.deltaR = diff_angle_track;	
		}
		if (jet.pt()>30)
		{
			jet_.sum_pt += jet.pt();
			jet_.n_jet++;
		}
	}

	//Initialization of hit parameters 
	for (int i=0 ; i<6 ; i++)
	{
	    hit_[i].charge=0; 
            hit_[i].charge_norm=0; 
            hit_[i].ratio_charge=0; 
            hit_[i].detector=0;
	    hit_[i].layer=0;
            hit_[i].nPixel=0;
            hit_[i].hit_r=0;
	    hit_[i].hit_phi=0;
	    hit_[i].hit_z=0;
            hit_[i].hit_sizeX=0;
	    hit_[i].hit_sizeY=0;
	} 
	
        const reco::DeDxHitInfoRef dedxRef = (*dedxMap)[reco::TrackRef(tracks,itrack)];
        if (dedxRef.isNull()) continue; /// this skips tracks for which there's no DeDx recorded (pt < 10 GeV)
        const reco::DeDxHitInfo & hitInfo = *dedxRef;

        // loop on the hits on the track
	int n=0; //index going through the structure object hit_[n] 
	for (unsigned int i = 0, nhits = hitInfo.size(); i < nhits; ++i) {
            // get the id of the module (a unique integer identifying each module in the CMS detector)
            DetId id = hitInfo.detId(i);
            // skip hits that are not on the pixel detector
            if (id.subdetId() != PixelSubdetector::SubDetector::PixelBarrel && id.subdetId() != PixelSubdetector::SubDetector::PixelEndcap) continue;

            if (n>=6) continue; // avoids the rare events with more than 6 hits that overflow our array 
	    
	    hit_[n].detector = id.subdetId();       // will be 1 for barrel and 2 for endcaps, as defined in DataFormats/SiPixelDetId/interface/PixelSubdetector.h                
            hit_[n].layer    = theTrkTopo->layer(id);  // the layer

            // find the C++ object corresponding to this detector module
            const PixelGeomDetUnit* det = dynamic_cast<const PixelGeomDetUnit*>(theGeometry->idToDet(id));
            if (!det) throw cms::Exception("CorruptData", "Missing DetID in geometry?? this is not supposed to happen.");

            // get the pixel topology, i.e. what maps from indices of pixels (integers) to absolute positions on the surface of the pixel module in cm
            const PixelTopology& topol = det->specificTopology();

            const SiPixelCluster & cluster = *hitInfo.pixelCluster(i);

            // get the charge of the cluster
            hit_[n].charge = cluster.charge();
            hit_[n].nPixel = cluster.size();
            // get the normalized charge
		if (hit_[n].detector==1)  // barrel
			hit_[n].charge_norm = hit_[n].charge*std::abs(sin(track_.theta));
		
		if (hit_[n].detector==2)  // endcaps
			hit_[n].charge_norm = hit_[n].charge*std::abs(cos(track_.theta));
	    // compute the ratio_charge = max_deposit*size/charge_norm
	    int  max_deposit=0;
	    const auto & pixelADC = cluster.pixelADC();
	    int size_ADC = pixelADC.size();
	    for (int i=0 ; i<size_ADC ; i++)
	    {
	    	if (max_deposit<pixelADC[i])
			max_deposit = pixelADC[i];
	    }
	    hit_[n].ratio_charge = (max_deposit*size_ADC)/hit_[n].charge_norm;
	    // get size (in X and Y) of the cluster
            hit_[n].hit_sizeX = cluster.sizeX();
            hit_[n].hit_sizeY = cluster.sizeY();

	    // position of the cluster in pixel units
            MeasurementPoint mp(cluster.x(), cluster.y());
            // convert in position of the cluster in the reference frame of the module (in cm)
            LocalPoint lp = topol.localPosition(mp);
            // convert in position of the cluster in the global frame of CMS (in cm)
            GlobalPoint gp = det->surface().toGlobal(lp);
                hit_[n].hit_r = gp.perp();
                hit_[n].hit_phi = gp.phi();
                hit_[n].hit_z = gp.z();

            // Prepares for the next hit recording
	    n++; // gets into a new hit
        }
        // fill one entry in the tree, reading the values from the variables for which we did the 'Branch' call in the above
	treeAll_->Fill();
    }
}


//define this as a plug-in
DEFINE_FWK_MODULE(PixelHitOnTrackStudiesAOD);
