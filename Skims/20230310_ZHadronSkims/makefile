PbPbBackgroundData = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias7/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias7/20221101_ZHadronMinimumBias7WithMuTree/221101_212932/0000/
PbPbBackgroundMCOld = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/
PbPbSignalDoubleMuon = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/
PbPbSignalSingleMuon = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20230501_ZHadronSingleMuonWithMuTree/230501_155126/
PbPbSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20230501_ZHadronMCDY/230501_155504/0000/
PbPbBackgroundMC = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/
PPSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230407_ZHadronMLLWithMuTreePP/230407_143418/0000/
# PPSignalMC = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20230405_ZHadronMLLWithMuTreePP/230405_101901/0000/
PPSignalData = /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/SingleMuon/Run2017G-17Nov2017-v1/AOD/SingleMuon/20230405_ZHadronSingleMuonWithMuTreePP/230405_185259/
JECBase = $(ProjectBase)/CommonCode/text/JEC/Autumn18_HI_RAAV3_DATA/
JECBaseMC = $(ProjectBase)/CommonCode/text/JEC/Autumn18_HI_RAAV3_MC/
JECBasePP = $(ProjectBase)/CommonCode/text/JEC/Spring18_ppRef5TeV_RAAV3_DATA/
JECBasePPMC = $(ProjectBase)/CommonCode/text/JEC/Spring18_ppRef5TeV_RAAV3_MC/

default: TestRun

TestRun: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --DoGenLevel false --IsData true --IsPP false --MinZPT 5 --MinTrackPT 0.5 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBase)/Autumn18_HI_RAAV3_DATA_L2Relative_AK3PF.txt,$(JECBase)/Autumn18_HI_RAAV3_DATA_L2L3Residual_AK3PF.txt

TestRunMC: Execute
	time ./Execute --Input PbPbMC/HiForestMiniAOD_211.root \
		--Output /tmp/$(USER)/TestMC.root --Fraction 0.02 --DoGenLevel true --DoGenCorrelation false --IsData false --IsPP false --MinZPT 5 --DoExtraAxes true \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

TestRunGen: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_114.root \
		--Output /tmp/$(USER)/TestGenMC.root --Fraction 0.1 --DoGenLevel true --DoGenCorrelation true --IsData false --IsPP false --MinZPT 5 --DoExtraAxes true \
		--DoTrackEfficiency false --GenCorrelationCharged true \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

TestRunGenPP: Execute
	./Execute --Input $(PPSignalMC)/HiForestAOD_12.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --DoGenLevel true --DoGenCorrelation true --IsData false --IsPP true --MinZPT 5 \
		--DoTrackEfficiency false --GenCorrelationCharged true \
		--DoJet true --Jet "ak3PFJetAnalyzer/t" \
		--JEC $(JECBasePPMC)/Spring18_ppRef5TeV_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBasePPMC)/Spring18_ppRef5TeV_RAAV3_MC_L2L3Residual_AK3PF.txt

TestRunBackground: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundData)/HiForestMiniAOD_118.root,$(PbPbBackgroundData)/HiForestMiniAOD_123.root,$(PbPbBackgroundData)/HiForestMiniAOD_127.root,$(PbPbBackgroundData)/HiForestMiniAOD_138.root,$(PbPbBackgroundData)/HiForestMiniAOD_148.root,$(PbPbBackgroundData)/HiForestMiniAOD_16.root,$(PbPbBackgroundData)/HiForestMiniAOD_17.root,$(PbPbBackgroundData)/HiForestMiniAOD_184.root,$(PbPbBackgroundData)/HiForestMiniAOD_18.root,$(PbPbBackgroundData)/HiForestMiniAOD_194.root \
		--HFShift 660 --Tolerance 0 --ToleranceFraction 0.01 --Oversample 10  --HFCeiling 70000 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBase)/Autumn18_HI_RAAV3_DATA_L2Relative_AK3PF.txt,$(JECBase)/Autumn18_HI_RAAV3_DATA_L2L3Residual_AK3PF.txt

TestRunPP: Execute
	./Execute --Input $(PPSignalMC)/HiForestAOD_12.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --DoGenLevel true --IsData false --IsPP true --MinZPT 5 --DoSumET false \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ --PFTree "pfcandAnalyzer/pfTree" \
		--DoJet true --Jet "ak3PFJetAnalyzer/t" \
		--JEC $(JECBasePP)/Spring18_ppRef5TeV_RAAV3_DATA_L2Relative_AK3PF.txt,$(JECBasePP)/Spring18_ppRef5TeV_RAAV3_DATA_L2L3Residual_AK3PF.txt

TestRunBackgroundSimple: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 1 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundData)/HiForestMiniAOD_118.root \
		--HFShift 660 --Tolerance 0 --ToleranceFraction 0.01 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBase)/Autumn18_HI_RAAV3_DATA_L2Relative_AK3PF.txt,$(JECBase)/Autumn18_HI_RAAV3_DATA_L2L3Residual_AK3PF.txt

TestRunMCBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --DoGenLevel true --IsData false --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root \
		--HFShift 682 --Tolerance 20 --ToleranceFraction 0.05 --DoSumET false --HFCeiling 134000 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

TestRunMCGenBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --DoGenLevel true --IsData false --IsPP false \
		--DoBackground true --DoGenCorrelation true \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root \
		--HFShift 1083 --Tolerance 10 --ToleranceFraction 0.01 --DoSumET false \
		--DoTrackEfficiency false --GenCorrelationCharged true --VZTolerance 10000 --HFCeiling 156000 \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

#BackgroundCount = 37
#BackgroundFiles = `ls $(PbPbBackgroundMC)/* | shuf | head -n$(BackgroundCount) | tr '\n' ',' | sed "s/,$//"`

#37
#BackgroundFiles = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_36.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_21.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_24.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_32.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_5.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_8.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_27.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_12.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_2.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_34.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_4.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_22.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_6.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_15.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_13.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_11.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_30.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_26.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_25.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_7.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_28.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_3.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_29.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_31.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_1.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_37.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_9.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_16.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_33.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_10.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_35.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_23.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_19.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_18.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_14.root

#12
BackgroundFiles = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_36.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_21.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_24.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_32.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_5.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_8.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_27.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_12.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_2.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_34.root,

TestRunRandomMCGenBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --DoGenLevel true --IsData false --IsPP false \
		--DoBackground true --DoGenCorrelation true \
		--Background $(BackgroundFiles) \
		--HFShift 1083 --Tolerance 10 --ToleranceFraction 0.01 --DoSumET false \
		--DoTrackEfficiency false --GenCorrelationCharged true --VZTolerance 10000 --HFCeiling 156000 \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

Execute: DoZHadronSkim.cpp
	g++ DoZHadronSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o \
		# $(FJExtra) $(FJCExtra)

#EOSBase = /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230310_ZHadronSkims
EOSBase = /eos/cms/store/group/phys_heavyions/pchou

PrepareToRun:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		5 LogData_0506/ $(EOSBase)/OutputData_0506/ \
		--Fraction 1 --DoGenLevel false --IsData true --IsPP false --MinZPT 5 --MinTrackPT 0.5 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBase)/Autumn18_HI_RAAV3_DATA_L2Relative_AK3PF.txt,$(JECBase)/Autumn18_HI_RAAV3_DATA_L2L3Residual_AK3PF.txt

PrepareToRunMC:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		5 LogMC_0506/ $(EOSBase)/OutputMC_0506/ \
		--Fraction 1 --DoGenLevel true --IsData false --IsPP false --MinZPT 5 --MinTrackPT 0.5 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

PrepareToRunGenMC:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		5 LogGenMC_0506/ $(EOSBase)/OutputMCGen_0506/ \
 		--Fraction 1 --DoGenLevel true --DoGenCorrelation true --IsData false --IsPP false --MinZPT 5 --MinTrackPT 0.5 \
		--DoTrackEfficiency false --DoSumET false --GenCorrelationCharged true \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

PrepareToRunPP:
	bash PrepareInput.sh \
		$(PPSignalMC)/ \
		10 LogPP_0503/ $(EOSBase)/OutputPPMC_0503/ \
 		--Fraction 1 --DoGenLevel true --IsData false --IsPP true \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ --MinZPT 5 --MinTrackPT 0.5 \
		--DoJet true --Jet "ak3PFJetAnalyzer/t" \
		--JEC $(JECBasePPMC)/Spring18_ppRef5TeV_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBasePPMC)/Spring18_ppRef5TeV_RAAV3_MC_L2L3Residual_AK3PF.txt

PrepareToRunGenPP:
	bash PrepareInput.sh \
		$(PPSignalMC)/ \
		10 LogGenPP_0503/ $(EOSBase)/OutputPPMCGen_0503/ \
 		--Fraction 1 --DoGenLevel true --DoGenCorrelation true --IsData false --IsPP true \
		--DoTrackEfficiency false --MinZPT 5 --MinTrackPT 0.5 --DoSumET false --GenCorrelationCharged true \
		--DoJet true --Jet "ak3PFJetAnalyzer/t" \
		--JEC $(JECBasePPMC)/Spring18_ppRef5TeV_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBasePPMC)/Spring18_ppRef5TeV_RAAV3_MC_L2L3Residual_AK3PF.txt

PrepareToRunPPData:
	bash PrepareInput.sh \
		'$(PPSignalData)/*/' \
		10 LogPPData_0503/ $(EOSBase)/OutputPPData_0503/ \
 		--Fraction 1 --DoGenLevel false --IsData true --IsPP true \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ --MinZPT 5 --MinTrackPT 0.5 \
		--DoJet true --Jet "ak3PFJetAnalyzer/t" \
		--JEC $(JECBasePP)/Spring18_ppRef5TeV_RAAV3_DATA_L2Relative_AK3PF.txt,$(JECBasePP)/Spring18_ppRef5TeV_RAAV3_DATA_L2L3Residual_AK3PF.txt

PrepareToRunBackground:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		10 LogDatabkg_0506/ $(EOSBase)/OutputDatabkg_0506/ \
 		--Fraction 1 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true \
		--Background /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_10.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_13.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_22.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_34.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_37.root \
		--HFShift 660 --Tolerance 0 --ToleranceFraction 0.01 --DoSumET false --Oversample 10 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ --MinZPT 5 --MinTrackPT 0.5 --HFCeiling 70000 \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBase)/Autumn18_HI_RAAV3_DATA_L2Relative_AK3PF.txt,$(JECBase)/Autumn18_HI_RAAV3_DATA_L2L3Residual_AK3PF.txt

PrepareToRunRandomBackground:
	bash PrepareInputRandomBackground.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		10 LogDatabkg_0506/ $(EOSBase)/OutputDatabkg_0506/ \
		$(PbPbBackgroundData)/ 100 \
 		--Fraction 1 --DoGenLevel false --IsData true --IsPP false \
		--DoBackground true --HFShift 660 --Tolerance 0 --ToleranceFraction 0.01 --DoSumET false --Oversample 25 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ --MinZPT 5 --MinTrackPT 0.5 --HFCeiling 70000 \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBase)/Autumn18_HI_RAAV3_DATA_L2Relative_AK3PF.txt,$(JECBase)/Autumn18_HI_RAAV3_DATA_L2L3Residual_AK3PF.txt

PrepareToRunMCBackground:
	bash PrepareInput.sh \
		$(PbPbSignalMC) \
		1 LogMCBackground_0506/ $(EOSBase)/OutputMCBackground_0506/ \
 		--Fraction 1 --DoGenLevel true --IsData false --IsPP false \
		--DoBackground true \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_11.root,$(PbPbBackgroundMC)/HiForestMiniAOD_12.root,$(PbPbBackgroundMC)/HiForestMiniAOD_13.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root,$(PbPbBackgroundMC)/HiForestMiniAOD_17.root,$(PbPbBackgroundMC)/HiForestMiniAOD_18.root,$(PbPbBackgroundMC)/HiForestMiniAOD_19.root,$(PbPbBackgroundMC)/HiForestMiniAOD_1.root,$(PbPbBackgroundMC)/HiForestMiniAOD_20.root \
		--HFShift 682 --Tolerance 20 --ToleranceFraction 0.05 --DoSumET false --Oversample 10 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ --MinZPT 5 --MinTrackPT 0.5 --HFCeiling 134000 \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

PrepareToRunRandomMCBackground:
	bash PrepareInputRandomBackground.sh \
		$(PbPbSignalMC) \
		1 LogMCBackground_0506/ $(EOSBase)/OutputMCBackground_0506/ \
		$(PbPbBackgroundMC)/ 10 \
 		--Fraction 1 --DoGenLevel true --IsData false --IsPP false \
		--DoBackground true --HFShift 682 --Tolerance 20 --ToleranceFraction 0.05 --DoSumET false --Oversample 10 \
		--DoTrackEfficiency true --TrackEfficiencyPath $(ProjectBase)/CommonCode/root/ --MinZPT 5 --MinTrackPT 0.5 --HFCeiling 134000 \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

PrepareToRunRandomMCGenBackground:
	bash PrepareInputRandomBackground.sh \
		$(PbPbSignalMC) \
		10 LogMCGenbkg_0506/ $(EOSBase)/OutputMCbkgGen_0506/ \
		$(PbPbBackgroundMC)/ 12 \
 		--Fraction 1 --DoGenLevel true --DoGenCorrelation true --IsData false --IsPP false \
		--DoBackground true --HFShift 1083 --Tolerance 10 --ToleranceFraction 0.01 --DoSumET false --Oversample 10 \
		--DoTrackEfficiency false --MinZPT 5 --MinTrackPT 0.5 --GenCorrelationCharged true --VZTolerance 10000 --HFCeiling 156000 \
		--DoJet true --Jet "akCs3PFJetAnalyzer/t" \
		--JEC $(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2Relative_AK3PF.txt,$(JECBaseMC)/Autumn18_HI_RAAV3_MC_L2L3Residual_AK3PF.txt

