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
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkgUEUp25_v14/ --Output GraphDatabkgUEUp25_v14.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGenUEUp25_v14/ --Output GraphMCbkgGenUEUp25_v14.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp25_v14/ --Output GraphMCBackgroundUEUp25_v14.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkgUEUp30_v14/ --Output GraphDatabkgUEUp30_v14.root --Fraction 1
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGenUEUp30_v14/ --Output GraphMCbkgGenUEUp30_v14.root --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp30_v14/ --Output GraphMCBackgroundUEUp30_v14.root --Fraction 1
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkgUEDown25_v14/ --Output GraphDatabkgUEDown25_v14.root --Fraction 1
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGenUEDown25_v14/ --Output GraphMCbkgGenUEDown25_v14.root --Fraction 1
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown25_v14/ --Output GraphMCBackgroundUEDown25_v14.root --Fraction 1
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkgUEDown30_v14/ --Output GraphDatabkgUEDown30_v14.root --Fraction 1
elif [ $1 -eq 10 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGenUEDown30_v14/ --Output GraphMCbkgGenUEDown30_v14.root --Fraction 1
elif [ $1 -eq 11 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown30_v14/ --Output GraphMCBackgroundUEDown30_v14.root --Fraction 1

else
	echo "Input number exceeded"
fi