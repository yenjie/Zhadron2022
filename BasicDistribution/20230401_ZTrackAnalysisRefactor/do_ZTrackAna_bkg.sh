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
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackground_v15b/ --Output GraphDataBackground_v15b.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v15b/ --Output GraphMCBackground_v15b.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEUp25_v15b/ --Output GraphDataBackgroundUEUp25_v15b.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp25_v15b/ --Output GraphMCBackgroundUEUp25_v15b.root --Fraction 1
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEDown25_v15b/ --Output OutputDataBackgroundUEDown25_v15b.root --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown25_v15b/ --Output GraphMCBackgroundUEDown25_v15b.root --Fraction 1

else
	echo "Input number exceeded"
fi