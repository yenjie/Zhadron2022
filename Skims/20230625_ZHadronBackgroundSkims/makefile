PbPbBackgroundData   := $(shell DHQuery Setting.dh Sample PbPbBackgroundData)
PbPbSignalDoubleMuon  = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/
PbPbSignalSingleMuon := $(shell DHQuery Setting.dh Sample PbPbSignalData)
PbPbSignalMC         := $(shell DHQuery Setting.dh Sample PbPbSignalMC)
PbPbBackgroundMC     := $(shell DHQuery Setting.dh Sample PbPbBackgroundMC)
PPSignalMC           := $(shell DHQuery Setting.dh Sample PPSignalMC)
PPSignalData         := $(shell DHQuery Setting.dh Sample PPSignalData)

#EOSBase = /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230625_ZHadronSkims
EOSBase = /eos/cms/store/group/phys_heavyions/pchou

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
	./Execute --Input $(EOSBase)/OutputMC_v14/Result10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbBackgroundMC Nominal` \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root \
		--ReuseBackground true

TestRunMCGenBackground: Execute
	./Execute --Input $(EOSBase)/OutputMCGen_v14/Result10.root \
		--Output /tmp/$(USER)/TestMCGen.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbBackgroundGenMC Nominal` \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root \
		--ReuseBackground true

PrepareToRunRandomMCBackground:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v14/ LogMCBackground_v15b/ $(EOSBase)/OutputMCBackground_v15b/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomDataBackground:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v14/ LogDataBackground_v15b/ $(EOSBase)/OutputDataBackground_v15b/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData Nominal`

PrepareToRunRandomMCGenBackground:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMCGen_v14/ LogMCGenbkg_v15b/ $(EOSBase)/OutputMCGenbkg_v15b/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundGenMC Nominal`

PrepareToRunRandomMCBackgroundUEUp25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v14/ LogMCBackgroundUEUp25_v15b/ $(EOSBase)/OutputMCBackgroundUEUp25_v15b/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp25`

PrepareToRunRandomDataBackgroundUEUp25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v14/ LogDataBackgroundUEUp25_v15b/ $(EOSBase)/OutputDataBackgroundUEUp25_v15b/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEUp25`

PrepareToRunRandomMCBackgroundUEDown25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v14/ LogMCBackgroundUEDown25_v15b/ $(EOSBase)/OutputMCBackgroundUEDown25_v15b/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown25`

PrepareToRunRandomDataBackgroundUEDown25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v14/ LogDataBackgroundUEDown25_v15b/ $(EOSBase)/OutputDataBackgroundUEDown25_v15b/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEDown25`

PrepareToRunRandomMCBackgroundUEUp30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v14/ LogMCBackgroundUEUp30_v15b/ $(EOSBase)/OutputMCBackgroundUEUp30_v15b/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp30`

PrepareToRunRandomDataBackgroundUEUp30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v14/ LogDataBackgroundUEUp30_v15b/ $(EOSBase)/OutputDataBackgroundUEUp30_v15b/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEUp30`

PrepareToRunRandomMCBackgroundUEDown30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v14/ LogMCBackgroundUEDown30_v15b/ $(EOSBase)/OutputMCBackgroundUEDown30_v15b/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown30`

PrepareToRunRandomDataBackgroundUEDown30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v14/ LogDataBackgroundUEDown30_v15b/ $(EOSBase)/OutputDataBackgroundUEDown30_v15b/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEDown30`
