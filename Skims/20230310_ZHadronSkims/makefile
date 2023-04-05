PbPbBackgroundData = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias7/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias7/20221101_ZHadronMinimumBias7WithMuTree/221101_212932/0000/
PbPbBackgroundMCOld = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/
PbPbSignalDoubleMuon00 = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/0000/
PbPbSignalDoubleMuon01 = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/0001/
PbPbSignalDoubleMuon = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/000*/
PbPbSignalSingleMuon = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20230403_ZHadronSingleMuonWithMuTree//230403_182556/
PbPbSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20221017_ZHadronInitialRunMCDY/221017_113040/0000/
PbPbBackgroundMC = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/

default: TestRun

TestRun: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 1 --DoGenLevel false --IsData true --IsPP false --MinZPT 5

TestRunBackground: Execute
	./Execute --Input $(PbPbSignalDoubleMuon)/HiForestMiniAOD_144.root \
		--Output /tmp/$(USER)/Test.root --Fraction 1 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundData)/HiForestMiniAOD_118.root,$(PbPbBackgroundData)/HiForestMiniAOD_123.root,$(PbPbBackgroundData)/HiForestMiniAOD_127.root,$(PbPbBackgroundData)/HiForestMiniAOD_138.root,$(PbPbBackgroundData)/HiForestMiniAOD_148.root,$(PbPbBackgroundData)/HiForestMiniAOD_16.root,$(PbPbBackgroundData)/HiForestMiniAOD_17.root,$(PbPbBackgroundData)/HiForestMiniAOD_184.root,$(PbPbBackgroundData)/HiForestMiniAOD_18.root,$(PbPbBackgroundData)/HiForestMiniAOD_194.root \
		--HFShift 10 --Tolerance 100 --ToleranceFraction 0.2 --Oversample 10

TestRunBackgroundSimple: Execute
	./Execute --Input $(PbPbSignalDoubleMuon)/HiForestMiniAOD_144.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.2 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundData)/HiForestMiniAOD_118.root \
		--HFShift 10 --Tolerance 100 --ToleranceFraction 0.2

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
	bash PrepareInput.sh $(PbPbSignalDoubleMuon00)/ 6 Log/ `pwd`/Output/ --Fraction 1 --DoGenLevel false --IsData true --IsPP false

PrepareToRun01:
	bash PrepareInput.sh $(PbPbSignalDoubleMuon01)/ 6 Log/ `pwd`/Output/ --Fraction 1 --DoGenLevel false --IsData true --IsPP false

PrepareToRunMC:
	bash PrepareInput.sh $(PbPbSignalMC)/ 2 LogMC/ /eos/cms/store/group/phys_heavyions_ops/pchou/OutputMC/ --Fraction 1 --DoGenLevel false --IsData true --IsPP false

PrepareToRunBackground:
	bash PrepareInput.sh $(PbPbSignalDoubleMuon00)/ 2 LogBkg/ `pwd`/OutputBkg/ --Fraction 1 --DoGenLevel false --IsData true --IsPP false \
	--DoBackground true \
	--Background $(PbPbBackgroundMCOld)/HiForestMiniAOD_10.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_13.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_17.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_20.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_22.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_34.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_37.root \
	--HFShift 682 --Tolerance 341 --ToleranceFraction 0.1 --DoSumET false --Oversample 10

PrepareToRunBackground01:
	bash PrepareInput.sh $(PbPbSignalDoubleMuon01)/ 2 LogBkg01/ `pwd`/OutputBkg01/ --Fraction 1 --DoGenLevel false --IsData true --IsPP false \
	--DoBackground true \
	--Background $(PbPbBackgroundMCOld)/HiForestMiniAOD_10.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_13.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_17.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_20.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_22.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_34.root,$(PbPbBackgroundMCOld)/HiForestMiniAOD_37.root \
	--HFShift 682 --Tolerance 341 --ToleranceFraction 0.1 --DoSumET false --Oversample 10

PrepareToRunRandomBackground:
	bash PrepareInputRandomBackground.sh \
		'$(PbPbSignalDoubleMuon)' 2 LogRandomBackground/ `pwd`/OutputRandomBackground/ \
		$(PbPbBackgroundData) 10 \
		--Fraction 1 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true --HFShift 682 --Tolerance 341 --ToleranceFraction 0.1 --DoSumET false --Oversample 10

PrepareToRunMCBackground:
	bash PrepareInput.sh $(PbPbSignalMC)/ 2 LogMCbkg_3/ /eos/cms/store/group/phys_heavyions_ops/pchou/OutputMCbkg_3/ --Fraction 1 --DoGenLevel true --IsData false --IsPP false \
	--DoBackground true \
	--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_11.root,$(PbPbBackgroundMC)/HiForestMiniAOD_12.root,$(PbPbBackgroundMC)/HiForestMiniAOD_13.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root,$(PbPbBackgroundMC)/HiForestMiniAOD_17.root,$(PbPbBackgroundMC)/HiForestMiniAOD_18.root,$(PbPbBackgroundMC)/HiForestMiniAOD_19.root,$(PbPbBackgroundMC)/HiForestMiniAOD_1.root,$(PbPbBackgroundMC)/HiForestMiniAOD_20.root \
	--HFShift 682 --Tolerance 341 --ToleranceFraction 0.1 --DoSumET false --Oversample 10


