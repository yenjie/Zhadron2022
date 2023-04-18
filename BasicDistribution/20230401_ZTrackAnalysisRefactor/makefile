default: TestRun

TestRun: Execute
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_5/ \
		--Output GraphMCSignal_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_5/ \
		--Output GraphDataSignal_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkg_5/ \
		--Output GraphMCBackground_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_5/ \
		--Output GraphDataBackground_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_5/ \
		--Output GraphPPMC_5.root --IgnoreCentrality true
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_5/ \
		--Output GraphMCSignalGen_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_5/ \
		--Output GraphMCBackgroundGen_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_5/ \
		--Output GraphPPMCGen_5.root --IgnoreCentrality true	

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
