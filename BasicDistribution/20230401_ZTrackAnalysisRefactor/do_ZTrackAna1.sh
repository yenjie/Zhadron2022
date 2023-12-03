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
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPDataSigBkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPDataSigBkg_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCSigBkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMCSigBkg_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataSigBkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSigBkg_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCSigBkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSigBkg_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp1000_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEUp1000_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown1000_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEDown1000_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp500_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEUp500_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown500_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphtMCBackgroundUEDown500_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenSigBkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCGenSigBkg_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown100_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEDown100_v17_PFmuon.root --Fraction 1
else
	echo "Input number exceeded"
fi