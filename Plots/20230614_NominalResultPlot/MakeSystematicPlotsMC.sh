#!/bin/bash

mkdir -p Plots/SysMC

for CRange in 0:30 0:10 10:30 30:90 30:50 50:90
do
   CMin=`echo $CRange | tr ':' ' ' | awk '{print $1}'`
   CMax=`echo $CRange | tr ':' ' ' | awk '{print $2}'`

   Tags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_10
   SecondTags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_1
   Labels="1 < p_{T}^{trk} < 2 GeV","2 < p_{T}^{trk} < 4 GeV","4 < p_{T}^{trk} < 10 GeV"
   PPExtraInfo="40 < p_{T}^{Z} < 200 GeV"
   ExtraInfo="40 < p_{T}^{Z} < 200 GeV,${CMin}-${CMax}%"
   Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.1415926535 --YMin -7 --YMax 10 --RMin -1.9 --RMax 1.9 --LegendLeft 0.08 --LegendBottom 0.40"
   PlottingY="--XAxisLabel |#Deltay_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.2 --YMin -200 --YMax 200 --RMin -7 --RMax 7 --LegendLeft 0.08 --LegendBottom 0.40"

   Suffix="C${CMin}${CMax}"
   
   
   # Background subtraction
   ./Execute --OutputBase Plots/SysMC/SysPbPbUE25$Suffix \
      --DataFiles Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","UE up","UE down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbYUE25$Suffix \
      --DataFiles Root/MCMix.root,Root/MCMixUEUp25.root,Root/MCMixUEDown25.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","UE up","UE down" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   


   # Track selection
   ./Execute --OutputBase Plots/SysMC/SysPbPbTrk$Suffix \
      --DataFiles Root/MC.root,Root/MCLoose.root,Root/MCTight.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","Loose track selection","Tight track selection" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbYTrk$Suffix \
      --DataFiles Root/MC.root,Root/MCLoose.root,Root/MCTight.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","Loose track selection","Tight track selection" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY

   # VZ cut
   #./Execute --OutputBase Plots/SysMC/SysPbPbVZ$Suffix \
   #   --DataFiles Root/MC.root,Root/MC_VZ1.root,Root/MC_VZ2.root,Root/MC_VZ3.root,Root/MC_VZ4.root --SkipSystematics true \
   #   --CurveLabels "Nominal PbPb","v_{z} < -5 cm","-5 < v_{z} < 0 cm","0 < v_{z} < 5 cm","v_{z} > 5 cm" \
   #   --ToPlot "DeltaPhi" \
   #   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   #   $Plotting
   #./Execute --OutputBase Plots/SysMC/SysPbPbYVZ$Suffix \
   #   --DataFiles Root/MC.root,Root/MC_VZ1.root,Root/MC_VZ2.root,Root/MC_VZ3.root,Root/MC_VZ4.root --SkipSystematics true \
   #   --CurveLabels "Nominal PbPb","v_{z} < -5 cm","-5 < v_{z} < 0 cm","0 < v_{z} < 5 cm","v_{z} > 5 cm" \
   #   --ToPlot "DeltaY" \
   #   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   #   $PlottingY
   ./Execute --OutputBase Plots/SysMC/SysPbPbVZ$Suffix \
      --DataFiles Root/MC.root,Root/MC_VZ10.root,Root/MC_VZ20.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","|v_{z}| < 10 cm","|v_{z}| < 20 cm" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbYVZ$Suffix \
      --DataFiles Root/MC.root,Root/MC_VZ10.root,Root/MC_VZ20.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","|v_{z}| < 10 cm","|v_{z}| < 20 cm" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY

done
   
