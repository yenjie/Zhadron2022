#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_13_2_3/src

cd $CMSSWDir

cmsenv

source /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/SetupAnalysis.sh

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230401_ZTrackAnalysisRefactor

mkdir -p log

if [ $1 -eq 0 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputData_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphDataSignal_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputDataBackground_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphDataBackground_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMC_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCSignal_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCBackground_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCBackground_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputPPMC_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphPPMC_v17_PFmuon.root --IgnoreCentrality true --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputPPMC_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphPPMC0Sub_v17_PFmuon.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCGen_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCSignalGen_v17_PFmuon.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCGen_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCSignalGen0Sub_v17_PFmuon.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCGenbkg_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCBackgroundGen_v17_PFmuon.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCGenbkg_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCBackgroundGen0Sub_v17_PFmuon.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 10 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputPPMCGen_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphPPMCGen_v17_PFmuon.root --IgnoreCentrality true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 11 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputPPMCGen_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphPPMCGen0Sub_v17_PFmuon.root --IgnoreCentrality true  --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 12 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMC_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCSignal0Sub_v17_PFmuon.root --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 13 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputPPData_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphPPData_v17_PFmuon.root --IgnoreCentrality true --Fraction 1
elif [ $1 -eq 14 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputDataBackgroundUEUp25_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphDataBackgroundUEUp25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 15 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCBackgroundUEUp25_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCBackgroundUEUp25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 16 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputDataBackgroundUEDown25_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphDataBackgroundUEDown25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 17 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCBackgroundUEDown25_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCBackgroundUEDown25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 18 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputDataLoose_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphDataSignalLoose_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 19 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputDataTight_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphDataSignalTight_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 20 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCLoose_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCSignalLoose_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 21 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputMCTight_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/GraphMCSignalTight_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 22 ]
then
	./Execute --InputBase /eos/home-p/pchou/OutputDataSigBkg_v17_PFmuon/ --Output /eos/home-p/pchou/BasicPlots/OutputDataSigBkg_v17_PFmuon.root --Fraction 1
else
	echo "Input number exceeded"
fi