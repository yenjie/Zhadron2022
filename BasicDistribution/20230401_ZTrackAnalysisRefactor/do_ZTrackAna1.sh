#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_13_2_3/src

cd $CMSSWDir

cmsenv

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/

source /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/SetupAnalysis.sh

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230401_ZTrackAnalysisRefactor

mkdir -p log

if [ $1 -eq 0 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataSigBkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSigBkg_v17_PFmuon.root --Fraction 1
#elif [ $1 -eq 1 ]
#then
#	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown100_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEDown100_v17_PFmuon.root --Fraction 1
#elif [ $1 -eq 2 ]
#then
#	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp200_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEUp200_v17_PFmuon.root --Fraction 1
#elif [ $1 -eq 3 ]
#then
#	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown200_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEDown200_v17_PFmuon.root --Fraction 1
else
	echo "Input number exceeded"
fi