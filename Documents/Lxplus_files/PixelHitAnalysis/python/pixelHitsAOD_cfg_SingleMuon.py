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
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/000A8989-6C7E-E711-9151-02163E01192F.root'
'/store/data/Run2015C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/0095BB2B-6C7E-E711-A773-02163E011FC5.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/00997D06-6C7E-E711-A6F8-02163E01A1EC.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/0217DC0E-6C7E-E711-B7E1-02163E01A4A9.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/0260020E-6C7E-E711-B8A5-02163E019BCA.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/0AE70B07-6C7E-E711-9A23-02163E019E5B.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/0E2F520B-6C7E-E711-A2F3-02163E019BA7.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/12FB1E14-6C7E-E711-B3C7-02163E01A556.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/18771F00-6C7E-E711-B14D-02163E014755.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/1E023608-6C7E-E711-AFCF-02163E014766.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/1E88F909-6C7E-E711-8F2E-02163E019E0F.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/2000B605-6C7E-E711-8074-02163E014537.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/22C0A107-6C7E-E711-B392-02163E019BE2.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/24EFD128-6C7E-E711-9A69-02163E01341F.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/28385E18-6C7E-E711-8891-02163E013840.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/2A17F90A-6C7E-E711-81D8-02163E019CC2.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/2A56CC20-6C7E-E711-B121-02163E011E89.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/2C9D5C10-6C7E-E711-A962-02163E014178.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/306D360D-6C7E-E711-A266-02163E01A1D4.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/3085190D-6C7E-E711-8520-02163E01A30A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/32C7E817-6C7E-E711-974C-02163E0133E9.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/36747D09-6C7E-E711-9B51-02163E019D06.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/3693B507-6C7E-E711-8E19-02163E01A650.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/36AC7524-6C7E-E711-A514-02163E013900.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/38CE1411-6C7E-E711-B509-02163E01A6E5.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/3AF4E035-6C7E-E711-907D-02163E01350B.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/4072420F-6C7E-E711-B08F-02163E01A6B1.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/40A7CB0F-6C7E-E711-970A-02163E0145E1.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/448CB703-6C7E-E711-8829-02163E01A1B8.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/4497601D-6C7E-E711-92EB-02163E01471E.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/44F34A0E-6C7E-E711-8842-02163E01A6BC.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/4635DE04-6C7E-E711-9E4D-02163E019E30.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/46689B0F-6C7E-E711-97B7-02163E01A524.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/467B7E0F-6C7E-E711-9754-02163E019E67.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/48C4011E-6C7E-E711-A6AA-02163E0140FA.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/4A01B706-6C7E-E711-B84F-02163E01A5BD.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/4C57DB1B-6C7E-E711-A224-02163E01250D.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/4C733424-6C7E-E711-BDB0-02163E012A12.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/4E04E66B-6C7E-E711-BBD1-02163E014793.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/5251EE0D-6C7E-E711-A3EC-02163E01A4B4.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/541E9600-6C7E-E711-B0EB-02163E0143CB.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/622F4401-6C7E-E711-9824-02163E019B79.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/6A36CA0C-6C7E-E711-9CF9-02163E019E36.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/6C24120C-6C7E-E711-923D-02163E019CBF.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/6CA1EF0B-6C7E-E711-A3E0-02163E01A5DB.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/6CC4D5CB-757E-E711-9008-02163E019CB5.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/6E24120F-6C7E-E711-94C9-02163E012234.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/6E891240-6C7E-E711-8757-02163E013614.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/70BA340D-AE7E-E711-A2E2-02163E019BBE.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/727C2D15-6C7E-E711-AA19-02163E01A4D8.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/72B2420B-6C7E-E711-BE2A-02163E01440A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/7428A10C-6C7E-E711-8193-02163E01A269.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/78A32806-6C7E-E711-A02C-02163E01A575.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/86917819-6C7E-E711-AD7B-02163E012B86.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/8AA1B225-6C7E-E711-8BB1-02163E0139C0.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/8C4B8A01-6C7E-E711-8CCB-02163E0143A4.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/8C857F0E-6C7E-E711-85F3-02163E01A686.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/90D3351A-6C7E-E711-918E-02163E014567.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/9240B512-6C7E-E711-8A38-02163E0142F9.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/946DE413-6C7E-E711-AF6F-02163E013698.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/9C053744-6C7E-E711-84FB-02163E01344C.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/9CD4221B-6C7E-E711-8BEC-02163E01A5D4.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/A294BE09-6C7E-E711-AC62-02163E0145B1.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/A2CCDC12-6C7E-E711-95A4-02163E01A678.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/A2FBF303-6C7E-E711-B0D1-02163E01457D.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/A47C3418-6C7E-E711-925D-02163E0144CA.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/B6D51E13-6C7E-E711-8FF4-02163E019DCB.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/B82B160A-6C7E-E711-9B35-02163E01456A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/B8D0536D-6C7E-E711-8D5E-02163E0137BC.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/BCB78500-6C7E-E711-A927-02163E014769.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/C4713B0B-6C7E-E711-B88E-02163E01A3FE.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/C65A19B4-6D7E-E711-8927-02163E01382B.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/D28CAE19-6C7E-E711-A83B-02163E0136CF.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/D465D107-6C7E-E711-A4CF-02163E0143FC.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/D8568E19-6C7E-E711-94E2-02163E0140F0.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/D88B7D0B-B07E-E711-8DB1-02163E01A26A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/DA46410B-6C7E-E711-A3EC-02163E01A464.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/DE507C0D-6C7E-E711-8557-02163E01A41A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/E0170809-6C7E-E711-82D7-02163E014554.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/E60EED08-6C7E-E711-89AA-02163E01A4E2.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/E6BBD6F9-6B7E-E711-94EF-02163E0143C8.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/EA2B2E2E-6C7E-E711-8E48-02163E0142DF.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/EAE05D03-6C7E-E711-A9B8-02163E019BF8.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F0F11D13-6C7E-E711-8DAC-02163E019E90.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F28D790F-6C7E-E711-AE31-02163E01A74C.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F2F1BB09-6C7E-E711-9E24-02163E01A5D2.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F4B0F108-6C7E-E711-8E5C-02163E01A3F9.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F4B90B94-6D7E-E711-95D0-02163E014454.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F6F12901-6C7E-E711-8427-02163E01470D.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F82A770A-6C7E-E711-AE57-02163E01A409.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F8660E0F-6C7E-E711-B9E7-02163E01A5F5.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/F87B7727-6C7E-E711-8600-02163E014736.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/FC753C0A-6C7E-E711-8D29-02163E01A212.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/777/00000/FCD5F892-717E-E711-8FFF-02163E011923.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/0055599D-7E7E-E711-85A0-02163E01A37E.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/0292C69B-7E7E-E711-894F-02163E014132.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/046D88AC-7E7E-E711-99A7-02163E01346A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/06ADBC86-7E7E-E711-A6C3-02163E01A642.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/08EF28AE-7E7E-E711-A41B-02163E011800.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/12772D9F-7E7E-E711-B516-02163E0126FD.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/1414827E-7E7E-E711-B7A2-02163E01A28B.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/14840A95-7E7E-E711-92EB-02163E01A5E5.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/1AFB7F98-7E7E-E711-AD32-02163E01A708.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/2404B988-7E7E-E711-B02A-02163E0146AE.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/30029C9B-7E7E-E711-BA78-02163E019E02.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/3454A78F-7E7E-E711-8D41-02163E019B21.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/365B0B8C-7E7E-E711-BB06-02163E014150.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/365FCAAF-7E7E-E711-9709-02163E011F56.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/40C9199C-7E7E-E711-9F2A-02163E011DD7.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/44651D8A-7E7E-E711-95D7-02163E01A21D.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/448B5701-7F7E-E711-BB7E-02163E014725.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/469F55BB-7E7E-E711-9A6B-02163E014637.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/4EA9C29B-7E7E-E711-B0BF-02163E01192A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/54B54B83-7E7E-E711-93CA-02163E014163.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/54C62390-7E7E-E711-B775-02163E01A2C2.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/5A1DE19D-7E7E-E711-9AD7-02163E014298.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/62D2FE86-7E7E-E711-951E-02163E019DA0.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/6892F083-7E7E-E711-B030-02163E0145F5.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/68EBE39B-7E7E-E711-A925-02163E0127B8.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/6A3CBC8E-7E7E-E711-B3C9-02163E01A66C.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/6CAB508E-7E7E-E711-80D2-02163E0134F6.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/6CF99A9B-7E7E-E711-8D22-02163E01459A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/6EAC1B89-7E7E-E711-959B-02163E01A273.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/761D678D-7E7E-E711-89E3-02163E019B54.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/86A0F08E-7E7E-E711-AB1C-02163E01A1FE.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/88CC278E-7E7E-E711-BE9D-02163E01366B.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/8A132386-7E7E-E711-8E83-02163E014330.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/8A3E6889-7E7E-E711-981D-02163E01A5DA.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/8CB69ECE-7E7E-E711-BB27-02163E0118B6.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/8EDB08AC-7E7E-E711-AFEF-02163E0139B6.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/8EDB5596-7E7E-E711-A6D8-02163E01A6AC.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/9A5A5D8B-7E7E-E711-B8B6-02163E019E66.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/9E22998D-7E7E-E711-95F8-02163E01A2B8.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/A07A0491-7E7E-E711-B891-02163E01A4B0.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/A2E89B89-7E7E-E711-ACC4-02163E01A479.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/B0D1FA83-7E7E-E711-9162-02163E019E14.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/B281D27B-7F7E-E711-A869-02163E0145AE.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/B42C0BA1-7E7E-E711-BE7B-02163E012528.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/B80E2790-7E7E-E711-B378-02163E014408.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/B8D8EC96-7E7E-E711-B536-02163E01471F.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/C217428A-7E7E-E711-B493-02163E019CC5.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/C281EC98-7E7E-E711-97CA-02163E019E12.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/CE75648F-7E7E-E711-8FC7-02163E01A42B.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/D844C9A6-7E7E-E711-8BCF-02163E011838.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/D8452991-7E7E-E711-9656-02163E01A665.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/D8828584-7E7E-E711-82E5-02163E01A69D.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/DABE54A4-7E7E-E711-A454-02163E01A30E.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/DC5ADE86-7E7E-E711-BCB0-02163E01A34F.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/DEC49388-7E7E-E711-80E9-02163E019B52.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/EC2BB5AB-7E7E-E711-BB8C-02163E01241A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/EC6A7D90-7E7E-E711-B3FC-02163E01A4DF.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/780/00000/F8E511DE-7E7E-E711-9C4C-02163E011E6F.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/14BAA7D1-D382-E711-B3C4-02163E019BB2.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/32FFA089-D382-E711-9F3A-02163E0142D6.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/3486E1E2-D382-E711-9580-02163E01A50A.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/5648B387-D382-E711-96AE-02163E01343D.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/66E5DC92-D382-E711-97EE-02163E01A38F.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/685E507C-D382-E711-8972-02163E01A384.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/6E0EC7EF-D382-E711-89BA-02163E0134CB.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/7C692EB6-D382-E711-A019-02163E01A2E8.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/7E36C4A6-D382-E711-9BEF-02163E019BDB.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/98882605-D482-E711-869B-02163E011DED.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/300/812/00000/F2270F3F-2B83-E711-9F2C-02163E013631.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/301/046/00000/3A02FB20-0E83-E711-B6AF-02163E011BD4.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/301/046/00000/54DF5308-0E83-E711-B9F3-02163E0141F4.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/301/046/00000/560D6DFA-A983-E711-A696-02163E01366D.root'
'/store/data/Run2017C/SingleMuon/AOD/PromptReco-v3/000/301/046/00000/C8B7000A-0E83-E711-9EDC-02163E01A6F0.root'
	)
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )    

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

from Configuration.AlCa.GlobalTag import GlobalTag
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
process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")  
process.triggerResultsFilter.l1tResults = "gtStage2Digis"
process.triggerResultsFilter.throw = False
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")
process.triggerResultsFilter.triggerConditions = cms.vstring('HLT_IsoMu24_v*','HLT_IsoMu27_v*' )


process.pixelHits = cms.EDAnalyzer("PixelHitOnTrackStudiesAOD",
    tracks = cms.InputTag("generalTracks"),
    dedxInfo = cms.InputTag("dedxHitInfo"),
    vertices = cms.InputTag("offlinePrimaryVertices"),
    candidates = cms.InputTag("particleFlow"),
    pfMet = cms.InputTag("pfMet"),
    muons = cms.InputTag("muons"),
    electrons = cms.InputTag("gedGsfElectrons"),
    jets = cms.InputTag("ak4PFchsCorrectedJets"),
    electronRef = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium")
)

jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-301141_13TeV_PromptReco_Collisions17_JSON.txt"
process.source.lumisToProcess = LumiList.LumiList(jsonFile).getVLuminosityBlockRange()

process.occupancy = cms.Path(
    process.triggerResultsFilter +
    process.egmGsfElectronIDSequence +
    process.ak4PFCHSL1FastL2L3ResidualCorrectorChain +
    process.ak4PFchsCorrectedJets +
    process.pixelHits 
)


process.TFileService = cms.Service("TFileService", fileName = cms.string("/afs/cern.ch/work/f/fbury/private/hits_AOD.root"))
process.source.inputCommands = cms.untracked.vstring("keep *", "drop CTPPSPixelClusteredmDetSetVector_ctppsPixelClusters__RECO")  # old verson of CMSSW
