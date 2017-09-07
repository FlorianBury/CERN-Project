import FWCore.ParameterSet.Config as cms


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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )    

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')  #MC
#process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Express_v2', '')    #Data


process.pixelHits = cms.EDAnalyzer("TrackDecay",
    tracks = cms.InputTag("generalTracks"),
    gen = cms.InputTag("genParticles"),
)

process.occupancy = cms.Path(
    process.pixelHits
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("hits.root"))

