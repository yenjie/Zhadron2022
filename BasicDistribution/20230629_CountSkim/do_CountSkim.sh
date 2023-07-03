#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_12_5_2_patch1/src

cd $CMSSWDir

cmsenv

source /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/SetupAnalysis.sh

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230629_CountSkim

mkdir -p SkimCount/20230630_1
mkdir -p SkimCount/log/20230630_1

if [ $1 -eq 0 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_nominal_centN-v15b-1-2.tex -Fraction 1 -CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 1 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_nominal_centU-v15b-1-2.tex -Fraction 1 -CentUD 1 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 2 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_nominal_centD-v15b-1-2.tex -Fraction 1 -CentUD 2 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 3 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_UEUp25_centN-v15b-1-2.tex -Fraction 1 -CentUD 0 --HFShift 699 --HFShiftData 676.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEUp25_v15b --BkgMCDir OutputMCBackgroundUEUp25_v15b
elif [ $1 -eq 4 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_UEUp25_centU-v15b-1-2.tex -Fraction 1 -CentUD 1 --HFShift 699 --HFShiftData 676.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEUp25_v15b --BkgMCDir OutputMCBackgroundUEUp25_v15b
elif [ $1 -eq 5 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_UEUp25_centD-v15b-1-2.tex -Fraction 1 -CentUD 2 --HFShift 699 --HFShiftData 676.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEUp25_v15b --BkgMCDir OutputMCBackgroundUEUp25_v15b
elif [ $1 -eq 6 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_UEDown25_centN-v15b-1-2.tex -Fraction 1 -CentUD 0 --HFShift 665 --HFShiftData 643.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEDown25_v15b --BkgMCDir OutputMCBackgroundUEDown25_v15b
elif [ $1 -eq 7 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_UEDown25_centU-v15b-1-2.tex -Fraction 1 -CentUD 1 --HFShift 665 --HFShiftData 643.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEDown25_v15b --BkgMCDir OutputMCBackgroundUEDown25_v15b
elif [ $1 -eq 8 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_UEDown25_centD-v15b-1-2.tex -Fraction 1 -CentUD 2 --HFShift 665 --HFShiftData 643.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEDown25_v15b --BkgMCDir OutputMCBackgroundUEDown25_v15b
elif [ $1 -eq 9 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt0-v15b-1-2.tex -Fraction 1 --ZWtID 0 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 10 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt1-v15b-1-2.tex -Fraction 1 --ZWtID 1 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 11 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt2-v15b-1-2.tex -Fraction 1 --ZWtID 2 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 12 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt3-v15b-1-2.tex -Fraction 1 --ZWtID 3 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 13 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt4-v15b-1-2.tex -Fraction 1 --ZWtID 4 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 14 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt5-v15b-1-2.tex -Fraction 1 --ZWtID 5 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 15 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt6-v15b-1-2.tex -Fraction 1 --ZWtID 6 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 16 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt7-v15b-1-2.tex -Fraction 1 --ZWtID 7 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 17 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt8-v15b-1-2.tex -Fraction 1 --ZWtID 8 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 18 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt9-v15b-1-2.tex -Fraction 1 --ZWtID 9 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 19 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt10-v15b-1-2.tex -Fraction 1 --ZWtID 10 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 20 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ZWt11-v15b-1-2.tex -Fraction 1 --ZWtID 11 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 21 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_ppNPUall-v15b-1-2.tex -Fraction 1 --ppNPU 1 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 22 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_VZ1-v15b-1-2.tex -Fraction 1 --VZMax -5 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 23 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_VZ2-v15b-1-2.tex -Fraction 1 --VZMin -5 --VZMax 0 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 24 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_VZ3-v15b-1-2.tex -Fraction 1 --VZMin 0 --VZMax 5 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 25 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_VZ4-v15b-1-2.tex -Fraction 1 --VZMin 5 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b
elif [ $1 -eq 26 ]
then
	./ExecuteCount --Output SkimCount/20230630_1/SkimCount_loose-v15b-1-2.tex -Fraction 1 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v15b --BkgMCDir OutputMCBackground_v15b --SigMCDir OutputMCLoose_v15c --SigDataDir OutputDataLoose_v15c
else
	echo "Input number exceeded"
fi