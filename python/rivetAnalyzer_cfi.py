import FWCore.ParameterSet.Config as cms

rivetAnalyzer = cms.EDAnalyzer('RivetAnalyzer',
  AnalysisNames = cms.vstring('BTAG_JET_TRACK_SEL'),
  HepMCCollection = cms.InputTag('generator'),
  UseExternalWeight = cms.bool(False),
  GenEventInfoCollection = cms.InputTag('generator'),
  CrossSection = cms.double(1000),
  DoFinalize = cms.bool(True),
  ProduceDQMOutput = cms.bool(False),
  #OutputFile = cms.string('/nfs/dust/cms/user/shwillia/CMSSW_7_4_0_pre8/src/GeneratorInterface/RivetInterface/data/BTAG_JET_TRACK_SEL.yoda')
  OutputFile = cms.string('BTAG_JET_TRACK_SEL.yoda')
)
