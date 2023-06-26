#!/bin/bash

mkdir -p Plots

for CRange in 0:30 0:10 10:30 30:90 30:50 50:90
do
   CMin=`echo $CRange | tr ':' ' ' | awk '{print $1}'`
   CMax=`echo $CRange | tr ':' ' ' | awk '{print $2}'`

   Tags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_10
   SecondTags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_1
   Labels="1 < p_{T}^{trk} < 2 GeV","2 < p_{T}^{trk} < 4 GeV","4 < p_{T}^{trk} < 10 GeV"
   PPExtraInfo="p_{T}^{Z} > 40 GeV"
   ExtraInfo="p_{T}^{Z} > 40 GeV,${CMin}-${CMax}%"
   Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.1415926535 --YMin -5 --YMax 10 --RMin -1.9 --RMax 1.9 --LegendLeft 0.08 --LegendBottom 0.40"
   Suffix="C${CMin}${CMax}"
   
   # Muon matching
   ./Execute --OutputBase Plots/SysPbPbMuMatch$Suffix \
      --DataFiles Root/Data.root,Root/DataMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","Muon match" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysPPMuMatch \
      --DataFiles Root/PPData.root,Root/PPDataMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal pp","Muon match" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $Plotting
   
   # Background subtraction
   ./Execute --OutputBase Plots/SysPbPbUE25$Suffix \
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
      --Tags "$Tags" --SecondTags "$SecondTags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $Plotting
   
   # Lepton SF variation
   ./Execute --OutputBase Plots/SysPbPbSF1Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight0.root,Root/DataExtraZWeight1.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk sys up","glbPFtrk sys down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysPbPbSF2Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight2.root,Root/DataExtraZWeight3.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid sys up","muid sys down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysPbPbSF3Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight4.root,Root/DataExtraZWeight5.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig sys up","trig sys down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysPbPbSF1Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight6.root,Root/DataExtraZWeight7.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk stat up","glbPFtrk stat down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysPbPbSF2Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight8.root,Root/DataExtraZWeight9.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid stat up","muid stat down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysPbPbSF3Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight10.root,Root/DataExtraZWeight11.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig stat up","trig stat down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   
   # Centrality definition
   ./Execute --OutputBase Plots/SysPbPbCent$Suffix \
      --DataFiles Root/Data.root,Root/DataHiBinUp.root,Root/DataHiBinDown.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","hiBin up","hiBin down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
done
   
