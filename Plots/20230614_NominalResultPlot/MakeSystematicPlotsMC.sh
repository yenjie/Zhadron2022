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
   
   # Muon matching
   ./Execute --OutputBase Plots/SysMC/SysPbPbMuMatch$Suffix \
      --DataFiles Root/MC.root,Root/MCMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb (#DeltaR > 0.01)","Muon match (#DeltaR > 0.0025)" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPPMuMatch \
      --DataFiles Root/PPMC.root,Root/PPMCMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal pp (#DeltaR > 0.01)","Muon match (#DeltaR > 0.0025)" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbYMuMatch$Suffix \
      --DataFiles Root/MC.root,Root/MCMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb (#DeltaR > 0.01)","Muon match (#DeltaR > 0.0025)" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysMC/SysPPYMuMatch \
      --DataFiles Root/PPMC.root,Root/PPMCMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal pp (#DeltaR > 0.01)","Muon match (#DeltaR > 0.0025)" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $PlottingY
   
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
   
   # Non-closure
   
   # pp PU
   ./Execute --OutputBase Plots/SysMC/SysPPPU \
      --DataFiles Root/PPMC.root,Root/PPMC.root --SkipSystematics true \
      --CurveLabels "Nominal","PV = 1" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --SecondTags "$SecondTags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPPYPU \
      --DataFiles Root/PPMC.root,Root/PPMC.root --SkipSystematics true \
      --CurveLabels "Nominal","PV = 1" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --SecondTags "$SecondTags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $PlottingY
   
   # Lepton SF variation
   ./Execute --OutputBase Plots/SysMC/SysPbPbSF1Sys$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight0.root,Root/MCExtraZWeight1.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk sys up","glbPFtrk sys down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbSF2Sys$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight2.root,Root/MCExtraZWeight3.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid sys up","muid sys down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbSF3Sys$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight4.root,Root/MCExtraZWeight5.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig sys up","trig sys down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbSF1Stat$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight6.root,Root/MCExtraZWeight7.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk stat up","glbPFtrk stat down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbSF2Stat$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight8.root,Root/MCExtraZWeight9.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid stat up","muid stat down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbSF3Stat$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight10.root,Root/MCExtraZWeight11.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig stat up","trig stat down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

   ./Execute --OutputBase Plots/SysMC/SysPbPbYSF1Sys$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight0.root,Root/MCExtraZWeight1.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk sys up","glbPFtrk sys down" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysMC/SysPbPbYSF2Sys$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight2.root,Root/MCExtraZWeight3.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid sys up","muid sys down" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysMC/SysPbPbYSF3Sys$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight4.root,Root/MCExtraZWeight5.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig sys up","trig sys down" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysMC/SysPbPbYSF1Stat$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight6.root,Root/MCExtraZWeight7.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk stat up","glbPFtrk stat down" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysMC/SysPbPbYSF2Stat$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight8.root,Root/MCExtraZWeight9.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid stat up","muid stat down" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysMC/SysPbPbYSF3Stat$Suffix \
      --DataFiles Root/MC.root,Root/MCExtraZWeight10.root,Root/MCExtraZWeight11.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig stat up","trig stat down" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   
   # Centrality definition
   ./Execute --OutputBase Plots/SysMC/SysPbPbCent$Suffix \
      --DataFiles Root/MC.root,Root/MCHiBinUp.root,Root/MCHiBinDown.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","hiBin up","hiBin down" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysMC/SysPbPbYCent$Suffix \
      --DataFiles Root/MC.root,Root/MCHiBinUp.root,Root/MCHiBinDown.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","hiBin up","hiBin down" \
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
   
