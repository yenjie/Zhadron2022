default: TestRun

TestRun: Execute
	mkdir -p log
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_v16/ \
		--Output GraphDataSignal_v16.root --Fraction 1 \
		 > log/GraphDataSignal_v16.out 2> log/GraphDataSignal_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackground_v15c/ \
		--Output GraphDataBackground_v15c.root --Fraction 1 \
		 > log/GraphDataBackground_v15c.out 2> log/GraphDataBackground_v15c.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v16/ \
		--Output GraphMCSignal_v16.root --Fraction 1 \
		 > log/GraphMCSignal_v16.out 2> log/GraphMCSignal_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v15c/ \
		--Output GraphMCBackground_v15c.root --Fraction 1 \
		 > log/GraphMCBackground_v15c.out 2> log/GraphMCBackground_v15c.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v16/ \
		--Output GraphPPMC_v16.root --IgnoreCentrality true --Fraction 1 \
		 > log/GraphPPMC_v16.out 2> log/GraphPPMC_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v16/ \
		--Output GraphPPMC0Sub_v16.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1 \
		 > log/GraphPPMC0Sub_v16.out 2> log/GraphPPMC0Sub_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v16/ \
		--Output GraphMCSignalGen_v16.root --Fraction 1 --DoGenCorrelation true \
		 > log/GraphMCSignalGen_v16.out 2> log/GraphMCSignalGen_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v16/ \
		--Output GraphMCSignalGen0Sub_v16.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true \
		 > log/GraphMCSignalGen0Sub_v16.out 2> log/GraphMCSignalGen0Sub_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v15c/ \
		--Output GraphMCBackgroundGen_v15c.root --Fraction 1 --DoGenCorrelation true \
		 > log/GraphMCBackgroundGen_v15c.out 2> log/GraphMCBackgroundGen_v15c.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v15c/ \
		--Output GraphMCBackgroundGen0Sub_v15c.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true \
		 > log/GraphMCBackgroundGen0Sub_v15c.out 2> log/GraphMCBackgroundGen0Sub_v15c.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v16/ \
		--Output GraphPPMCGen_v16.root --IgnoreCentrality true --Fraction 1 --DoGenCorrelation true \
		 > log/GraphPPMCGen_v16.out 2> log/GraphPPMCGen_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v16/ \
		--Output GraphPPMCGen_v16.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true \
		 > log/GraphPPMCGen_v16.out 2> log/GraphPPMCGen0Sub_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v16/ \
		--Output GraphMCSignal0Sub_v16.root --OnlyZeroSub true --Fraction 1 \
		 > log/GraphMCSignal0Sub_v16.out 2> log/GraphMCSignal0Sub_v16.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPData_v16/ \
		--Output GraphPPData_v16.root --IgnoreCentrality true --Fraction 1 \
		 > log/GraphPPData_v16.out 2> log/GraphPPData_v16.err < /dev/null &

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