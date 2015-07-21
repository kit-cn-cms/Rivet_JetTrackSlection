from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'MC_Powheg_Herwig_TT_CT10_AUET2_8TeV'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/nfs/dust/cms/user/shwillia/CMSSW_7_4_0_pre8/src/GeneratorInterface/RivetInterface/test/runRivetAnalyzer_cfg.py'
config.JobType.outputFiles = ['BTAG_JET_TRACK_SEL.yoda']

config.section_("Data")
config.Data.inputDataset = '/TT_CT10_AUET2_8TeV-powheg-herwig/Summer12_DR53X-PU_S10_START53_V19-v1/AODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = False
config.Data.totalUnits = 100
#config.Data.publishDbsUrl = 'phys03'
#config.Data.publishDataName = 'CRAB3_tutorial_MC_analysis_test1'

config.section_("Site")
config.Site.storageSite = 'T2_DE_DESY'

