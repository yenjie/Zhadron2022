PbPbBackgroundMC = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/
PPSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230407_ZHadronMLLWithMuTreePP/230407_143418/0000/


default: TestRun

TestRun: Execute
	./Execute --Input $(PPSignalMC)/HiForestAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --IsData false --IsPP true --MinZPT 5 \
		--DoBackground true --Background $(PbPbBackgroundMC)/HiForestMiniAOD_14.root
	root -l -b -q /tmp/chenyi/Test.root QuickPlot.C 
	cp Meow*.pdf ~/public/html/

Execute: CalculateAxis.cpp
	g++ CalculateAxis.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o \
		$(FJExtra) $(FJCExtra)

