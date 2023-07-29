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
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSignal_v16-1.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackground_v15c/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackground_v15c-1.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignal_v16-1.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v15c/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackground_v15c-1.root --Fraction 1
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMC_v16-1.root --IgnoreCentrality true --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMC0Sub_v16-1.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignalGen_v16-1.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignalGen0Sub_v16-1.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v15c/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundGen_v15c-1.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v15c/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundGen0Sub_v15c-1.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 10 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMCGen_v16-1.root --IgnoreCentrality true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 11 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMCGen0Sub_v16-1.root --IgnoreCentrality true  --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 12 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignal0Sub_v16-1.root --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 13 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPData_v16/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPData_v16-1.root --IgnoreCentrality true --Fraction 1
elif [ $1 -eq 14 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEUp25_v15c/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackgroundUEUp25_v15c-1.root --Fraction 1
elif [ $1 -eq 15 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp25_v15c/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEUp25_v15c-1.root --Fraction 1
elif [ $1 -eq 16 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEDown25_v15c/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackgroundUEDown25_v15c-1.root --Fraction 1
elif [ $1 -eq 17 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown25_v15c/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEDown25_v15c-1.root --Fraction 1
else
	echo "Input number exceeded"
fi