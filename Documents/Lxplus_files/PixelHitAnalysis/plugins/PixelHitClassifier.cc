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
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

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

class PixelHitClassifier : public edm::one::EDAnalyzer<edm::one::SharedResources> {
    public:
        explicit PixelHitClassifier(const edm::ParameterSet&);
        ~PixelHitClassifier();

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
	    float p;
	    float beta;
	    float gamma_beta;
	    float theta;
	    int n_hit;
	} track_; 

};

//
// constructors and destructor
//
PixelHitClassifier::PixelHitClassifier(const edm::ParameterSet& iConfig):
    tracks_(consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("tracks"))),
    generate_(consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("gen")))
{
    usesResource("TFileService");
    edm::Service<TFileService> fs;
    // we create a ROOT tree 
    treeAll_ = fs->make<TTree>("treeAll","treeAll");

    // now we define each variable in the tree, and give the addess of the C++ variable to read the contents, and the type (I = int, F = float)
    // see https://root.cern.ch/doc/master/classTTree.html

    treeAll_->Branch("mass", &track_.mass, "mass/F");
    treeAll_->Branch("eta", &track_.eta, "eta/F");
    treeAll_->Branch("pt", &track_.pt, "pt/F");
    treeAll_->Branch("p", &track_.p, "p/F");
    treeAll_->Branch("beta", &track_.beta, "beta/F"); 
    treeAll_->Branch("gamma_beta", &track_.gamma_beta, "gamma_beta/F");
    treeAll_->Branch("theta", &track_.theta, "theta/F");
    treeAll_->Branch("signal", &track_.signal, "signal/I");
    treeAll_->Branch("n_hit", &track_.n_hit, "n_hit/I");

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


PixelHitClassifier::~PixelHitClassifier()
{
}

void
PixelHitClassifier::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // 
    // read conditions
    iSetup.get<TrackerTopologyRcd>().get(theTrkTopo);
    iSetup.get<TrackerDigiGeometryRecord>().get(theGeometry);

    // read data
    edm::Handle<std::vector<reco::Track>> tracks;
    iEvent.getByToken(tracks_, tracks);

    // read MC
    edm::Handle<std::vector<reco::GenParticle>> gen_tracks;
    iEvent.getByToken(generate_, gen_tracks);

	
    // loop on tracks 
    for (const reco::Track & track : *tracks) {
	//Initialization of track parameters
	    track_.signal=0; // initialized at 0 (background) 
	    track_.mass=0; 	 
            track_.eta=0;
	    track_.pt=0;
	    track_.p=0;
	    track_.beta=0;
	    track_.gamma_beta=0;
	    track_.n_hit=0;
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
	
	//Initialization of comparators
	float min_angle = 1;  //records the minimal value of the angle difference
	float min_pt = 1;   //records the minimal value of the Pt difference
    
	// loop on MC generated particles   
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

	if (track_.mass != 0)
	{
		track_.beta = 1/sqrt(1+(pow(track_.mass,2)/(pow(track.p(),2))));  		
		track_.gamma_beta = track.p()/track_.mass;	
	}
	track_.eta = track.eta();
	track_.pt = track.pt();
	track_.p = track.p(); 
	track_.theta = track.theta();

	//if (track_.pt<2) // avoids a lot of background 
	//	continue;

	int n=0; //index going through the structure object hit_[n] 
    	// loop on the hits on the track
 	for (unsigned int i = 0, nhits = track.recHitsSize(); i < nhits; ++i) {
	    	const TrackingRecHit *hit = &* track.recHit(i);
		// skip "invalid" hits (markers that the track crossed a detector without yielding a hit)
            	if (!hit->isValid()) continue;
	        // get the id of the module (a unique integer identifying each module in the CMS detector)
                DetId id = hit->geographicalId();
                // skip hits that are not on the pixel detector
                if (id.subdetId() != PixelSubdetector::SubDetector::PixelBarrel && id.subdetId() != PixelSubdetector::SubDetector::PixelEndcap) continue;
		// Identifies layer and detector
		if (n>=6) continue; // avoids the rare events with more than 6 hits that overflow our array 
		hit_[n].detector = id.subdetId();       // will be 1 for barrel and 2 for endcaps, as defined in DataFormats/SiPixelDetId/interface/PixelSubdetector.h                
		hit_[n].layer    = theTrkTopo->layer(id);  // the layer
                // find the C++ object corresponding to this detector module
                const PixelGeomDetUnit* det = dynamic_cast<const PixelGeomDetUnit*>(theGeometry->idToDet(id));
                if (!det) throw cms::Exception("CorruptData", "Missing DetID in geometry?? this is not supposed to happen.");

                // get the pixel topology, i.e. what maps from indices of pixels (integers) to absolute positions on the surface of the pixel module in c
                const PixelTopology& topol = det->specificTopology();

                // convert from the generic hit type to the pixel hit type
                const auto * pixhit = dynamic_cast<const SiPixelRecHit*>(hit->hit()); 
                if (!pixhit) throw cms::Exception("CorruptData", "Valid pixel hit that is not a SiPixelRecHit");
                // get the cluster from the hit
                const SiPixelCluster & cluster = *(pixhit->cluster());
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
	track_.n_hit = n; // records number of hits
        // fill one entry in the tree, reading the values from the variables for which we did the 'Branch' call in the above
	treeAll_->Fill();
     }
}


//define this as a plug-in
DEFINE_FWK_MODULE(PixelHitClassifier);
