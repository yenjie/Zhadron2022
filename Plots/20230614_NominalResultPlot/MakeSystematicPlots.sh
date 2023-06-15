#!/bin/bash

Tags=Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_0_10,Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_0_10
SecondTags=Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_0_1,Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_0_1
Labels="1 < p_{T}^{trk} < 2 GeV","2 < p_{T}^{trk} < 5 GeV","5 < p_{T}^{trk} < 10 GeV"
ExtraInfo="p_{T}^{Z} > 40 GeV"
Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.1415926535 --YMin -5 --YMax 10 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"

mkdir -p Plots

# Muon matching
./Execute --OutputBase Plots/SysPbPbMuMatch \
   --DataFiles Root/Data.root,Root/DataMuMatch.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","Muon match" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting
./Execute --OutputBase Plots/SysPPMuMatch \
   --DataFiles Root/PPData.root,Root/PPDataMuMatch.root --SkipSystematics true \
   --CurveLabels "Nominal pp","Muon match" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting

# Background subtraction
./Execute --OutputBase Plots/SysPbPbUE25 \
   --DataFiles Root/DataMix.root,Root/DataMixUEUp25.root,Root/DataMixUEDown25.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","UE up","UE down" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting

# Non-closure

# pp PU
./Execute --OutputBase Plots/SysPPPU \
   --DataFiles Root/PPData.root,Root/PPData.root --SkipSystematics true \
   --CurveLabels "Nominal","PV = 1" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --SecondTags "$SecondTags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting

# Lepton SF variation
./Execute --OutputBase Plots/SysPbPbSF1Sys \
   --DataFiles Root/Data.root,Root/DataExtraZWeight0.root,Root/DataExtraZWeight1.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","glbPFtrk sys up","glbPFtrk sys down" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting
./Execute --OutputBase Plots/SysPbPbSF2Sys \
   --DataFiles Root/Data.root,Root/DataExtraZWeight2.root,Root/DataExtraZWeight3.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","muid sys up","muid sys down" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting
./Execute --OutputBase Plots/SysPbPbSF3Sys \
   --DataFiles Root/Data.root,Root/DataExtraZWeight4.root,Root/DataExtraZWeight5.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","trig sys up","trig sys down" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting
./Execute --OutputBase Plots/SysPbPbSF1Stat \
   --DataFiles Root/Data.root,Root/DataExtraZWeight6.root,Root/DataExtraZWeight7.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","glbPFtrk stat up","glbPFtrk stat down" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting
./Execute --OutputBase Plots/SysPbPbSF2Stat \
   --DataFiles Root/Data.root,Root/DataExtraZWeight8.root,Root/DataExtraZWeight9.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","muid stat up","muid stat down" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting
./Execute --OutputBase Plots/SysPbPbSF3Stat \
   --DataFiles Root/Data.root,Root/DataExtraZWeight10.root,Root/DataExtraZWeight11.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","trig stat up","trig stat down" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting

# Centrality definition
./Execute --OutputBase Plots/SysPbPbCent \
   --DataFiles Root/Data.root,Root/DataHiBinUp.root,Root/DataHiBinDown.root --SkipSystematics true \
   --CurveLabels "Nominal PbPb","hiBin up","hiBin down" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting


