PbPbBackgroundData   := $(shell DHQuery Setting.dh Sample PbPbBackgroundData)
PbPbSignalDoubleMuon  = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/
PbPbSignalSingleMuon := $(shell DHQuery Setting.dh Sample PbPbSignalData)
PbPbSignalMC         := $(shell DHQuery Setting.dh Sample PbPbSignalMC)
PbPbBackgroundMC     := $(shell DHQuery Setting.dh Sample PbPbBackgroundMC)
PPSignalMC           := $(shell DHQuery Setting.dh Sample PPSignalMC)
PPSignalData         := $(shell DHQuery Setting.dh Sample PPSignalData)

#YiEOS =  /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230310_ZHadronSkims/
#EOSBase = /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230625_ZHadronSkims
EOSBase = /eos/cms/store/group/phys_heavyions/pchou
#CERNBOX = /eos/home-p/pchou

default: Prepare TestRun

Prepare:
	#ln -sf $(ProjectBase)/Skims/20230310_ZHadronSkims/Setting.dh .
	bash DefineNominalSetting.sh
	chmod u+x Expand
	
Execute: DoZHadronSkim.cpp
	g++ DoZHadronSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o

TestRun: Execute
	./Execute --Input $(EOSBase)/OutputMC_v17_PFmuon/Result10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbBackgroundMC Nominal` \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root \
		--ReuseBackground true

TestRunMCGenBackground: Execute
	./Execute --Input $(EOSBase)/OutputMCGen_v17_PFmuon/Result10.root \
		--Output /tmp/$(USER)/TestMCGen.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbBackgroundGenMC Nominal` \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root \
		--ReuseBackground true

TestRunRandomMCSigBkg: Execute
	./Execute --Input $(EOSBase)/OutputMC_v17_PFmuon/Result10.root \
		--Output /tmp/$(USER)/TestMCSigBkg.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbSignalMC Nominal` \
		--Background $(PbPbSignalMC)/HiForestMiniAOD_10.root,$(PbPbSignalMC)/HiForestMiniAOD_14.root,$(PbPbSignalMC)/HiForestMiniAOD_15.root,$(PbPbSignalMC)/HiForestMiniAOD_16.root \
		--ReuseBackground true --CheckForBackgroundZ true

TestRunRandomDataSigBkg: Execute
	./Execute --Input $(EOSBase)/OutputData_v17_PFmuon/Result10.root \
		--Output /tmp/$(USER)/TestDataSigBkg.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbSignalData Nominal` \
		--Background $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_10.root,$(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root,$(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_15.root,$(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_16.root \
		--ReuseBackground true --CheckForBackgroundZ true

PrepareToRunRandomMCBackground:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackground_v17_PFmuon/ $(EOSBase)/OutputMCBackground_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomDataBackground:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackground_v17_PFmuon/ $(EOSBase)/OutputDataBackground_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData Nominal`

PrepareToRunRandomMCGenBackground:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMCGen_v17_PFmuon/ LogMCGenbkg_v17_PFmuon/ $(EOSBase)/OutputMCGenbkg_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundGenMC Nominal`

PrepareToRunRandomMCBackgroundUEUp25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEUp25_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEUp25_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp25`

PrepareToRunRandomDataBackgroundUEUp25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackgroundUEUp25_v17_PFmuon/ $(EOSBase)/OutputDataBackgroundUEUp25_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEUp25`

PrepareToRunRandomMCBackgroundUEDown25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEDown25_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEDown25_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown25`

PrepareToRunRandomDataBackgroundUEDown25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackgroundUEDown25_v17_PFmuon/ $(EOSBase)/OutputDataBackgroundUEDown25_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEDown25`

PrepareToRunRandomMCBackgroundUEUp30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEUp30_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEUp30_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp30`

PrepareToRunRandomDataBackgroundUEUp30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackgroundUEUp30_v17_PFmuon/ $(EOSBase)/OutputDataBackgroundUEUp30_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEUp30`

PrepareToRunRandomMCBackgroundUEDown30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEDown30_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEDown30_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown30`

PrepareToRunRandomDataBackgroundUEDown30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackgroundUEDown30_v17_PFmuon/ $(EOSBase)/OutputDataBackgroundUEDown30_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEDown30`

PrepareToRunRandomMCBackgroundUEUp50:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEUp50_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEUp50_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp50`

PrepareToRunRandomMCBackgroundUEDown50:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEDown50_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEDown50_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown50`

PrepareToRunRandomMCBackgroundUEUp100:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEUp100_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEUp100_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp100`

PrepareToRunRandomMCBackgroundUEDown100:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEDown100_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEDown100_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown100`

PrepareToRunRandomMCBackgroundUEUp200:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEUp200_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEUp200_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp200`

PrepareToRunRandomMCBackgroundUEDown200:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEDown200_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEDown200_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown200`

PrepareToRunRandomMCBackgroundUEUp500:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEUp500_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEUp500_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp500`

PrepareToRunRandomMCBackgroundUEDown500:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEDown500_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEDown500_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown500`

PrepareToRunRandomMCBackgroundUEUp1000:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEUp1000_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEUp1000_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp1000`

PrepareToRunRandomMCBackgroundUEDown1000:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEDown1000_v17_checkz/ $(EOSBase)/OutputMCBackgroundUEDown1000_v17_checkz/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown1000`

PrepareToRunRandomMCSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCSigBkg_v17b_ov10_50/ $(EOSBase)/OutputMCSigBkg_v17b_ov10_50/ $(PbPbSignalMC)/ 50 \
		`./Expand Setting.dh PbPbSignalMC Nominal`

PrepareToRunRandomDataSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataSigBkg_v17b_checkz/ $(EOSBase)/OutputDataSigBkg_v17b_checkz/ '$(PbPbSignalSingleMuon)/*/' 200 \
		`./Expand Setting.dh PbPbSignalData Nominal`

PrepareToRunRandomMCGenSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMCGen_v17_PFmuon/ LogMCGenSigBkg_v17b_checkz/ $(EOSBase)/OutputMCGenSigBkg_v17b_checkz/ $(PbPbSignalMC)/ 10 \
		`./Expand Setting.dh PbPbSignalGenMC Nominal`

PrepareToRunRandomPPMCSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputPPMC_v17_PFmuon/ LogPPMCSigBkg_v17b_ov10_50/ $(EOSBase)/OutputPPMCSigBkg_v17b_ov10_50/ $(PPSignalMC)/ 50 \
		`./Expand Setting.dh PPSignalMC Nominal`

PrepareToRunRandomPPDataSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputPPData_v17_PFmuon/ LogPPDataSigBkg_v17b_checkz/ $(EOSBase)/OutputPPDataSigBkg_v17b_checkz/ '$(PPSignalData)/*/' 200 \
		`./Expand Setting.dh PPSignalData Nominal`

PrepareToRunRandomMCSigBkgCent10:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCSigBkg_v17b_rejZ_Cent10/ $(EOSBase)/OutputMCSigBkg_v17b_rejZ_Cent10/ $(PbPbSignalMC)/ 10 \
		`./Expand Setting.dh PbPbSignalMCCent10 Nominal`

PrepareToRunRandomPPMCSigBkgCent10:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputPPMC_v17_PFmuon/ LogPPMCSigBkg_v17b_rejZ_Cent10/ $(EOSBase)/OutputPPMCSigBkg_v17b_rejZ_Cent10/ $(PPSignalMC)/ 10 \
		`./Expand Setting.dh PPSignalMCCent10 Nominal`