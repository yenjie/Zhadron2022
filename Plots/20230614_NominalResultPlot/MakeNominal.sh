#!/bin/bash

Tags=Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_0_10,Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_0_10
SecondTags=Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_0_1,Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_0_1
Labels="1 < p_{T}^{trk} < 2 GeV","2 < p_{T}^{trk} < 5 GeV","5 < p_{T}^{trk} < 10 GeV"
PPExtraInfo="p_{T}^{Z} > 40 GeV"
ExtraInfo="p_{T}^{Z} > 40 GeV,0-30%"
Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.1415926535 --YMin -5 --YMax 10 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"
Suffix="C030"

mkdir -p Plots

./Execute --OutputBase Plots/ResultNominal$Suffix \
   --DataFiles Root/PPData.root,Root/Data.root --SkipSystematics true \
   --CurveLabels "pp","PbPb" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting

Tags=Centrality_30_90_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_30_90_ZPT_40_200_TrackPT_20_50_PV_0_10,Centrality_30_90_ZPT_40_200_TrackPT_50_100_PV_0_10
SecondTags=Centrality_30_90_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_30_90_ZPT_40_200_TrackPT_20_50_PV_0_1,Centrality_30_90_ZPT_40_200_TrackPT_50_100_PV_0_1
ExtraInfo="p_{T}^{Z} > 40 GeV,30-90%"
Suffix="C3090"

./Execute --OutputBase Plots/ResultNominal$Suffix \
   --DataFiles Root/PPData.root,Root/Data.root --SkipSystematics true \
   --CurveLabels "pp","PbPb" \
   --ToPlot "DeltaPhi" \
   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   $Plotting


