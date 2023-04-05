PbPbBackgroundData = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias7/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias7/20221101_ZHadronMinimumBias7WithMuTree/221101_212932/0000/
PbPbBackgroundMCOld = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/
PbPbSignalDoubleMuon = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941//
PbPbSignalSingleMuon = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20230403_ZHadronSingleMuonWithMuTree//230403_182556/
PbPbSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20221017_ZHadronInitialRunMCDY/221017_113040/0000/
PbPbBackgroundMC = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/
PPSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230405_ZHadronMLLWithMuTreePP/230405_101901/0000/
# PPSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230405_ZHadronMLLWithMuTreePP/230405_101901/0000/////////

default: TestRun

TestRun: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.2 --DoGenLevel false --IsData true --IsPP false --MinZPT 5

TestRunBackground: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.2 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundData)//HiForestMiniAOD_118.root,$(PbPbBackgroundData)//HiForestMiniAOD_123.root,$(PbPbBackgroundData)//HiForestMiniAOD_127.root,$(PbPbBackgroundData)//HiForestMiniAOD_138.root,$(PbPbBackgroundData)//HiForestMiniAOD_148.root,$(PbPbBackgroundData)//HiForestMiniAOD_16.root,$(PbPbBackgroundData)//HiForestMiniAOD_17.root,$(PbPbBackgroundData)//HiForestMiniAOD_184.root,$(PbPbBackgroundData)//HiForestMiniAOD_18.root,$(PbPbBackgroundData)//HiForestMiniAOD_194.root \
		--HFShift 660 --Tolerance 330 --ToleranceFraction 0.1 --Oversample 10

TestRunPP: Execute
	./Execute --Input $(PPSignalMC)/HiForestAOD_12.root \
		--Output /tmp/$(USER)/Test.root --Fraction 1 --DoGenLevel true --IsData false --IsPP true --MinZPT 5

TestRunBackgroundSimple: Execute
	./Execute --Input /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20230403_ZHadronSingleMuonWithMuTree/230403_182556/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.2 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundData)//HiForestMiniAOD_118.root \
		--HFShift 660 --Tolerance 330 --ToleranceFraction 0.1

TestRunMCBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.2 --DoGenLevel true --IsData false --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root \
		--HFShift 682 --Tolerance 341 --ToleranceFraction 0.1 --DoSumET false


Execute: DoZHadronSkim.cpp
	g++ DoZHadronSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o

PrepareToRun:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		6 LogData/ /eos/cms/store/group/phys_heavyions/pchou/OutputData/ --Fraction 1 --DoGenLevel false --IsData true --IsPP false

PrepareToRunMC:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		2 LogMC/ /eos/cms/store/group/phys_heavyions/pchou/OutputMC/ \
		--Fraction 1 --DoGenLevel false --IsData true --IsPP false

PrepareToRunBackground:
	bash PrepareInput.sh \
		'/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20230403_ZHadronSingleMuonWithMuTree/230403_182556/*/' \
		2 LogDatabkg/ /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg/ --Fraction 1 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true \
		--Background /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_10.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_13.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_22.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_34.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_37.root \
		--HFShift 660 --Tolerance 330 --ToleranceFraction 0.1 --DoSumET false --Oversample 10

PrepareToRunRandomBackground:
	bash PrepareInputRandomBackground.sh \
		'/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20230403_ZHadronSingleMuonWithMuTree/230403_182556/*/' \
		2 LogDatabkg/ /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg/ \
		$(PbPbBackgroundData)// 12 \
		--Fraction 1 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true --HFShift 660 --Tolerance 330 --ToleranceFraction 0.1 --DoSumET false --Oversample 10

PrepareToRunMCBackground:
	bash PrepareInput.sh \
		/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20221017_ZHadronInitialRunMCDY/221017_113040/0000/ \
		2 LogMCbkg/ /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkg/ \
		--Fraction 1 --DoGenLevel true --IsData false --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_11.root,$(PbPbBackgroundMC)/HiForestMiniAOD_12.root,$(PbPbBackgroundMC)/HiForestMiniAOD_13.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root,$(PbPbBackgroundMC)/HiForestMiniAOD_17.root,$(PbPbBackgroundMC)/HiForestMiniAOD_18.root,$(PbPbBackgroundMC)/HiForestMiniAOD_19.root,$(PbPbBackgroundMC)/HiForestMiniAOD_1.root,$(PbPbBackgroundMC)/HiForestMiniAOD_20.root \
		--HFShift 682 --Tolerance 341 --ToleranceFraction 0.1 --DoSumET false --Oversample 10

PrepareToRunRandomMCBackground:
	bash PrepareInputRandomBackground.sh \
		/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20221017_ZHadronInitialRunMCDY/221017_113040/0000/ \
		2 LogMCbkg/ /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkg/ \
		$(PbPbBackgroundMC)/ 12 \
		--Fraction 1 --DoGenLevel true --IsData false --IsPP false \
		--DoBackground true --HFShift 682 --Tolerance 341 --ToleranceFraction 0.1 --DoSumET false --Oversample 10
