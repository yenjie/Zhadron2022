#PbPbBackgroundData = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias7/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias7/20221101_ZHadronMinimumBias7WithMuTree/221101_212932/0000/
PbPbBackgroundData = /eos/cms/store/group/phys_heavyions/mitaylor/PhotonJet/HIMinimumBias4/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias4/20230203PbPbMB/230203_165233/0000/
PbPbBackgroundMCOld = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/
PbPbSignalDoubleMuon = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/
PbPbSignalSingleMuon = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20230501_ZHadronSingleMuonWithMuTree/230501_155126/
PbPbSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20230501_ZHadronMCDY/230501_155504/0000/
PbPbBackgroundMC = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/
PPSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230408_ZHadronMLLWithMuTreePP/230408_215932//0000/
# PPSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230405_ZHadronMLLWithMuTreePP/230405_101901/0000/
PPSignalData = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/SingleMuon/Run2017G-17Nov2017-v1/AOD/SingleMuon/20230405_ZHadronSingleMuonWithMuTreePP/230405_185259/

default: Prepare TestRun

Prepare:
	bash DefineNominalSetting.sh
	
Execute: DoZHadronSkim.cpp
	g++ DoZHadronSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o \
		# $(FJExtra) $(FJCExtra)

TestRun: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		`DHQuery Setting.dh PbPbSignalData Nominal`
	
TestRunMC: Execute
	time ./Execute --Input PbPbMC/HiForestMiniAOD_211.root \
		--Output /tmp/$(USER)/TestMC.root --Fraction 0.02 \
		`DHQuery Setting.dh PbPbSignalMC Nominal`

TestRunGen: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_114.root \
		--Output /tmp/$(USER)/TestGenMC.root --Fraction 0.1 \
		`DHQuery Setting.dh PbPbSignalGenMC Nominal`

TestRunGenPP: Execute
	./Execute --Input `ls $(PPSignalMC)/*root | head -n 2 | tr '\n' ','` \
		--Output /tmp/$(USER)/TestGenPP.root --Fraction 1 \
		`DHQuery Setting.dh PPSignalGenMC Nominal`

TestRunBackground: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(PbPbBackgroundData)/HiForestMiniAOD_118.root,$(PbPbBackgroundData)/HiForestMiniAOD_123.root,$(PbPbBackgroundData)/HiForestMiniAOD_127.root,$(PbPbBackgroundData)/HiForestMiniAOD_138.root,$(PbPbBackgroundData)/HiForestMiniAOD_148.root,$(PbPbBackgroundData)/HiForestMiniAOD_16.root,$(PbPbBackgroundData)/HiForestMiniAOD_17.root,$(PbPbBackgroundData)/HiForestMiniAOD_184.root,$(PbPbBackgroundData)/HiForestMiniAOD_18.root,$(PbPbBackgroundData)/HiForestMiniAOD_194.root \
		`DHQuery Setting.dh PbPbSignalData Nominal`

TestRunPP: Execute
	./Execute --Input `ls $(PPSignalMC)/*root | head -n2 | tr '\n' ','` \
		--Output /tmp/$(USER)/TestPP.root --Fraction 1 \
		`DHQuery Setting.dh PPSignalMC Nominal`

TestRunPPData: Execute
	./Execute --Input $(PPSignalData)/0000/HiForestAOD_12.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		`DHQuery Setting.dh PPSignalData Nominal`

TestRunBackgroundSimple: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 1 \
		--Background $(PbPbBackgroundData)/HiForestMiniAOD_118.root \
		`DHQuery Setting.dh PbPbSignalData Nominal`

TestRunMCBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root \
		`DHQuery Setting.dh PbPbBackgroundMC Nominal`

TestRunMCGenBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root \
		`DHQuery Setting.dh PbPbSignalMC Nominal`

#BackgroundCount = 37
#BackgroundFiles = `ls $(PbPbBackgroundMC)/* | shuf | head -n$(BackgroundCount) | tr '\n' ',' | sed "s/,$//"`

#37
#BackgroundFiles = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_36.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_21.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_24.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_32.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_5.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_8.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_27.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_12.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_2.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_34.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_4.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_22.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_6.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_15.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_13.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_11.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_30.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_26.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_25.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_7.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_28.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_3.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_29.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_31.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_1.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_37.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_9.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_16.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_33.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_10.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_35.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_23.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_19.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_18.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_14.root

#12
BackgroundFiles = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_36.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_21.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_24.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_32.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_5.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_8.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_27.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_12.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_2.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_34.root,

TestRunRandomMCGenBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(BackgroundFiles) \
		`DHQuery Setting.dh PbPbSignalMC Nominal`

#EOSBase = /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230310_ZHadronSkims
EOSBase = /eos/cms/store/group/phys_heavyions/pchou

PrepareToRun:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		5 LogData_v10/ $(EOSBase)/OutputData_v10/ \
		--Fraction 1 `DHQuery Setting.dh PbPbSignalData Nominal`

PrepareToRunMC:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		5 LogMC_v10/ $(EOSBase)/OutputMC_v10/ \
		--Fraction 1 `DHQuery Setting.dh PbPbSignalMC Nominal`

PrepareToRunGenMC:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		5 LogGenMC_v10/ $(EOSBase)/OutputMCGen_v10/ \
 		--Fraction 1 `DHQuery Setting.dh PbPbSignalGenMC Nominal`

PrepareToRunPP:
	bash PrepareInput.sh \
		$(PPSignalMC)/ \
		10 LogPP_v10/ $(EOSBase)/OutputPPMC_v10/ \
 		--Fraction 1 `DHQuery Setting.dh PPSignalMC Nominal`

PrepareToRunGenPP:
	bash PrepareInput.sh \
		$(PPSignalMC)/ \
		10 LogGenPP_v10/ $(EOSBase)/OutputPPMCGen_v10/ \
 		--Fraction 1 `DHQuery Setting.dh PPSignalGenMC Nominal`

PrepareToRunPPData:
	bash PrepareInput.sh \
		'$(PPSignalData)/*/' \
		10 LogPPData_v10/ $(EOSBase)/OutputPPData_v10/ \
 		--Fraction 1 `DHQuery Setting.dh PPSignalData Nominal`

PrepareToRunBackground:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		10 LogDatabkg_v10/ $(EOSBase)/OutputDatabkg_v10/ \
		--Background /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_10.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_13.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_22.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_34.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_37.root \
		`DHQuery Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomBackground:
	bash PrepareInputRandomBackground.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		10 LogDatabkg_v10/ $(EOSBase)/OutputDatabkg_v10/ \
		$(PbPbBackgroundData)/ 100 \
		`DHQuery Setting.dh PbPbBackgroundData Nominal`

PrepareToRunMCBackground:
	bash PrepareInput.sh \
		$(PbPbSignalMC) \
		1 LogMCBackground_v10/ $(EOSBase)/OutputMCBackground_v10/ \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_11.root,$(PbPbBackgroundMC)/HiForestMiniAOD_12.root,$(PbPbBackgroundMC)/HiForestMiniAOD_13.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root,$(PbPbBackgroundMC)/HiForestMiniAOD_17.root,$(PbPbBackgroundMC)/HiForestMiniAOD_18.root,$(PbPbBackgroundMC)/HiForestMiniAOD_19.root,$(PbPbBackgroundMC)/HiForestMiniAOD_1.root,$(PbPbBackgroundMC)/HiForestMiniAOD_20.root \
		`DHQuery Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomMCBackground:
	bash PrepareInputRandomBackground.sh \
		$(PbPbSignalMC) \
		1 LogMCBackground_v10/ $(EOSBase)/OutputMCBackground_v10/ \
		$(PbPbBackgroundMC)/ 10 \
		`DHQuery Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomMCGenBackground:
	bash PrepareInputRandomBackground.sh \
		$(PbPbSignalMC) \
		10 LogMCGenbkg_v10/ $(EOSBase)/OutputMCbkgGen_v10/ \
		$(PbPbBackgroundMC)/ 12 \
 		`DHQuery Setting.dh PbPbBackgroundGenMC Nominal`

