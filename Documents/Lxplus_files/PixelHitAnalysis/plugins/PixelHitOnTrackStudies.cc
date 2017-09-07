
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

class PixelHitOnTrackStudies : public edm::one::EDAnalyzer<edm::one::SharedResources> {
    public:
        explicit PixelHitOnTrackStudies(const edm::ParameterSet&);
        ~PixelHitOnTrackStudies();

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
        struct HitOnTrack {
	    float mass; 
            float charge; 
            float charge_norm; 
            float ratio_charge; 
            int detector, layer;
            int nPixel;
            float hit_r, hit_phi, hit_z;
            int hit_sizeX, hit_sizeY;
            float track_eta, track_pt, track_p;
	    float track_energy;
	    float track_beta;
	    float track_gb;
	    float track_theta;
	} hit_; 

};

//
// constructors and destructor
//
PixelHitOnTrackStudies::PixelHitOnTrackStudies(const edm::ParameterSet& iConfig):
    tracks_(consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("tracks"))),
    generate_(consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("gen")))
{
    usesResource("TFileService");
    edm::Service<TFileService> fs;
    // we create a ROOT tree 
    treeAll_ = fs->make<TTree>("treeAll","treeAll");

    // now we define each variable in the tree, and give the addess of the C++ variable to read the contents, and the type (I = int, F = float)
    // see https://root.cern.ch/doc/master/classTTree.html
    treeAll_->Branch("detector", &hit_.detector, "detector/I");
    treeAll_->Branch("mass", &hit_.mass, "mass/F");
    treeAll_->Branch("layer", &hit_.layer, "layer/I");
    treeAll_->Branch("charge", &hit_.charge, "charge/F");
    treeAll_->Branch("charge_norm", &hit_.charge_norm, "charge_norm/F");
    treeAll_->Branch("ratio_charge", &hit_.ratio_charge, "ratio_charge/F");
    treeAll_->Branch("nPixel", &hit_.nPixel, "nPixel/I");
    treeAll_->Branch("hit_r", &hit_.hit_r, "hit_r/F");
    treeAll_->Branch("hit_phi", &hit_.hit_phi, "hit_phi/F");
    treeAll_->Branch("hit_z", &hit_.hit_z, "hit_z/F");
    treeAll_->Branch("hit_sizeX", &hit_.hit_sizeX, "hit_sizeX/I");
    treeAll_->Branch("hit_sizeY", &hit_.hit_sizeY, "hit_sizeY/I" );
    treeAll_->Branch("track_eta", &hit_.track_eta, "track_eta/F");
    treeAll_->Branch("track_pt", &hit_.track_pt, "track_pt/F");
    treeAll_->Branch("track_p", &hit_.track_p, "track_p/F");
    treeAll_->Branch("track_beta", &hit_.track_beta, "track_beta/F"); 
    treeAll_->Branch("track_gb", &hit_.track_gb, "track_gb/F");
    treeAll_->Branch("track_theta", &hit_.track_theta, "tracktheta/F");
}


PixelHitOnTrackStudies::~PixelHitOnTrackStudies()
{
}

void
PixelHitOnTrackStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

	hit_.mass=0; 	//stays 0 if no match to charged and stable
	float min_angle = 1;  //records the minimal value of the angle difference
	float min_pt = 1;   //records the minimal value of the Pt difference
    
	// loop on MC generated particles   
	for (const reco::GenParticle & gptrack : *gen_tracks){
 		if (gptrack.status()!=1 || gptrack.charge()==0)   continue; // selects only the stable, charged ones
		
	 	float diff_angle =  deltaR(track.eta(), track.phi(), gptrack.eta(), gptrack.phi());
		float diff_pt =  std::abs((gptrack.pt()-track.pt())/gptrack.pt());

		// Search for the closest generated particle for the track
	
               if (diff_angle > 0.1)
  			continue;  // the two tracks are not close
  	       if (diff_pt>0.1)
 			continue; // the two tracks have different Pt
		
		if (diff_angle < min_angle && diff_pt < min_pt) //records the minimum value and assign the mass to the track
		{		
			min_angle = diff_angle;
			min_pt = diff_pt;
			hit_.mass = gptrack.mass();	//records the mass for the minimum 
		}  

	 }

	if (hit_.mass == 0) 	continue; 	// not recognized as a charged and stable particle coming from the generated ones

	hit_.track_beta = 1/sqrt((1+(hit_.mass*hit_.mass/(hit_.track_p*hit_.track_p))));  		
	hit_.track_gb = track.p()/hit_.mass;	
	hit_.track_eta = track.eta();
	hit_.track_pt = track.pt();
	hit_.track_p = track.p(); 
	hit_.track_theta = track.theta();
 
 	if (hit_.track_pt<10) 	continue; 	// cut on Pt already applied 
 
    	// loop on the hits on the track
 	for (unsigned int i = 0, nhits = track.recHitsSize(); i < nhits; ++i) {
            	const TrackingRecHit *hit = &* track.recHit(i);
		// skip "invalid" hits (markers that the track crossed a detector without yielding a hit)
            	if (!hit->isValid()) continue;
	        // get the id of the module (a unique integer identifying each module in the CMS detector)
                DetId id = hit->geographicalId();
                // skip hits that are not on the pixel detector
                if (id.subdetId() != PixelSubdetector::SubDetector::PixelBarrel && id.subdetId() != PixelSubdetector::SubDetector::PixelEndcap) continue;

                hit_.detector = id.subdetId();          // will be 1 for barrel and 2 for endcaps, as defined in DataFormats/SiPixelDetId/interface/PixelSubdetector.h
                hit_.layer    = theTrkTopo->layer(id);  // the layer

                // find the C++ object corresponding to this detector module
                const PixelGeomDetUnit* det = dynamic_cast<const PixelGeomDetUnit*>(theGeometry->idToDet(id));
                if (!det) throw cms::Exception("CorruptData", "Missing DetID in geometry?? this is not supposed to happen.");

                // get the pixel topology, i.e. what maps from indices of pixels (integers) to absolute positions on the surface of the pixel module in cm
                const PixelTopology& topol = det->specificTopology();

                // convert from the generic hit type to the pixel hit type
                const auto * pixhit = dynamic_cast<const SiPixelRecHit*>(hit->hit()); 
                if (!pixhit) throw cms::Exception("CorruptData", "Valid pixel hit that is not a SiPixelRecHit");
                // get the cluster from the hit
                const SiPixelCluster & cluster = *(pixhit->cluster());
                // get the charge of the cluster
                hit_.charge = cluster.charge();
                hit_.nPixel = cluster.size();
		// get the normalized charge
		if (hit_.detector==1)  // barrel
			hit_.charge_norm = hit_.charge*std::abs(sin(hit_.track_theta));
		
		if (hit_.detector==2)  // endcaps
			hit_.charge_norm = hit_.charge*std::abs(cos(hit_.track_theta));
		
		// compute the ratio_charge = max_deposit*size/charge_norm
		int  max_deposit=0;
		const auto & pixelADC = cluster.pixelADC();
		int size_ADC = pixelADC.size();
		for (int i=0 ; i<size_ADC ; i++)
		{
			if (max_deposit<pixelADC[i])
				max_deposit = pixelADC[i];
		}
		hit_.ratio_charge = (max_deposit*size_ADC)/hit_.charge_norm;
	    
                // get size (in X and Y) of the cluster
                hit_.hit_sizeX = cluster.sizeX();
                hit_.hit_sizeY = cluster.sizeY();
                // position of the cluster in pixel units
                MeasurementPoint mp(cluster.x(), cluster.y());
                // convert in position of the cluster in the reference frame of the module (in cm)
                LocalPoint lp = topol.localPosition(mp);
                // convert in position of the cluster in the global frame of CMS (in cm)
                GlobalPoint gp = det->surface().toGlobal(lp);
                hit_.hit_r = gp.perp();
                hit_.hit_phi = gp.phi();
                hit_.hit_z = gp.z();
                // fill one entry in the tree, reading the values from the variables for which we did the 'Branch' call in the above
		treeAll_->Fill();
         }  
    }
}


//define this as a plug-in
DEFINE_FWK_MODULE(PixelHitOnTrackStudies);
