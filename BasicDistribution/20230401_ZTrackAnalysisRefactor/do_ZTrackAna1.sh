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
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackground_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackground_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackground_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundGen_v17_PFmuon.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundGen0Sub_v17_PFmuon.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEUp25_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackgroundUEUp25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp25_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEUp25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEDown25_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackgroundUEDown25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown25_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEDown25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEUp30_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackgroundUEUp30_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp30_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEUp30_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 10 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEDown30_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackgroundUEDown30_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 11 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown30_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEDown30_v17_PFmuon.root --Fraction 1
else
	echo "Input number exceeded"
fi