default: Prepare TestRun

DYMC    = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20230501_ZHadronMCDY/230501_155504/0000//
EOSBase = /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Corrections/20230506_ZEfficiency/

PPMC    = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230408_ZHadronMLLWithMuTreePP/230408_215932/0000/

Prepare:
	ln -sf $(DYMC) DYMC

TestRun: Execute
	./Execute --Input `ls DYMC/* | head -n5 | tr '\n' ','` \
		--Output EfficiencyPlots.pdf --RootOutput /tmp/chenyi/ZEfficiency.root --Fraction 1.00
	mv /tmp/chenyi/ZEfficiency.root .
	cp EfficiencyPlots.pdf ~/public/html/

TestRunPP: Execute
	./Execute --Input `ls PPMC/* | head -n5 | tr '\n' ','` \
		--Output EfficiencyPlots.pdf --RootOutput /tmp/chenyi/ZEfficiency.root --Fraction 1.00 --IsPP true
	mv /tmp/chenyi/ZEfficiency.root .
	cp EfficiencyPlots.pdf ~/public/html/

TestRunAll: Execute
	./Execute --Input `ls DYMC/* | tr '\n' ','` \
		--Output AllEfficiencyPlots.pdf --RootOutput /tmp/chenyi/ZEfficiencyAll.root --Fraction 1.00
	mv /tmp/chenyi/ZEfficiencyAll.root .
	cp AllEfficiencyPlots.pdf ~/public/html/

Execute: DeriveZEfficiency.cpp
	g++ DeriveZEfficiency.cpp  -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o \
		# $(FJExtra) $(FJCExtra)

PrepareToRun: Execute
	bash PrepareInput.sh \
		$(DYMC) 2 Log/ $(EOSBase)/PbPb/ \
		--Fraction 1.00

PrepareToRunPP: Execute
	bash PrepareInput.sh \
		$(PPMC) 2 Log/ $(EOSBase)/pp/ \
		--Fraction 1.00 --IsPP true
