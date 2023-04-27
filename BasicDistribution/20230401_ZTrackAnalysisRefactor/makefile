default: TestRun

TestRun: Execute
	mkdir -p log
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_0427/ \
		--Output GraphDataSignal_0427.root --Fraction 1 \
		 > log/GraphDataSignal_0427.out 2> log/GraphDataSignal_0427.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_0427/ \
		--Output GraphDataBackground_0427.root --Fraction 1 \
		 > log/GraphDataBackground_0427.out 2> log/GraphDataBackground_0427.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_0427/ \
		--Output GraphMCSignal_0427.root --Fraction 1 \
		 > log/GraphMCSignal_0427.out 2> log/GraphMCSignal_0427.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkg_0427/ \
		--Output GraphMCBackground_0427.root --Fraction 1 \
		 > log/GraphMCBackground_0427.out 2> log/GraphMCBackground_0427.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_0427/ \
		--Output GraphPPMC_0427.root --IgnoreCentrality true --Fraction 1 \
		 > log/GraphPPMC_0427.out 2> log/GraphPPMC_0427.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_0427/ \
		--Output GraphMCSignalGen_0427.root --Fraction 1 \
		 > log/GraphMCSignalGen_0427.out 2> log/GraphMCSignalGen_0427.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_0427/ \
		--Output GraphMCSignalGen0Sub_0427.root --OnlyZeroSub true --Fraction 1 \
		 > log/GraphMCSignalGen0Sub_0427.out 2> log/GraphMCSignalGen0Sub_0427.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_0427/ \
		--Output GraphMCBackgroundGen_0427.root --Fraction 1 \
		 > log/GraphMCBackgroundGen_0427.out 2> log/GraphMCBackgroundGen_0427.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_0427/ \
		--Output GraphPPMCGen_0427.root --IgnoreCentrality true --Fraction 1 \
		 > log/GraphPPMCGen_0427.out 2> log/GraphPPMCGen_0427.err < /dev/null &

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