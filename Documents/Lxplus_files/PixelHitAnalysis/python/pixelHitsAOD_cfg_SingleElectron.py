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
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/00EC5A2B-6C7E-E711-A9DD-02163E012A6B.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/06011713-6C7E-E711-A040-02163E019BB8.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/0636B50D-6C7E-E711-BEBA-02163E019D63.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/0A3F7711-6C7E-E711-B00B-02163E01A1EA.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/0E5BB710-6C7E-E711-A1A4-02163E01A3D0.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/0E9CF513-6C7E-E711-8442-02163E014494.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/0EBFAA17-AE7E-E711-975E-02163E01A6AE.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/1058E015-6C7E-E711-B556-02163E01A24D.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/129A830B-6C7E-E711-8514-02163E019D59.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/18CA525B-6C7E-E711-93EF-02163E011949.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/1A070366-6D7E-E711-9AC0-02163E0119D5.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/1AB3CC14-6C7E-E711-B826-02163E01A31A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/1AD7830C-6C7E-E711-9CA9-02163E01A1CE.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/1E778615-6C7E-E711-8193-02163E01A794.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/201BCF1C-6C7E-E711-8AC6-02163E01A254.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/20F9223B-6C7E-E711-8A82-02163E012745.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/22DEE3C3-6D7E-E711-8306-02163E013670.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/246F2B9A-6C7E-E711-ADA3-02163E011E43.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/24A13914-6C7E-E711-8C93-02163E019DFF.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/24C8E054-767E-E711-BCE5-02163E01343A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/2A30B431-6C7E-E711-B74F-02163E01A2D9.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/30765423-A27E-E711-93E8-02163E01A1E4.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/3617C22B-6C7E-E711-A3A9-02163E014272.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/3A738648-6C7E-E711-9B49-02163E014235.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/3C1DD11A-6C7E-E711-B9C9-02163E01A507.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/3E3B4C16-6C7E-E711-B678-02163E019B8B.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/44AFE214-6C7E-E711-95A4-02163E014102.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/503A279A-AB7E-E711-8B74-02163E0118F7.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/58FA8517-6C7E-E711-AAA7-02163E019BC9.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/6011F60F-6C7E-E711-8546-02163E01464E.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/60E4AD2A-6C7E-E711-ADE9-02163E0141BA.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/662AA014-6C7E-E711-87ED-02163E01A26A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/6ECB3B16-6C7E-E711-9825-02163E01A508.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/7027531E-6C7E-E711-8A09-02163E01A588.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/706FF781-6C7E-E711-9CDB-02163E014580.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/74016105-6C7E-E711-A6E3-02163E01A5DF.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/74D2201A-6C7E-E711-9E86-02163E01A41D.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/7CF8541C-6C7E-E711-B162-02163E01A48A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/8400E32D-6C7E-E711-85D1-02163E011CF3.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/86F7E7CF-6C7E-E711-915F-02163E011F37.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/8895750C-6C7E-E711-A867-02163E01A247.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/8A24DD5D-6D7E-E711-B1F0-02163E0133CC.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/8A3A301E-6C7E-E711-8F46-02163E01A4EE.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/8AD55913-6C7E-E711-9490-02163E01A68B.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/925DA424-6C7E-E711-9CB0-02163E01A2F2.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/98838B0C-6C7E-E711-AA7C-02163E01A4AF.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/98E5393D-6C7E-E711-A91A-02163E01272A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/A0692C14-6C7E-E711-A84A-02163E01A301.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/AA1CC607-8B7E-E711-9875-02163E019DD3.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/AAD3AB1B-6C7E-E711-B373-02163E01A765.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/B08D5F0C-6C7E-E711-9E92-02163E01A528.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/B0F6D518-6C7E-E711-9D9D-02163E01A66E.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/B6B12206-6C7E-E711-857D-02163E01A633.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/BC454CB0-A87E-E711-976B-02163E01A39A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/BC7C2A87-6C7E-E711-8D3E-02163E014577.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/C41DE636-6C7E-E711-9F60-02163E011D85.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/C4F4860F-6C7E-E711-9673-02163E01A75F.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/C82F3B12-6C7E-E711-A51F-02163E01A2E2.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/CA576A4A-6C7E-E711-8487-02163E0120A1.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/CAB0622B-6C7E-E711-A008-02163E0144A5.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/CC176D17-6C7E-E711-AEB6-02163E019BAE.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/CC228918-6C7E-E711-9678-02163E01A36B.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/CC302622-6C7E-E711-8DEC-02163E01191D.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/D0317F28-6C7E-E711-81E3-02163E01429A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/D2600616-6C7E-E711-89A9-02163E019C1C.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/D411111C-6C7E-E711-9B6C-02163E01A662.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/D4DD0916-6C7E-E711-9CC5-02163E01A5D3.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/DA43BC10-6C7E-E711-BC14-02163E01A2EA.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/DC164823-6C7E-E711-96CA-02163E01A1ED.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/DEB0C919-6C7E-E711-8FFC-02163E019C0D.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/E008FD31-6C7E-E711-977B-02163E013939.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/E0DDA93C-6C7E-E711-B5D3-02163E013462.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/E0E37925-6C7E-E711-A31C-02163E01274B.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/E2872D3A-6C7E-E711-A360-02163E014421.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/E403FF35-6C7E-E711-8465-02163E01461A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/E4CCEB07-6C7E-E711-B39D-02163E0143B2.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/E83A6C15-6C7E-E711-AF8F-02163E01A2F3.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/E87CC416-6C7E-E711-AE39-02163E014211.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/F42BB7BD-717E-E711-A649-02163E011C03.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/777/00000/F8B74F0E-6C7E-E711-9E81-02163E019DB9.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/02AAA8D8-7E7E-E711-A1C0-02163E013397.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/02EB8C9A-7E7E-E711-9F48-02163E01A6F5.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/124D489F-7E7E-E711-BC64-02163E01A4A7.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/162E71AA-7E7E-E711-8CC4-02163E01A5DE.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/1C2B50AF-7E7E-E711-BF80-02163E0134EB.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/1C3F80A7-7E7E-E711-A905-02163E019BA6.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/20655A11-7F7E-E711-BAD3-02163E0133A4.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/28F8DCA3-B57E-E711-9FDE-02163E014217.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/3613C49D-7E7E-E711-B3B5-02163E0141D2.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/3CAF8322-7F7E-E711-9ED0-02163E011BE9.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/3EE6E893-7E7E-E711-ADE5-02163E01453A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/424ADD9B-7E7E-E711-BB25-02163E019DAE.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/443EE7B6-817E-E711-AF66-02163E0137DF.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/50B912AD-7E7E-E711-B95A-02163E01A6AA.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/5837998C-7E7E-E711-AACB-02163E0143A9.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/5EB77692-7E7E-E711-A753-02163E014480.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/5ED6EBC6-7E7E-E711-91AE-02163E0134C9.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/64CF9D2C-867E-E711-B202-02163E012943.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/70371C97-7E7E-E711-8C93-02163E01A245.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/7833A1C2-7E7E-E711-9BE1-02163E013527.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/7A49E999-7E7E-E711-99BC-02163E019BD3.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/7AAD0043-D27E-E711-9CB6-02163E0137F6.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/7E12B69B-7E7E-E711-B371-02163E01A6C3.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/84D5337F-AE7E-E711-8FC7-02163E01451D.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/86ED0299-7E7E-E711-9D97-02163E014654.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/92D5E5AD-7E7E-E711-9ECF-02163E011E35.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/989B919A-7E7E-E711-B9BB-02163E01A47C.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/9C263C98-7E7E-E711-B2F3-02163E019BA9.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/9C6D23BA-7E7E-E711-B663-02163E01399E.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/9EAF4194-7E7E-E711-9B0A-02163E01A78C.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/A0B90AE2-7E7E-E711-8F1C-02163E011A18.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/AC223D9A-7E7E-E711-9289-02163E01A272.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/ACFB6C9B-7E7E-E711-A455-02163E019C8D.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/B0AB5B3B-227F-E711-B319-02163E0144B4.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/B2486F96-7E7E-E711-8B4C-02163E01A49B.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/C09E321C-AE7E-E711-8CE6-02163E011D31.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/C8866BA0-7E7E-E711-88D2-02163E01A444.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/CA74CA9C-7E7E-E711-9489-02163E01A1DC.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/D0276DBE-7E7E-E711-9178-02163E011A02.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/D07E389C-7E7E-E711-87E2-02163E019CDA.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/D65912A5-7E7E-E711-8739-02163E0121E8.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/D85722B3-7E7E-E711-BE41-02163E014118.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/D885299C-7E7E-E711-8C21-02163E01A58D.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/DC5D05D5-7E7E-E711-96C3-02163E01292F.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/F62E2F93-7E7E-E711-90CD-02163E01A5F9.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/F8FBD4A0-7E7E-E711-8824-02163E019DFB.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/FAC3E9A3-7E7E-E711-BA6B-02163E019DD4.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/FC31C99A-7E7E-E711-8E20-02163E01A312.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/780/00000/FE022EB3-7E7E-E711-A91B-02163E01360A.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/00A0658A-D182-E711-A09F-02163E011FA1.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/46B368CE-D182-E711-9CAD-02163E0146DD.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/5E00454C-D182-E711-8290-02163E0143A7.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/7279B067-D182-E711-BCA0-02163E013768.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/9A692580-D182-E711-84C9-02163E01A583.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/BE2B3D87-D182-E711-A108-02163E011F06.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/C06B2A99-D182-E711-B550-02163E01A53D.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/CA694C7E-D182-E711-89D3-02163E01A5B5.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/300/812/00000/E40F2851-D182-E711-9DE7-02163E0143FF.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/301/046/00000/36F7E40E-0E83-E711-A464-02163E011A80.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/301/046/00000/72F9D43A-0E83-E711-8AF6-02163E011BF0.root'
'/store/data/Run2017C/SingleElectron/AOD/PromptReco-v3/000/301/046/00000/8A465258-0E83-E711-AB14-02163E013913.root'


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
process.triggerResultsFilter.triggerConditions = cms.vstring('HLT_Ele35_WPTight_Gsf_v*' )


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
