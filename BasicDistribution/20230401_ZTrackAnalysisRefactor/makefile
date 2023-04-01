default: TestRun

TestRun: Execute
	./Execute --InputBase /eos/cms/store/group/phys_heavyions_ops/pchou/OutputMC_old/ \
		--Output GraphMCSignal.root
	./Execute --InputBase /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/Skims/20230310_ZHadronSkims/Output_old/ \
		--Output GraphDataSignal.root
	./Execute --InputBase /eos/cms/store/group/phys_heavyions_ops/pchou/OutputMCbkg_old/ \
		--Output GraphMCBackground.root
	./Execute --InputBase /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/Skims/20230310_ZHadronSkims/OutputBkg_old/ \
		--Output GraphDataBackground.root

Execute: ZTrackAnalysis.cpp
	g++ ZTrackAnalysis.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17

