import FWCore.ParameterSet.Config as cms

process = cms.Process("runRivetAnalysis")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)
process.source = cms.Source("PoolSource",
    #skipEvents = cms.untracked.uint32(930),
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Summer12_DR53X/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/GEN-SIM-RECODEBUG/PU_S10_START53_V7A-v1/0000/000E161B-D5F3-E111-9CAB-003048C69408.root')
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Fall13/QCD_Pt-50to80_TuneZ2star_13TeV_pythia6/GEN-SIM/POSTLS162_V1-v1/00000/02F7711E-FF4B-E311-A8BD-0002C90A37CA.root')
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Spring14dr/QCD_Pt-50to80_Tune4C_13TeV_pythia8/GEN-SIM-RAW/castor_Flat0to10_POSTLS170_V5-v1/00000/0087DDB9-C012-E411-B8AC-0025905A60D0.root')
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Spring14dr/QCD_Pt-50to80_MuEnrichedPt5_Tune4C_13TeV_pythia8/GEN-SIM-RAW/Flat20to50_POSTLS170_V5-v1/00000/088AC9E8-67DC-E311-9F5F-848F69FD454D.root')
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Summer12/QCD_Pt-50to80_Tune4C_8TeV_pythia8/GEN-SIM/START50_V13-v1/0000/001ED0E4-5B57-E111-BC8B-485B39800C1D.root')
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Summer12_DR53X/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/AODSIM/PU25bx25_START53_V19D-v1/20000/0012AFC9-5ECD-E211-87F4-90E6BA442F13.root')
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Summer12_DR53X/QCD_Pt-15to3000_TuneEE3C_Flat_8TeV_herwigpp/AODSIM/PU_S10_START53_V7A-v1/00000/02088915-F613-E211-920A-00304867902E.root')
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Summer12_DR53X/QCD_Pt-15to3000_TuneEE3C_Flat_8TeV_herwigpp/AODSIM/PU_S10_START53_V7A-v1/00000/001A0DC8-C313-E211-BCCB-00261894397B.root')
    #fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Summer12_DR53X/TT_CT10_AUET2_8TeV-powheg-herwig/AODSIM/PU_S10_START53_V19-v1/10000/007C2BC5-C5CA-E211-B4D1-003048679188.root')
    fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/Summer12_DR53X/TTJets_MSDecays_central_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V19-v1/00000/0037BFA7-D943-E311-8FA3-00266CF9C018.root')
)

process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("GeneratorInterface.RivetInterface.genParticles2HepMC_cfi")

process.rivetAnalyzer.AnalysisNames = cms.vstring('BTAG_JET_TRACK_SEL')

#process.p = cms.Path(process.rivetAnalyzer)
process.p = cms.Path(process.generator*process.rivetAnalyzer)
