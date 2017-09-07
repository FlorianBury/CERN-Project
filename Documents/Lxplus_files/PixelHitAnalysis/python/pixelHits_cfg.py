import FWCore.ParameterSet.Config as cms


from Configuration.StandardSequences.Eras import eras
process = cms.Process("Occupancy",eras.Run2_2017)

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(
           # data files
        '/store/express/Run2017B/ExpressPhysics/FEVT/Express-v1/000/297/178/00000/00179E1E-7055-E711-811C-02163E01283D.root',
        '/store/express/Run2017B/ExpressPhysics/FEVT/Express-v1/000/297/178/00000/0069D1D7-6355-E711-AF34-02163E0143BC.root',
        '/store/express/Run2017B/ExpressPhysics/FEVT/Express-v1/000/297/178/00000/0085E8F2-6F55-E711-A95E-02163E0133F0.root',
        '/store/express/Run2017B/ExpressPhysics/FEVT/Express-v1/000/297/178/00000/00A6F68B-6655-E711-8C52-02163E013555.root'
           # MC files
#'/store/cmst3/user/gpetrucc/SusyWithDeDx2017/GenStau432/HSCPstau_M_432_job1.RECO.root',
#'/store/cmst3/user/gpetrucc/SusyWithDeDx2017/GenStau432/HSCPstau_M_432_job13.RECO.root',
#'/store/cmst3/user/gpetrucc/SusyWithDeDx2017/GenStau432/HSCPstau_M_432_job18.RECO.root',
#'/store/cmst3/user/gpetrucc/SusyWithDeDx2017/GenStau432/HSCPstau_M_432_job3.RECO.root',
#'/store/cmst3/user/gpetrucc/SusyWithDeDx2017/GenStau432/HSCPstau_M_432_job7.RECO.root',
#'/store/cmst3/user/gpetrucc/SusyWithDeDx2017/GenStau432/HSCPstau_M_432_job8.RECO.root',
#'/store/cmst3/user/gpetrucc/SusyWithDeDx2017/GenStau432/HSCPstau_M_432_job9.RECO.root',

#'/store/relval/CMSSW_9_2_2/RelValMinBias_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/56DD9EB2-B24D-E711-A30D-0CC47A7C3424.root',
#'/store/relval/CMSSW_9_2_2/RelValMinBias_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/88BAA6AF-B24D-E711-8D95-0025905A6138.root',
#'/store/relval/CMSSW_9_2_2/RelValMinBias_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/92D4E2EE-A94D-E711-B31C-0CC47A7C34D0.root',
#'/store/relval/CMSSW_9_2_2/RelValMinBias_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/BE41C096-A94D-E711-857E-0CC47A4C8EB0.root',
#'/store/relval/CMSSW_9_2_2/RelValMinBias_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/E05DCD2E-A84D-E711-B6F3-0025905A608C.root',
#'/store/relval/CMSSW_9_2_2/RelValMinBias_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/E2192472-AA4D-E711-A655-0CC47A4D76A2.root',
#'/store/relval/CMSSW_9_2_2/RelValMinBias_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/E4CACF38-A84D-E711-BB85-0025905A60A0.root',
#'/store/relval/CMSSW_9_2_2/RelValMinBias_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/FC3E8AFB-A84D-E711-BE06-0CC47A7C354A.root',
#'/store/relval/CMSSW_9_2_2/RelValTTbar_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/2A644B02-B14D-E711-A7EC-0025905B85AA.root',
#'/store/relval/CMSSW_9_2_2/RelValTTbar_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/3A83D279-B04D-E711-AB5A-003048FFCBB8.root',
#'/store/relval/CMSSW_9_2_2/RelValTTbar_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/561E0BBB-B14D-E711-A8ED-0CC47A7452D8.root',
#'/store/relval/CMSSW_9_2_2/RelValTTbar_13/GEN-SIM-RECO/92X_upgrade2017_realistic_v1-v1/10000/C880B6BD-B14D-E711-A3C5-0CC47A4D767E.root'
	)
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )    

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')  #MC
process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Express_v2', '')    #Data


process.pixelHits = cms.EDAnalyzer("PixelHitOnTrackStudies",
    tracks = cms.InputTag("generalTracks"),
    gen = cms.InputTag("genParticles"),
)

process.occupancy = cms.Path(
    process.pixelHits
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("hits.root"))

