default: TestRun

TestRun: Execute
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_0422/ \
		--Output GraphDataSignal_0422.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_0422/ \
		--Output GraphDataBackground_0422.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_0422/ \
		--Output GraphMCSignal_0422.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkg_0422/ \
		--Output GraphMCBackground_0422.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_0422/ \
		--Output GraphPPMC_0422.root --IgnoreCentrality true
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_0422/ \
		--Output GraphMCSignalGen_0422.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_0422/ \
		--Output GraphMCSignalGen0Sub_0422.root --OnlyZeroSub true
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_0422/ \
		--Output GraphMCBackgroundGen_0422.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_0422/ \
		--Output GraphPPMCGen_0422.root --IgnoreCentrality true	

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