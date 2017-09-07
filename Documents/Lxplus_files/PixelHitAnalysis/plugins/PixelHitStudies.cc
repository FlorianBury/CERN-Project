
// system include files
#include <memory>
#include <cmath>

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


class PixelHitStudies : public edm::one::EDAnalyzer<edm::one::SharedResources> {
    public:
        explicit PixelHitStudies(const edm::ParameterSet&);
        ~PixelHitStudies();

    private:
        virtual void analyze(const edm::Event&, const edm::EventSetup&);

        // token that we use to get the data (in this case, pixel clusters) from the event
        const edm::EDGetTokenT<edmNew::DetSetVector<SiPixelCluster>> pixelClusterLabel_;

        // TrackerTopology: something that maps detector ids into logical arrangements within the detctor (e.g. which subdetector, layer, ...)
        edm::ESHandle<TrackerTopology> theTrkTopo;
        // TrackerGeometry: contains C++ objects for each detector telling how they are arranged geometrically in space (i.e. precise position and orientation of each module)
        edm::ESHandle<TrackerGeometry> theGeometry;

        // output ROOT tree for all hits
        TTree *treeAll_;
        // define a structure to hold variables about a hit to be put in the tree
        struct HitOffTrack {
            float charge; 
            int detector, layer;
            int nPixel;
            float hit_r, hit_phi, hit_z;
	    int hit_sizeX, hit_sizeY;
        } hit_;

};

//
// constructors and destructor
//
PixelHitStudies::PixelHitStudies(const edm::ParameterSet& iConfig):
    pixelClusterLabel_(consumes<edmNew::DetSetVector<SiPixelCluster>>(iConfig.getParameter<edm::InputTag>("pixelClusters")))
{
    usesResource("TFileService");
    edm::Service<TFileService> fs;
    // we create a ROOT tree 
    treeAll_ = fs->make<TTree>("treeAll","treeAll");

    // now we define each variable in the tree, and give the addess of the C++ variable to read the contents, and the type (I = int, F = float)
    // see https://root.cern.ch/doc/master/classTTree.html
    treeAll_->Branch("detector", &hit_.detector, "detector/I");
    treeAll_->Branch("layer", &hit_.layer, "layer/I");
    treeAll_->Branch("charge", &hit_.charge, "charge/F");
    treeAll_->Branch("nPixel", &hit_.nPixel, "nPixel/I");
    treeAll_->Branch("hit_r", &hit_.hit_r, "hit_r/F");
    treeAll_->Branch("hit_phi", &hit_.hit_phi, "hit_phi/F");
    treeAll_->Branch("hit_z", &hit_.hit_z, "hit_z/F");
    treeAll_->Branch("hit_sizeX", &hit_.hit_sizeX, "hit_sizeX/I");
    treeAll_->Branch("hit_sizeY", &hit_.hit_sizeY, "hit_sizeY/I" );
}


PixelHitStudies::~PixelHitStudies()
{
}

void
PixelHitStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // read conditions
    iSetup.get<TrackerTopologyRcd>().get(theTrkTopo);
    iSetup.get<TrackerDigiGeometryRecord>().get(theGeometry);

    // read data
    edm::Handle<edmNew::DetSetVector<SiPixelCluster> > pixelClusters; 
    iEvent.getByToken(pixelClusterLabel_, pixelClusters); 

    // loop on detsets (collections of hits on a single pixel detector module)
    for (const auto & detset : *pixelClusters) {
        // get the id of the module (a unique integer identifying each module in the CMS detector)
        DetId id(detset.detId());
        hit_.detector = id.subdetId();          // will be 1 for barrel and 2 for endcaps, as defined in DataFormats/SiPixelDetId/interface/PixelSubdetector.h
        hit_.layer    = theTrkTopo->layer(id);  // the layer

        // find the C++ object corresponding to this detector module
        const PixelGeomDetUnit* det = dynamic_cast<const PixelGeomDetUnit*>(theGeometry->idToDet(id));
        if (!det) throw cms::Exception("CorruptData", "Missing DetID in geometry?? this is not supposed to happen.");

        // get the pixel topology, i.e. what maps from indices of pixels (integers) to absolute positions on the surface of the pixel module in cm
        const PixelTopology& topol = det->specificTopology();

        // now do a loop on the clusters on this detector
        for (const SiPixelCluster & cluster : detset) { 
            // start filling the information
            // documentation of the cluster class: http://cmsdoxygen.web.cern.ch/cmsdoxygen/CMSSW_9_2_3_patch2/doc/html/da/dc9/classSiPixelCluster.html
            // get the charge of the cluster
            hit_.charge = cluster.charge();
            hit_.nPixel = cluster.size();
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
DEFINE_FWK_MODULE(PixelHitStudies);
