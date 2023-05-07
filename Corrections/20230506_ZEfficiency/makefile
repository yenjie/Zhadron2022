default: Prepare TestRun

Prepare:
	ln -sf /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20230501_ZHadronMCDY/230501_155504/0000// DYMC

TestRun: Execute
	./Execute --Input `ls DYMC/* | head -n10 | tr '\n' ','` \
		--Output EfficiencyPlots.pdf --RootOutput /tmp/chenyi/ZEfficiency.root --Fraction 1.00
	cp EfficiencyPlots.pdf ~/public/html/

TestRunAll: Execute
	./Execute --Input `ls DYMC/* | tr '\n' ','` \
		--Output EfficiencyPlots.pdf --RootOutput /tmp/chenyi/ZEfficiencyAll.root --Fraction 1.00
	mv /tmp/chenyi/ZEfficiencyAll.root .
	cp EfficiencyPlots.pdf ~/public/html/

Execute: DeriveZEfficiency.cpp
	g++ DeriveZEfficiency.cpp  -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o \
		# $(FJExtra) $(FJCExtra)

