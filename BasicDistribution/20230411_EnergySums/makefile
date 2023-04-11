
default: TestRunExploration

Prepare:
	rm -f Embedded Hydjet Nonembedded
	ln -sf /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20221017_ZHadronInitialRunMCDY/221017_113040/0000// Embedded
	ln -sf /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118// Hydjet
	ln -sf /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230408_ZHadronMLLWithMuTreePP/230408_215932/0000// Nonembedded

Execute: CalculateEnergySum.cpp
	g++ CalculateEnergySum.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o

TestRun: Execute
	./Execute --Input Embedded/HiForestMiniAOD_140.root --Output OutputEmbedded.root --Fraction 1
	./Execute --Input Hydjet/HiForestMiniAOD_14.root --Output OutputHydjet.root --Fraction 0.1
	./Execute --Input Nonembedded/HiForestAOD_140.root --Output OutputNonembedded.root --Fraction 0.1

ExecuteExploration: ExplorationPlots.cpp
	g++ ExplorationPlots.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteExploration `root-config --cflags --libs` -std=c++17

TestRunExploration: ExecuteExploration
	./ExecuteExploration --Embedded OutputEmbedded.root --Hydjet OutputHydjet.root --Nonembedded OutputNonembedded.root \
		--NominalHFShift 660 \
		--Output Plots.pdf
	cp Plots.pdf ~/public/html
