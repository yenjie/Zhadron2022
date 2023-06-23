default: TestRun

TestRun: Execute
	mkdir -p log
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_v14/ \
		--Output GraphDataSignal_v14_05test.root --Fraction 0.5 \
		 > log/GraphDataSignal_v14_05test.out 2> log/GraphDataSignal_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_v14/ \
		--Output GraphDataBackground_v14_05test.root --Fraction 0.5 \
		 > log/GraphDataBackground_v14_05test.out 2> log/GraphDataBackground_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v14/ \
		--Output GraphMCSignal_v14_05test.root --Fraction 0.5 \
		 > log/GraphMCSignal_v14_05test.out 2> log/GraphMCSignal_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v14/ \
		--Output GraphMCBackground_v14_05test.root --Fraction 0.5 \
		 > log/GraphMCBackground_v14_05test.out 2> log/GraphMCBackground_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v14/ \
		--Output GraphPPMC_v14_05test.root --IgnoreCentrality true --Fraction 0.5 \
		 > log/GraphPPMC_v14_05test.out 2> log/GraphPPMC_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v14/ \
		--Output GraphPPMC0Sub_v14_05test.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 0.5 \
		 > log/GraphPPMC0Sub_v14_05test.out 2> log/GraphPPMC0Sub_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v14/ \
		--Output GraphMCSignalGen_v14_05test.root --Fraction 0.5 --DoGenCorrelation true \
		 > log/GraphMCSignalGen_v14_05test.out 2> log/GraphMCSignalGen_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v14/ \
		--Output GraphMCSignalGen0Sub_v14_05test.root --OnlyZeroSub true --Fraction 0.5 --DoGenCorrelation true \
		 > log/GraphMCSignalGen0Sub_v14_05test.out 2> log/GraphMCSignalGen0Sub_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_v14/ \
		--Output GraphMCBackgroundGen_v14_05test.root --Fraction 0.5 --DoGenCorrelation true \
		 > log/GraphMCBackgroundGen_v14_05test.out 2> log/GraphMCBackgroundGen_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_v14/ \
		--Output GraphMCBackgroundGen0Sub_v14_05test.root --OnlyZeroSub true --Fraction 0.5 --DoGenCorrelation true \
		 > log/GraphMCBackgroundGen0Sub_v14_05test.out 2> log/GraphMCBackgroundGen0Sub_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v14/ \
		--Output GraphPPMCGen_v14_05test.root --IgnoreCentrality true --Fraction 0.5 --DoGenCorrelation true \
		 > log/GraphPPMCGen_v14_05test.out 2> log/GraphPPMCGen_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v14/ \
		--Output GraphPPMCGen_v14_05test.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 0.5 --DoGenCorrelation true \
		 > log/GraphPPMCGen_v14_05test.out 2> log/GraphPPMCGen0Sub_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v14/ \
		--Output GraphMCSignal0Sub_v14_05test.root --OnlyZeroSub true --Fraction 0.5 \
		 > log/GraphMCSignal0Sub_v14_05test.out 2> log/GraphMCSignal0Sub_v14_05test.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPData_v14/ \
		--Output GraphPPData_v14_05test.root --IgnoreCentrality true --Fraction 0.5 \
		 > log/GraphPPData_v14_05test.out 2> log/GraphPPData_v14_05test.err < /dev/null &

TestExploration: ExecuteExploration
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00 --Histogram HEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00_HEtaPhi.pdf
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_0_10_TrackPT_0p00_1000p00 --Histogram HEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_0_10_TrackPT_0p00_1000p00_HEtaPhi.pdf
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_50_90_TrackPT_0p00_1000p00 --Histogram HEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_50_90_TrackPT_0p00_1000p00_HEtaPhi.pdf
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00 --Histogram HWTAEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00_HWTAEtaPhi.pdf
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00 --Histogram HMaxOppositeHadronEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00_HMaxOppositeHadronEtaPhi.pdf

Execute: ZTrackAnalysis.cpp
	g++ ZTrackAnalysis.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17

Draw: ExecuteDraw
	./ExecuteDraw

ExecuteDraw: ZtrackDraw.cpp
	g++ ZtrackDraw.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteDraw `root-config --cflags --libs` -std=c++17

ExecuteExploration: SimpleExploration.cpp
	g++ SimpleExploration.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteExploration `root-config --cflags --libs` -std=c++17

DrawZdPhi: ExecuteDrawZdPhi
	./ExecuteDrawZdPhi

ExecuteDrawZdPhi: ZdPhiDraw.cpp
	g++ ZdPhiDraw.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteDrawZdPhi `root-config --cflags --libs` -std=c++17

CheckSubtract: ExecuteCheckSubtract
	./ExecuteCheckSubtract

ExecuteCheckSubtract: ZcheckSubtract.cpp
	g++ ZcheckSubtract.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteCheckSubtract `root-config --cflags --libs` -std=c++17

CheckBasic: ExecuteZcheckBasic
	./ExecuteZcheckBasic

ExecuteZcheckBasic: ZcheckBasic.cpp
	g++ ZcheckBasic.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteZcheckBasic `root-config --cflags --libs` -std=c++17

DrawProj: ExecuteDrawProj
	./ExecuteDrawProj

ExecuteDrawProj: ZtrackProj.cpp
	g++ ZtrackProj.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteDrawProj `root-config --cflags --libs` -std=c++17

CountSkim: ExecuteCount
	mkdir -p SkimCount/log
	./ExecuteCount --Output SkimCount/SkimCount_nominal_centN-1.txt --CentUD 0 --HFShift 682 --Tolerance 187.5 \
		--BkgDataDir OutputDatabkg_v15 --BkgMCDir SkimMCBackground \
		> SkimCount/log/SkimCount_nominal_centN.out 2> SkimCount/log/SkimCount_nominal_centN.err < /dev/null &
	./ExecuteCount --Output SkimCount/SkimCount_nominal_centN_50-1.txt --CentUD 0 --HFShift 682 --Tolerance 50 \
		--BkgDataDir OutputDatabkg_v15 --BkgMCDir SkimMCBackground \
		> SkimCount/log/SkimCount_nominal_centN_50.out 2> SkimCount/log/SkimCount_nominal_centN_50.err < /dev/null &
	./ExecuteCount --Output SkimCount/SkimCount_nominal_centN_30-1.txt --CentUD 0 --HFShift 682 --Tolerance 30 \
		--BkgDataDir OutputDatabkg_v15 --BkgMCDir SkimMCBackground \
		> SkimCount/log/SkimCount_nominal_centN_30.out 2> SkimCount/log/SkimCount_nominal_centN_30.err < /dev/null &
	##./ExecuteCount --Output SkimCount/SkimCount_nominal_centU.txt --CentUD 1 \
	##	--BkgDataDir OutputDatabkg_v15 --BkgMCDir OutputMCBackground_v15 \
	##	> SkimCount/log/SkimCount_nominal_centU.out 2> SkimCount/log/SkimCount_nominal_centU.err < /dev/null &
	##./ExecuteCount --Output SkimCount/SkimCount_nominal_centD.txt --CentUD 2 \
	##	--BkgDataDir OutputDatabkg_v15 --BkgMCDir OutputMCBackground_v15 \
	##	> SkimCount/log/SkimCount_nominal_centD.out 2> SkimCount/log/SkimCount_nominal_centD.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEDown25_centN.txt --CentUD 0 --HFShift 665 --Tolerance 187.5 \
	#	--BkgDataDir OutputDatabkgUEDown25_v15 --BkgMCDir OutputMCBackgroundUEDown25_v15 \
	#	> SkimCount/log/SkimCount_UEDown25_centN.out 2> SkimCount/log/SkimCount_UEDown25_centN.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEDown25_centN_50.txt --CentUD 0 --HFShift 665 --Tolerance 50 \
	#	--BkgDataDir OutputDatabkgUEDown25_v15 --BkgMCDir OutputMCBackgroundUEDown25_v15 \
	#	> SkimCount/log/SkimCount_UEDown25_centN_50.out 2> SkimCount/log/SkimCount_UEDown25_centN_50.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEDown25_centN_30.txt --CentUD 0 --HFShift 665 --Tolerance 30 \
	#	--BkgDataDir OutputDatabkgUEDown25_v15 --BkgMCDir OutputMCBackgroundUEDown25_v15 \
	#	> SkimCount/log/SkimCount_UEDown25_centN_30.out 2> SkimCount/log/SkimCount_UEDown25_centN_30.err < /dev/null &
	##./ExecuteCount --Output SkimCount/SkimCount_UEDown25_centU.txt --CentUD 1 \
	##	--BkgDataDir OutputDatabkgUEDown25_v15 --BkgMCDir OutputMCBackgroundUEDown25_v15 \
	##	> SkimCount/log/SkimCount_UEDown25_centU.out 2> SkimCount/log/SkimCount_UEDown25_centU.err < /dev/null &
	##./ExecuteCount --Output SkimCount/SkimCount_UEDown25_centD.txt --CentUD 2 \
	##	--BkgDataDir OutputDatabkgUEDown25_v15 --BkgMCDir OutputMCBackgroundUEDown25_v15 \
	##	> SkimCount/log/SkimCount_UEDown25_centD.out 2> SkimCount/log/SkimCount_UEDown25_centD.err < /dev/null &
	./ExecuteCount --Output SkimCount/SkimCount_UEUp25_centN.txt --CentUD 0 --HFShift 699 --Tolerance 187.5 \
		--BkgDataDir OutputDatabkgUEUp25_v15 --BkgMCDir SkimMCBackgroundUEUp25 \
		> SkimCount/log/SkimCount_UEUp25_centN.out 2> SkimCount/log/SkimCount_UEUp25_centN.err < /dev/null &
	./ExecuteCount --Output SkimCount/SkimCount_UEUp25_centN_50.txt --CentUD 0 --HFShift 699 --Tolerance 50 \
		--BkgDataDir OutputDatabkgUEUp25_v15 --BkgMCDir SkimMCBackgroundUEUp25 \
		> SkimCount/log/SkimCount_UEUp25_centN_50.out 2> SkimCount/log/SkimCount_UEUp25_centN_50.err < /dev/null &
	./ExecuteCount --Output SkimCount/SkimCount_UEUp25_centN_30.txt --CentUD 0 --HFShift 699 --Tolerance 30 \
		--BkgDataDir OutputDatabkgUEUp25_v15 --BkgMCDir SkimMCBackgroundUEUp25 \
		> SkimCount/log/SkimCount_UEUp25_centN_30.out 2> SkimCount/log/SkimCount_UEUp25_centN_30.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEUp25_centU.txt --CentUD 1 \
	#	--BkgDataDir OutputDatabkgUEUp25_v15 --BkgMCDir OutputMCBackgroundUEUp25_v15 \
	#	> SkimCount/log/SkimCount_UEUp25_centU.out 2> SkimCount/log/SkimCount_UEUp25_centU.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEUp25_centD.txt --CentUD 2 \
	#	--BkgDataDir OutputDatabkgUEUp25_v15 --BkgMCDir OutputMCBackgroundUEUp25_v15 \
	#	> SkimCount/log/SkimCount_UEUp25_centD.out 2> SkimCount/log/SkimCount_UEUp25_centD.err < /dev/null &	
	#./ExecuteCount --Output SkimCount/SkimCount_UEDown30_centN.txt --CentUD 0 \
	#	--BkgDataDir OutputDatabkgUEDown30_v15 --BkgMCDir OutputMCBackgroundUEDown30_v15 \
	#	> SkimCount/log/SkimCount_UEDown30_centN.out 2> SkimCount/log/SkimCount_UEDown30_centN.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEDown30_centU.txt --CentUD 1 \
	#	--BkgDataDir OutputDatabkgUEDown30_v15 --BkgMCDir OutputMCBackgroundUEDown30_v15 \
	#	> SkimCount/log/SkimCount_UEDown30_centU.out 2> SkimCount/log/SkimCount_UEDown30_centU.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEDown30_centD.txt --CentUD 2 \
	#	--BkgDataDir OutputDatabkgUEDown30_v15 --BkgMCDir OutputMCBackgroundUEDown30_v15 \
	#	> SkimCount/log/SkimCount_UEDown30_centD.out 2> SkimCount/log/SkimCount_UEDown30_centD.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEUp30_centN.txt --CentUD 0 \
	#	--BkgDataDir OutputDatabkgUEUp30_v15 --BkgMCDir OutputMCBackgroundUEUp30_v15 \
	#	> SkimCount/log/SkimCount_UEUp30_centN.out 2> SkimCount/log/SkimCount_UEUp30_centN.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEUp30_centU.txt --CentUD 1 \
	#	--BkgDataDir OutputDatabkgUEUp30_v15 --BkgMCDir OutputMCBackgroundUEUp30_v15 \
	#	> SkimCount/log/SkimCount_UEUp30_centU.out 2> SkimCount/log/SkimCount_UEUp30_centU.err < /dev/null &
	#./ExecuteCount --Output SkimCount/SkimCount_UEUp30_centD.txt --CentUD 2 \
	#	--BkgDataDir OutputDatabkgUEUp30_v15 --BkgMCDir OutputMCBackgroundUEUp30_v15 \
	#	> SkimCount/log/SkimCount_UEUp30_centD.out 2> SkimCount/log/SkimCount_UEUp30_centD.err < /dev/null &
ExecuteCount: CountSkim.cpp
	g++ CountSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteCount `root-config --cflags --libs` -std=c++17
