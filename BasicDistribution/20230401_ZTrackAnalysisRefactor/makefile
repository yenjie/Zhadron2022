default: TestRun

TestRun: Execute
	./Execute --InputBase /eos/cms/store/group/phys_heavyions_ops/pchou/OutputMC/ \
		--Output GraphMCSignal.root
	./Execute --InputBase /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/Skims/20230310_ZHadronSkims/Output/000*/ \
		--Output GraphDataSignal.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions_ops/pchou/OutputMCbkg/ \
		--Output GraphMCBackground.root
	./Execute --InputBase /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/Skims/20230310_ZHadronSkims/OutputBkg/000*/ \
		--Output GraphDataBackground.root

Execute: ZTrackAnalysis.cpp
	g++ ZTrackAnalysis.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17

Draw: ExecuteDraw
	./ExecuteDraw

ExecuteDraw: ZtrackDraw.cpp
	g++ ZtrackDraw.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteDraw `root-config --cflags --libs` -std=c++17
