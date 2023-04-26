default: TestRun

TestRun: Execute
	mkdir -p log
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_0422/ \
		--Output GraphDataSignal_0422.root \
		 > log/GraphDataSignal_0422.out 2> log/GraphDataSignal_0422.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_0422/ \
		--Output GraphDataBackground_0422.root \
		 > log/GraphDataBackground_0422.out 2> log/GraphDataBackground_0422.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_0422/ \
		--Output GraphMCSignal_0422.root \
		 > log/GraphMCSignal_0422.out 2> log/GraphMCSignal_0422.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkg_0422/ \
		--Output GraphMCBackground_0422.root \
		 > log/GraphMCBackground_0422.out 2> log/GraphMCBackground_0422.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_0422/ \
		--Output GraphPPMC_0422.root --IgnoreCentrality true \
		 > log/GraphPPMC_0422.out 2> log/GraphPPMC_0422.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_0422/ \
		--Output GraphMCSignalGen_0422.root \
		 > log/GraphMCSignalGen_0422.out 2> log/GraphMCSignalGen_0422.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_0422/ \
		--Output GraphMCSignalGen0Sub_0422.root --OnlyZeroSub true \
		 > log/GraphMCSignalGen0Sub_0422.out 2> log/GraphMCSignalGen0Sub_0422.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_0422/ \
		--Output GraphMCBackgroundGen_0422.root \
		 > log/GraphMCBackgroundGen_0422.out 2> log/GraphMCBackgroundGen_0422.err < /dev/null &
	nohup ./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_0422/ \
		--Output GraphPPMCGen_0422.root --IgnoreCentrality true \
		 > log/GraphPPMCGen_0422.out 2> log/GraphPPMCGen_0422.err < /dev/null &

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