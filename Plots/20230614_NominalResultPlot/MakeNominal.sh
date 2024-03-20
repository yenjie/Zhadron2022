#!/bin/bash

mkdir -p Plots

for CRange in 0:30 0:10 10:30 30:90 30:50 50:90 50:70 70:90
do
   CMin=`echo $CRange | tr ':' ' ' | awk '{print $1}'`
   CMax=`echo $CRange | tr ':' ' ' | awk '{print $2}'`

   Tags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_10
   SecondTags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_1
   Labels="1 < p_{T}^{trk} < 2 GeV","2 < p_{T}^{trk} < 4 GeV","4 < p_{T}^{trk} < 10 GeV"
   PPExtraInfo="p_{T}^{Z} > 40 GeV"
   ExtraInfo="p_{T}^{Z} > 40 GeV,${CMin}-${CMax}%"
   Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.1415926535 --YMin -5 --YMax 10 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"
   Suffix="C$CMin$CMax"

   ./Execute --OutputBase Plots/ResultNominal$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root --SkipSystematics false \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

   Plotting="--XAxisLabel |#Delta#eta_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.2 --YMin -5 --YMax 10 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"

   ./Execute --OutputBase Plots/ResultNominalEta$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root --SkipSystematics false \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaEta" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultNominalEtaJetSide$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root --SkipSystematics false \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaEtaJetSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultNominalEtaZSide$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root --SkipSystematics false \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaEtaZSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

done



