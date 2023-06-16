
default: TestRun


Prepare:
	ln -sf $(ProjectBase)/CommonCode/root/ Efficiency
	ln -sf /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/ Hydjet

TestRun: Execute
	./Execute --Input Hydjet/HiForestMiniAOD_14.root --Output /tmp/chenyi/MB.root

Execute: DoQuickTree.cpp
	g++  DoQuickTree.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` \
		$(ProjectBase)/CommonCode/library/Messenger.o


