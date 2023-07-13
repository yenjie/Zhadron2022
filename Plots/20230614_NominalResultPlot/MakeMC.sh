#!/bin/bash

mkdir -p Plots

for CRange in 0:30 0:10 10:30 30:90 30:50 50:90
do
   CMin=`echo $CRange | tr ':' ' ' | awk '{print $1}'`
   CMax=`echo $CRange | tr ':' ' ' | awk '{print $2}'`

   Tags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_10
   SecondTags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_1
   Labels="1 < p_{T}^{trk} < 2 GeV","2 < p_{T}^{trk} < 4 GeV","4 < p_{T}^{trk} < 10 GeV"
   PPExtraInfo="200 > p_{T}^{Z} > 40 GeV"
   ExtraInfo="200 > p_{T}^{Z} > 40 GeV,${CMin}-${CMax}%"
   Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.1415926535 --YMin -5 --YMax 10 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"
   Suffix="C$CMin$CMax"

   ./Execute --OutputBase Plots/ResultMC$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root --SkipSystematics false \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

   Plotting="--XAxisLabel |#Delta#eta_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.2 --YMin -5 --YMax 10 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"

   ./Execute --OutputBase Plots/ResultMCEta$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaEta" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultMCEtaJetSide$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaEtaJetSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultMCEtaZSide$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaEtaZSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

   ./Execute --OutputBase Plots/ResultMCEtaOnePercent$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SubtractFudgeFactor 1.01 \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaEta" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultMCEtaTwoPercent$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SubtractFudgeFactor 1.02 \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaEta" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultMCEtaThreePercent$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SubtractFudgeFactor 1.03 \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaEta" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   
   Plotting="--XAxisLabel |#Delta#eta_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.2 --YMin 0 --YMax 30 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"
   
   ./Execute --OutputBase Plots/ResultMCEtaNoSubtract$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root,Root/MCMix.root --SkipSystematics true --SkipSelfSubtract true \
      --SubtractFiles None,None,Root/MCMix.root,Root/MCMixUEDown25.root,None --SkipSubtract false \
      --SubtractFudgeFactor 1.00 \
      --CurveLabels "pp","PbPb","PbPb Subtracted","PbPb Subtracted (-2.5%)","PbPb Mix" \
      --ToPlot "DeltaEta" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

   Plotting="--XAxisLabel |#Deltay_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.2 --YMin -5 --YMax 10 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"

   ./Execute --OutputBase Plots/ResultMCY$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultMCYJetSide$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaYJetSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultMCYZSide$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaYZSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

   ./Execute --OutputBase Plots/ResultMCYOnePercent$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SubtractFudgeFactor 1.01 \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultMCYTwoPercent$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SubtractFudgeFactor 1.02 \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/ResultMCYThreePercent$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root \
      --SubtractFiles None,Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSubtract false \
      --SubtractFudgeFactor 1.03 \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root,None,None --SkipSystematics false \
      --CurveLabels "pp","PbPb","PbPb UE+2.5%","PbPb UE-2.5%" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   
   Plotting="--XAxisLabel |#Deltay_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.2 --YMin 0 --YMax 30 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"
   
   ./Execute --OutputBase Plots/ResultMCYNoSubtract$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root,Root/MCMix.root --SkipSystematics true --SkipSelfSubtract true \
      --SubtractFiles None,None,Root/MCMix.root,Root/MCMixUEDown25.root,None --SkipSubtract false \
      --SubtractFudgeFactor 1.00 \
      --CurveLabels "pp","PbPb","PbPb Subtracted","PbPb Subtracted (-2.5%)","PbPb Mix" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting



   Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.2 --YMin 0 --YMax 30 --RMin -5 --RMax 5 --LegendLeft 0.08 --LegendBottom 0.40"
   
   ./Execute --OutputBase Plots/ResultMCNoSubtract$Suffix \
      --DataFiles Root/PPMC.root,Root/MC.root,Root/MC.root,Root/MC.root,Root/MCMix.root --SkipSystematics true --SkipSelfSubtract true \
      --SubtractFiles None,None,Root/MCMix.root,Root/MCMixUEDown25.root,None --SkipSubtract false \
      --SubtractFudgeFactor 1.00 \
      --CurveLabels "pp","PbPb","PbPb Subtracted","PbPb Subtracted (-2.5%)","PbPb Mix" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
done



