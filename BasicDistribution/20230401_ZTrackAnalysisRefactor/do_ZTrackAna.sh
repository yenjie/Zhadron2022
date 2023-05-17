#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_12_5_2_patch1/src

cd $CMSSWDir

cmsenv

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022

. SetupAnalysis.sh

cd BasicDistribution/20230401_ZTrackAnalysisRefactor

mkdir -p log

if [ $1 -eq 0 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_v9/ --Output GraphDataSignal_v9.root --Fraction 1  > log/GraphDataSignal_v9.out 2> log/GraphDataSignal_v9.err < /dev/null &
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_v9/ --Output GraphDataBackground_v9.root --Fraction 1  > log/GraphDataBackground_v9.out 2> log/GraphDataBackground_v9.err < /dev/null &
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v9/ --Output GraphMCSignal_v9.root --Fraction 1  > log/GraphMCSignal_v9.out 2> log/GraphMCSignal_v9.err < /dev/null &
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v9/ --Output GraphMCBackground_v9.root --Fraction 1  > log/GraphMCBackground_v9.out 2> log/GraphMCBackground_v9.err < /dev/null &
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v9/ --Output GraphPPMC_v9.root --IgnoreCentrality true --Fraction 1  > log/GraphPPMC_v9.out 2> log/GraphPPMC_v9.err < /dev/null &
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v9/ --Output GraphPPMC0Sub_v9.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1  > log/GraphPPMC0Sub_v9.out 2> log/GraphPPMC0Sub_v9.err < /dev/null &
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v9/ --Output GraphMCSignalGen_v9.root --Fraction 1 --DoGenCorrelation true  > log/GraphMCSignalGen_v9.out 2> log/GraphMCSignalGen_v9.err < /dev/null &
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v9/ --Output GraphMCSignalGen0Sub_v9.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true  > log/GraphMCSignalGen0Sub_v9.out 2> log/GraphMCSignalGen0Sub_v9.err < /dev/null &
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_v9/ --Output GraphMCBackgroundGen_v9.root --Fraction 1 --DoGenCorrelation true  > log/GraphMCBackgroundGen_v9.out 2> log/GraphMCBackgroundGen_v9.err < /dev/null &
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_v9/ --Output GraphMCBackgroundGen0Sub_v9.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true  > log/GraphMCBackgroundGen0Sub_v9.out 2> log/GraphMCBackgroundGen0Sub_v9.err < /dev/null &
elif [ $1 -eq 10 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v9/ --Output GraphPPMCGen_v9.root --IgnoreCentrality true --Fraction 1 --DoGenCorrelation true  > log/GraphPPMCGen_v9.out 2> log/GraphPPMCGen_v9.err < /dev/null &
elif [ $1 -eq 11 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v9/ --Output GraphPPMCGen0Sub_v9.root --IgnoreCentrality true  --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true  > log/GraphPPMCGen_v9.out 2> log/GraphPPMCGen_v9.err < /dev/null &
else
	echo "Input number exceeded"
fi