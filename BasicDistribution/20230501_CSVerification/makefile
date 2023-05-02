PbPbBackgroundMC = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/
PPSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230407_ZHadronMLLWithMuTreePP/230407_143418/0000/
PbPbSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20230501_ZHadronMCDY/230501_155504/0000/


default: TestRun

TestRun: Execute
	# for i in `seq 10 60`; do echo $$i; ./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_140.root --IsPP false --Entry $$i; done
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_140.root --Entry 43 --Output Meow.root

Execute: CSVerification.cpp
	g++ CSVerification.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o \
		$(FJExtra) $(FJCExtra)

