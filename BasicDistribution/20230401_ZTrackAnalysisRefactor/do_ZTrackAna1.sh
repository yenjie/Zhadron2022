#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_12_5_2_patch1/src

cd $CMSSWDir

cmsenv

source /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/SetupAnalysis.sh

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230401_ZTrackAnalysisRefactor

mkdir -p log

if [ $1 -eq 0 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataLoose_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSignalLoose_v16-1.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataTight_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSignalTight_v15c-1.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCLoose_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignalLoose_v16-1.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCTight_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignalTight_v15c-1.root --Fraction 1
else
	echo "Input number exceeded"
fi