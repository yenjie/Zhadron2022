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
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_v14/ --Output GraphDataSignal_v14.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_v14/ --Output GraphDataBackground_v14.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v14/ --Output GraphMCSignal_v14.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v14/ --Output GraphMCBackground_v14.root --Fraction 1
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v14/ --Output GraphPPMC_v14.root --IgnoreCentrality true --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v14/ --Output GraphPPMC0Sub_v14.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v14/ --Output GraphMCSignalGen_v14.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v14/ --Output GraphMCSignalGen0Sub_v14.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_v14/ --Output GraphMCBackgroundGen_v14.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_v14/ --Output GraphMCBackgroundGen0Sub_v14.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 10 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v14/ --Output GraphPPMCGen_v14.root --IgnoreCentrality true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 11 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v14/ --Output GraphPPMCGen0Sub_v14.root --IgnoreCentrality true  --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 12 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v14/ --Output GraphMCSignal0Sub_v14.root --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 13 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPData_v14/ --Output GraphPPData_v14.root --IgnoreCentrality true --Fraction 1
else
	echo "Input number exceeded"
fi