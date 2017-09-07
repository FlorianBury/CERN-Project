import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList

from Configuration.StandardSequences.Eras import eras
process = cms.Process("Occupancy",eras.Run2_2017)

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(
		)
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )    

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

from Configuration.AlCa.GlobalTag import GlobalTag
#GlobalTag(process.GlobalTag, '92X_upgrade2017_realistic_v7', '') #minbias
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')  #MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Express_v2', '')    #Data
GlobalTag(process.GlobalTag, '92X_dataRun2_Prompt_v7', '') #Data

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process, DataFormat.AOD)
setupAllVIDIdsInModule(process, "RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff", setupVIDElectronSelection)

process.load('JetMETCorrections.Configuration.JetCorrectors_cff')
process.ak4PFchsCorrectedJets   = cms.EDProducer('CorrectedPFJetProducer',
	src         = cms.InputTag('ak4PFJetsCHS'),
        correctors  = cms.VInputTag('ak4PFCHSL1FastL2L3ResidualCorrector')
)

#Trigger slection
#process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")  
#process.triggerResultsFilter.l1tResults = "gtStage2Digis"
#process.triggerResultsFilter.throw = False
#process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")
#process.triggerResultsFilter.triggerConditions = cms.vstring('HLT_IsoMu24_v*','HLT_IsoMu27_v*' )


process.pixelHits = cms.EDAnalyzer("PixelHitOnTrackStudiesAOD",
    tracks = cms.InputTag("generalTracks"),
    dedxInfo = cms.InputTag("dedxHitInfo"),
    vertices = cms.InputTag("offlinePrimaryVertices"),
    candidates = cms.InputTag("particleFlow"),
    pfMet = cms.InputTag("pfMet"),
    gen = cms.InputTag("genParticles"),
    muons = cms.InputTag("muons"),
    electrons = cms.InputTag("gedGsfElectrons"),
    jets = cms.InputTag("ak4PFchsCorrectedJets"),
    electronRef = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium")
)

#jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-301141_13TeV_PromptReco_Collisions17_JSON.txt"
#process.source.lumisToProcess = LumiList.LumiList(jsonFile).getVLuminosityBlockRange()

process.occupancy = cms.Path(
#    process.triggerResultsFilter +
    process.egmGsfElectronIDSequence +
    process.ak4PFCHSL1FastL2L3ResidualCorrectorChain +
    process.ak4PFchsCorrectedJets +
    process.pixelHits 
)


process.TFileService = cms.Service("TFileService", fileName = cms.string("/afs/cern.ch/work/f/fbury/private/hits_AOD.root"))
process.source.inputCommands = cms.untracked.vstring("keep *", "drop CTPPSPixelClusteredmDetSetVector_ctppsPixelClusters__RECO")  # old verson of CMSSW
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange("299649:151-299649:228", "299649:230-299649:332") #Data (select when detector fully functioning)
