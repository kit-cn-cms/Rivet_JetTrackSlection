#!/bin/bash

#INDIR=/pnfs/desy.de/cms/tier2/store/user/shwillia
INDIR=/nfs/dust/cms/user/shwillia/BTV/Apr15
OUTDIR=/nfs/dust/cms/user/shwillia/BTV/Apr15

#./mergeSample.sh $INDIR/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/crab_MC_Pythia6_QCD_Pt-50to80_TuneZ2star_8TeV/150402_122104/0000 $OUTDIR MC_Pythia6_QCD_Pt-50to80_TuneZ2star_8TeV
#./mergeSample.sh $INDIR/QCD_Pt-50to80_Tune4C_8TeV_pythia8/crab_MC_Pythia8_QCD_Pt-50to80_Tune4C_8TeV/150402_121711/0000 $OUTDIR MC_Pythia8_QCD_Pt-50to80_Tune4C_8TeV
#./mergeSample.sh $INDIR/QCD_Pt_50to80_CTEQ6L1_8TeV_herwig6/crab_MC_Herwig6_QCD_Pt-50to80_Tune4C_8TeV/150402_120929/0000 $OUTDIR MC_Herwig6_QCD_Pt-50to80_Tune4C_8TeV
#./mergeSample.sh $INDIR/QCD_Pt-50To150_bEnriched_TuneZ2star_8TeV-pythia6-evtgen/crab_MC_Pythia6_EvtGen_QCD_Pt-50To150_bEnriched_TuneZ2star_8TeV/150402_120909/0000 $OUTDIR MC_Pythia6_EvtGen_QCD_Pt-50To150_bEnriched_TuneZ2star_8TeV
#./mergeSample.sh $INDIR/QCD4Jets_Pt-100to180_TuneZ2Star_8TeV-alpgen/crab_MC_AlpGen_QCD4Jets_Pt-100to180_TuneZ2Star_8TeV/150402_120701/0000 $OUTDIR MC_AlpGen_QCD4Jets_Pt-100to180_TuneZ2Star_8TeV
#
#./mergeSample.sh $INDIR/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/crab_MC_Pythia6_QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV/150402_121529/0000 $OUTDIR MC_Pythia6_QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_8TeV
#
#./mergeSample.sh $INDIR/QCD_Pt-50to80_TuneZ2star_13TeV_pythia6/crab_MC_Pythia6_QCD_Pt-50to80_TuneZ2star_13TeV/150402_122034 $OUTDIR MC_Pythia6_QCD_Pt-50to80_TuneZ2star_13TeV 
#./mergeSample.sh $INDIR/QCD_Pt-15to30_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-15to30_Tune4C_13TeV/150402_120816/0000 $OUTDIR MC_Pythia8_QCD_Pt-15to30_Tune4C_13TeV
#./mergeSample.sh $INDIR/QCD_Pt-30to50_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-30to50_Tune4C_13TeV/150402_120847/0000 $OUTDIR MC_Pythia8_QCD_Pt-30to50_Tune4C_13TeV
#./mergeSample.sh $INDIR/QCD_Pt-50to80_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-50to80_Tune4C_13TeV/150402_121559/0000 $OUTDIR MC_Pythia8_QCD_Pt-50to80_Tune4C_13TeV
#./mergeSample.sh $INDIR/QCD_Pt-80to120_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-80to120_Tune4C_13TeV/150402_122159/0000 $OUTDIR MC_Pythia8_QCD_Pt-80to120_Tune4C_13TeV 
#./mergeSample.sh $INDIR/QCD_Pt-120to170_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-120to170_Tune4C_13TeV/150402_120722/0000 $OUTDIR MC_Pythia8_QCD_Pt-120to170_Tune4C_13TeV
#
#./mergeSample.sh $INDIR/QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_13TeV_pythia6/crab_MC_Pythia6_QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_13TeV/150402_121506/0000 $OUTDIR MC_Pythia6_QCD_Pt-50to80_MuEnrichedPt5_TuneZ2star_13TeV
#./mergeSample.sh $INDIR/QCD_Pt-50to80_MuEnrichedPt5_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-50to80_MuEnrichedPt5_Tune4C_13TeV/150402_121354/0000 $OUTDIR MC_Pythia8_QCD_Pt-50to80_MuEnrichedPt5_Tune4C_13TeV
#./mergeSample.sh $INDIR/QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV/150402_121112/0000 $OUTDIR MC_Pythia8_QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV
#
#./mergeSample.sh $INDIR/QCD_Pt-50to80_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-50to80_Tune4C_13TeV_Phys14/150402_121625/0000 $OUTDIR MC_Pythia8_QCD_Pt-50to80_Tune4C_13TeV_Phys14
#./mergeSample.sh $INDIR/QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_pythia8/crab_MC_Pythia8_QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_Phys14/150402_121324/0000 $OUTDIR MC_Pythia8_QCD_Pt-50to80_MuEnrichedPt5_PionKaonDecay_Tune4C_13TeV_Phys14

#./mergeSample.sh $INDIR/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola $OUTDIR MC_MadGraph_TTJets_MassiveBinDECAY_TuneZ2star_8TeV
#./mergeSample.sh $INDIR/TT_CT10_TuneZ2star_8TeV-powheg-tauola $OUTDIR MC_Powheg_TT_CT10_TuneZ2star_8TeV
./mergeSample.sh $INDIR/TT_CT10_AUET2_8TeV-powheg-herwig $OUTDIR MC_Powheg_Herwig_TT_CT10_AUET2_8TeV
#./mergeSample.sh $INDIR/TT_8TeV-mcatnlo $OUTDIR MC_MCatNLO_TT_8TeV
#./mergeSample.sh $INDIR/TTJets_TuneCUETP8M1_8TeV-amcatnloFXFX-pythia8 $OUTDIR MC_aMCatNLO_TTbarH_M-125_13TeV_PHYS14
#./mergeSample.sh $INDIR/TTJets_SemiLeptDecays_8TeV-sherpa $OUTDIR MC_Sherpa_TTJets_SemiLeptDecays_8TeV
#./mergeSample.sh $INDIR/TTJets_DileptDecays_8TeV-sherpa $OUTDIR MC_Sherpa_TTJets_DiLeptDecays_8TeV
