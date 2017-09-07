
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

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHit.h"

#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/CommonTopologies/interface/PixelTopology.h"
#include "Geometry/Records/interface/TrackerTopologyRcd.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

class TrackDecay : public edm::one::EDAnalyzer<edm::one::SharedResources> {
    public:
        explicit  TrackDecay (const edm::ParameterSet&);
        ~TrackDecay();

    private:
        virtual void analyze(const edm::Event&, const edm::EventSetup&);

        // token that we use to get the data (in this case, tracks) from the event
        const edm::EDGetTokenT<std::vector<reco::Track>> tracks_;    
  	const edm::EDGetTokenT<std::vector<reco::GenParticle>> generate_;       

        // TrackerTopology: something that maps detector ids into logical arrangements within the detctor (e.g. which subdetector, layer, ...)
        edm::ESHandle<TrackerTopology> theTrkTopo;
        // TrackerGeometry: contains C++ objects for each detector telling how they are arranged geometrically in space (i.e. precise position and orientation of each module)
        edm::ESHandle<TrackerGeometry> theGeometry;

        // output ROOT tree for all hits
        TTree *treeAll_;
        // define a structure to hold variables about a hit to be put in the tree
        struct Kinematic {
	    float mass; 
            float eta;
	    float pt;
	    float p;
	    float beta;
	    float gb;
	    float theta;
	} gen_,reco_;
	struct  Motion {
	    int selected;
            float length;
            int nValidBH;
            float prod_rho;
            float prod_z;
            float decay_rho;
            float decay_z;
            float pion_eta;
            float pion_pt;
            int nLayersBH;
	} track_;
};

//
// constructors and destructor
//
TrackDecay::TrackDecay(const edm::ParameterSet& iConfig):
    tracks_(consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("tracks"))),
    generate_(consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("gen")))
{
    usesResource("TFileService");
    edm::Service<TFileService> fs;
    // we create a ROOT tree 
    treeAll_ = fs->make<TTree>("treeAll","treeAll");

    // now we define each variable in the tree, and give the addess of the C++ variable to read the contents, and the type (I = int, F = float)
    // see https://root.cern.ch/doc/master/classTTree.html
    treeAll_->Branch("reco_mass", &reco_.mass, "reco_.mass/F");
    treeAll_->Branch("reco_eta", &reco_.eta, "reco_.eta/F");
    treeAll_->Branch("reco_pt", &reco_.pt, "reco_.pt/F");
    treeAll_->Branch("reco_p", &reco_.p, "reco_.p/F");
    treeAll_->Branch("reco_beta", &reco_.beta, "reco_.beta/F"); 
    treeAll_->Branch("reco_gb", &reco_.gb, "reco_.gb/F");
    treeAll_->Branch("reco_theta", &reco_.theta, "reco_.theta/F");

    treeAll_->Branch("gen_mass", &gen_.mass, "gen_.mass/F");
    treeAll_->Branch("gen_eta", &gen_.eta, "gen_.eta/F");
    treeAll_->Branch("gen_pt", &gen_.pt, "gen_.pt/F");
    treeAll_->Branch("gen_p", &gen_.p, "gen_.p/F");
    treeAll_->Branch("gen_beta", &gen_.beta, "gen_.beta/F"); 
    treeAll_->Branch("gen_gb", &gen_.gb, "gen_.gb/F");
    treeAll_->Branch("gen_theta", &gen_.theta, "gen_.theta/F");
   
    treeAll_->Branch("selected", &track_.selected, "track_.selected/I");
    treeAll_->Branch("length", &track_.length, "track_.length/F");
    treeAll_->Branch("nValidBH", &track_.nValidBH, "track_.nValidBH/F");
    treeAll_->Branch("nLayersBH", &track_.nLayersBH, "track_.nLayersBH/F");
    treeAll_->Branch("prod_rho", &track_.prod_rho, "track_.prod_rho/F");
    treeAll_->Branch("prod_z", &track_.prod_z, "track_.prod_rho/F");
    treeAll_->Branch("decay_rho", &track_.decay_rho, "track_.decay_rho/F");
    treeAll_->Branch("decay_z", &track_.decay_z, "track_.decay_rho/F");
    treeAll_->Branch("pion_pt", &track_.pion_pt, "track_.pion_pt/F");
    treeAll_->Branch("pion_eta", &track_.pion_eta, "track_.pion_peta/F");

 
}



TrackDecay::~TrackDecay()
{
}

void
TrackDecay::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // read conditions
    iSetup.get<TrackerTopologyRcd>().get(theTrkTopo);
    iSetup.get<TrackerDigiGeometryRecord>().get(theGeometry);

    // read data
    edm::Handle<std::vector<reco::Track>> tracks;
    iEvent.getByToken(tracks_, tracks);

    // read MC
    edm::Handle<std::vector<reco::GenParticle>> gen_tracks;
    iEvent.getByToken(generate_, gen_tracks);
	
    // loop on MC generated particles   
    for (const reco::GenParticle & gptrack : *gen_tracks)
    {
	if (gptrack.status() != 62 || std::abs(gptrack.pdgId()) != 1000024 || gptrack.numberOfDaughters() != 2)
		continue; 		// if not the particle we're looking for -> next particle
	// records the kinematic parameters of generated particle
        gen_.beta = 1/sqrt((1+(gptrack.mass()*gptrack.mass()/(gptrack.p()*gptrack.p()))));
        gen_.gb = gptrack.p()/gptrack.mass();
        gen_.eta = gptrack.eta();
        gen_.pt = gptrack.pt();
        gen_.p = gptrack.p();
        gen_.theta = gptrack.theta();
        gen_.mass = gptrack.mass();

	
	//Initialization	
	float min_angle = 1;  //records the minimal value of the angle difference
        float min_pt = 1;   //records the minimal value of the Pt difference
	

	reco_.beta = 0;
        reco_.gb = 0;   
        reco_.eta = 0;
        reco_.pt = 0;
        reco_.p = 0;
        reco_.theta = 0;
        reco_.mass = 0;

	track_.nValidBH = 0;
        track_.nLayersBH = 0;

	track_.selected = 0;		//0->no track associated, 1-> track associated 
	
	// Find the 2 daughters
	const reco::GenParticle &d1 = *gptrack.daughterRef(0);
	const reco::GenParticle &d2 = *gptrack.daughterRef(1);

	// Identify the 2 daughters
	
	if (std::abs(d1.pdgId()) == 211)  // first daughter is a pion
	{
		track_.pion_pt = d1.pt();
		track_.pion_eta = d1.eta();
	}
	if (std::abs(d2.pdgId()) == 211)  // first daughter is a pion
	{
		track_.pion_pt = d2.pt();
		track_.pion_eta = d2.eta();
	}		
	
	// Find the production and decay parameters
	track_.prod_rho = (gptrack.vertex()).rho();	
	track_.prod_z = (gptrack.vertex()).z();	
	track_.decay_rho = (d1.vertex()).rho();	
	track_.decay_z = (d1.vertex()).z();	
	
	track_.length = sqrt(pow(track_.prod_rho-track_.decay_rho,2)+pow(track_.prod_z-track_.decay_z,2));			
              

	for (const reco::Track & track : *tracks) 
	{
		// Look for a close reconstructed track
		float diff_angle =  deltaR(track.eta(), track.phi(), gptrack.eta(), gptrack.phi());
                float diff_pt =  std::abs((gptrack.pt()-track.pt())/gptrack.pt());

		if (diff_angle > 0.1)
                        continue;  // the two tracks are not close
                if (diff_pt>0.1 && (gptrack.pt()<5 || track.pt()<5))   // if pt>5GeV => huge uncertainty on pt
		      continue; // the two tracks have different Pt
		
		// Find the closest reconstructed track 
                if (diff_angle < min_angle && diff_pt < min_pt)
                {
			track_.selected=1;
			
			// Record the new minimal values if they have changed
		        min_angle = diff_angle;
                        min_pt = diff_pt;

			// Store the kinematic values 
			reco_.beta = 1/sqrt((1+(gptrack.mass()*gptrack.mass()/(track.p()*track.p()))));  		
			reco_.gb = track.p()/gptrack.mass();	
			reco_.eta = track.eta();
			reco_.pt = track.pt();
			reco_.p = track.p(); 
			reco_.theta = track.theta();
			reco_.mass = gptrack.mass();
       
			// Find the number of valid hits on pixel
			track_.nValidBH = track.hitPattern().numberOfValidPixelBarrelHits();	 
			track_.nLayersBH = track.hitPattern().pixelBarrelLayersWithMeasurement();	 
		}
	 }
    	treeAll_->Fill();
    }
}
//define this as a plug-in
DEFINE_FWK_MODULE(TrackDecay);
