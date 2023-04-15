default: TestRun

TestRun: Execute
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC01_5/ \
		--Output GraphMCSignal01_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData01_5/ \
		--Output GraphDataSignal01_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkg01_5/ \
		--Output GraphMCBackground01_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg01_5/ \
		--Output GraphDataBackground01_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC01_5/ \
		--Output GraphPPMC01_5.root --IgnoreCentrality true
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen01_5/ \
		--Output GraphMCSignalGen01_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen01_5/ \
		--Output GraphMCBackgroundGen01_5.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen01_5/ \
		--Output GraphPPMCGen01_5.root --IgnoreCentrality true	

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

