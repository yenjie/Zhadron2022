

default: TestRunGenRecoPlot

Prepare:
	ln -sf /eos/cms/store/group/phys_heavyions/pchou/ PinChunOutput

TestRun: Execute
	./Execute --Input PinChunOutput/OutputData_v14/Result14.root --Output Test.root

TestRunPlot: ExecutePlot
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_0_1      --Output Plots_0_30_40_1_2.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_0_1      --Output Plots_0_30_40_2_5.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_0_1     --Output Plots_0_30_40_5_10.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_100_1000_PV_0_1   --Output Plots_0_30_40_10_100.pdf
	./ExecutePlot --Tag Centrality_30_90_ZPT_40_200_TrackPT_10_20_PV_0_1     --Output Plots_30_90_40_1_2.pdf
	./ExecutePlot --Tag Centrality_30_90_ZPT_40_200_TrackPT_20_50_PV_0_1     --Output Plots_30_90_40_2_5.pdf
	./ExecutePlot --Tag Centrality_30_90_ZPT_40_200_TrackPT_50_100_PV_0_1    --Output Plots_30_90_40_5_10.pdf
	./ExecutePlot --Tag Centrality_30_90_ZPT_40_200_TrackPT_100_1000_PV_0_1  --Output Plots_30_90_40_10_100.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_2_10     --Output PlotsPV_0_30_40_1_2.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_2_10     --Output PlotsPV_0_30_40_2_5.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_2_10    --Output PlotsPV_0_30_40_5_10.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_100_1000_PV_2_10  --Output PlotsPV_0_30_40_10_100.pdf
	cp Plots*.pdf ~/public/html/

TestRunPUPlot: ExecutePUPlot
	./ExecutePUPlot

TestRunGenRecoPlot: ExecuteGenRecoPlot
	./ExecuteGenRecoPlot --Gen PPMCGen.root --Reco PPMC.root --OutputTag PP \
		--Tag Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen MCGen.root --Reco MC.root --OutputTag PbPb0To30 \
		--Tag Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen MCGen.root --Reco MC.root --OutputTag PbPb30To90 \
		--Tag Centrality_30_90_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen PPMCGen.root --Reco PPMCNoResidual.root --OutputTag PPNoResidual \
		--Tag Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen MCGen.root --Reco MCNoResidual.root --OutputTag PbPb0To30NoResidual \
		--Tag Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen MCGen.root --Reco MCNoResidual.root --OutputTag PbPb30To90NoResidual \
		--Tag Centrality_30_90_ZPT_40_200_TrackPT_10_1000_PV_0_10

Execute: FillHistogram.cpp
	g++ FillHistogram.cpp -o Execute `root-config --cflags --libs` \
		-I$(ProjectBase)/CommonCode/include $(ProjectBase)/CommonCode/library/*.o

RunAll: RunMix RunNoMix

RunMix: RunDataMix RunMCMix

RunNoMix: RunData RunMC RunPPMC RunPPData

RunData: Execute
	./Execute --Input `ls PinChunOutput/OutputData_v14/*root | tr '\n' ','` --Output Data.root --IsPP false --IsMC false

RunDataMix: Execute
	./Execute --Input `ls PinChunOutput/OutputDatabkg_v14/*root | tr '\n' ','` --Output DataMix.root --IsPP false --IsMC false

RunMC: Execute
	./Execute --Input `ls PinChunOutput/OutputMC_v14/*root | tr '\n' ','` --Output MC.root --IsPP false --IsMC true --Fraction 1.0 

RunMCMix: Execute
	./Execute --Input `ls PinChunOutput/OutputMCBackground_v14/*root | tr '\n' ','` --Output MCMix.root --IsPP false --IsMC true

RunPPMC: Execute
	./Execute --Input `ls PinChunOutput/OutputPPMC_v14/*root | tr '\n' ','` --Output PPMC.root --Fraction 0.1 --IsPP true --IsMC true

RunPPData: Execute
	./Execute --Input `ls PinChunOutput/OutputPPData_v14/*root | tr '\n' ','` --Output PPData.root --Fraction 0.1 --IsPP true --IsMC false

ExecutePlot: MakePlots.cpp
	g++ MakePlots.cpp -o ExecutePlot `root-config --cflags --libs` \
		-I$(ProjectBase)/CommonCode/include

ExecutePUPlot: MakePUPlots.cpp
	g++ MakePUPlots.cpp -o ExecutePUPlot `root-config --cflags --libs` \
		-I$(ProjectBase)/CommonCode/include

ExecuteGenRecoPlot: MakeGenRecoClosure.cpp
	g++ MakeGenRecoClosure.cpp -o ExecuteGenRecoPlot `root-config --cflags --libs` \
		-I$(ProjectBase)/CommonCode/include

