default: TestRun

TestRun: Execute
	mkdir -p log
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_0428/ \
		--Output GraphDataSignal_0430.root --Fraction 1 \
		 > log/GraphDataSignal_0430.out 2> log/GraphDataSignal_0430.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_0428/ \
		--Output GraphDataBackground_0430.root --Fraction 1 \
		 > log/GraphDataBackground_0430.out 2> log/GraphDataBackground_0430.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_0428/ \
		--Output GraphMCSignal_0430.root --Fraction 1 \
		 > log/GraphMCSignal_0430.out 2> log/GraphMCSignal_0430.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkg_0428/ \
		--Output GraphMCBackground_0430.root --Fraction 1 \
		 > log/GraphMCBackground_0430.out 2> log/GraphMCBackground_0430.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_0428/ \
		--Output GraphPPMC_0430.root --IgnoreCentrality true --Fraction 1 \
		 > log/GraphPPMC_0430.out 2> log/GraphPPMC_0430.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_0428/ \
		--Output GraphMCSignalGen_0430.root --Fraction 1 \
		 > log/GraphMCSignalGen_0430.out 2> log/GraphMCSignalGen_0430.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_0428/ \
		--Output GraphMCSignalGen0Sub_0430.root --OnlyZeroSub true --Fraction 1 \
		 > log/GraphMCSignalGen0Sub_0430.out 2> log/GraphMCSignalGen0Sub_0430.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_0428/ \
		--Output GraphMCBackgroundGen_0430.root --Fraction 1 \
		 > log/GraphMCBackgroundGen_0430.out 2> log/GraphMCBackgroundGen_0430.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_0428/ \
		--Output GraphPPMCGen_0430.root --IgnoreCentrality true --Fraction 1 \
		 > log/GraphPPMCGen_0430.out 2> log/GraphPPMCGen_0430.err < /dev/null &

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