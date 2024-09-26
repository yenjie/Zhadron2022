#!/bin/bash

mkdir -p Plots/SysRat

for CRange in 0:30 0:10 10:30 30:90 30:50 50:90
do
   CMin=`echo $CRange | tr ':' ' ' | awk '{print $1}'`
   CMax=`echo $CRange | tr ':' ' ' | awk '{print $2}'`

   Tags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_10
   SecondTags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_1
   Labels="1 < p_{T}^{trk} < 2 GeV","2 < p_{T}^{trk} < 4 GeV","4 < p_{T}^{trk} < 10 GeV"
   PPExtraInfo="40 < p_{T}^{Z} < 200 GeV"
   ExtraInfo="40 < p_{T}^{Z} < 200 GeV,${CMin}-${CMax}%"
   Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Ratio --XMin 0 --XMax 3.1415926535 --YMin -7 --YMax 10 --RMin -1 --RMax 3 --LegendLeft 0.08 --LegendBottom 0.40"
   PlottingY="--XAxisLabel |#Deltay_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Ratio --XMin 0 --XMax 3.2 --YMin -200 --YMax 200 --RMin -1 --RMax 3 --LegendLeft 0.08 --LegendBottom 0.40"

   Suffix="C${CMin}${CMax}"
   
   # Muon matching
   ./Execute --OutputBase Plots/SysRat/SysPbPbMuMatch$Suffix \
      --DataFiles Root/Data.root,Root/DataMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb (#DeltaR > 0.01)","Muon match (#DeltaR > 0.0025)" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPPMuMatch \
      --DataFiles Root/PPData.root,Root/PPDataMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal pp (#DeltaR > 0.01)","Muon match (#DeltaR > 0.0025)" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbYMuMatch$Suffix \
      --DataFiles Root/Data.root,Root/DataMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb (#DeltaR > 0.01)","Muon match (#DeltaR > 0.0025)" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysRat/SysPPYMuMatch \
      --DataFiles Root/PPData.root,Root/PPDataMuMatch.root --SkipSystematics true \
      --CurveLabels "Nominal pp (#DeltaR > 0.01)","Muon match (#DeltaR > 0.0025)" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $PlottingY
   
   # Background subtraction
   ./Execute --OutputBase Plots/SysRat/SysPbPbUE25$Suffix \
      --DataFiles Root/DataMix.root,Root/DataMixUEUp25.root,Root/DataMixUEDown25.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","UE up","UE down" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbYUE25$Suffix \
      --DataFiles Root/DataMix.root,Root/DataMixUEUp25.root,Root/DataMixUEDown25.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","UE up","UE down" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   
   # Non-closure
   
   # pp PU
   ./Execute --OutputBase Plots/SysRat/SysPPPU \
      --DataFiles Root/PPData.root,Root/PPData.root --SkipSystematics true \
      --CurveLabels "Nominal","PV = 1" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --SecondTags "$SecondTags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPPYPU \
      --DataFiles Root/PPData.root,Root/PPData.root --SkipSystematics true \
      --CurveLabels "Nominal","PV = 1" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --SecondTags "$SecondTags" --Labels "$Labels" --ExtraInfo "$PPExtraInfo" \
      $PlottingY
   
   # Lepton SF variation
   ./Execute --OutputBase Plots/SysRat/SysPbPbSF1Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight0.root,Root/DataExtraZWeight1.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk sys up","glbPFtrk sys down" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbSF2Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight2.root,Root/DataExtraZWeight3.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid sys up","muid sys down" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbSF3Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight4.root,Root/DataExtraZWeight5.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig sys up","trig sys down" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbSF1Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight6.root,Root/DataExtraZWeight7.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk stat up","glbPFtrk stat down" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbSF2Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight8.root,Root/DataExtraZWeight9.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid stat up","muid stat down" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbSF3Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight10.root,Root/DataExtraZWeight11.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig stat up","trig stat down" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

   ./Execute --OutputBase Plots/SysRat/SysPbPbYSF1Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight0.root,Root/DataExtraZWeight1.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk sys up","glbPFtrk sys down" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysRat/SysPbPbYSF2Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight2.root,Root/DataExtraZWeight3.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid sys up","muid sys down" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysRat/SysPbPbYSF3Sys$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight4.root,Root/DataExtraZWeight5.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig sys up","trig sys down" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysRat/SysPbPbYSF1Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight6.root,Root/DataExtraZWeight7.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","glbPFtrk stat up","glbPFtrk stat down" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysRat/SysPbPbYSF2Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight8.root,Root/DataExtraZWeight9.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","muid stat up","muid stat down" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   ./Execute --OutputBase Plots/SysRat/SysPbPbYSF3Stat$Suffix \
      --DataFiles Root/Data.root,Root/DataExtraZWeight10.root,Root/DataExtraZWeight11.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","trig stat up","trig stat down" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY
   
   # Centrality definition
   ./Execute --OutputBase Plots/SysRat/SysPbPbCent$Suffix \
      --DataFiles Root/Data.root,Root/DataHiBinUp.root,Root/DataHiBinDown.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","hiBin up","hiBin down" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbYCent$Suffix \
      --DataFiles Root/Data.root,Root/DataHiBinUp.root,Root/DataHiBinDown.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","hiBin up","hiBin down" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY

   # Track selection
   ./Execute --OutputBase Plots/SysRat/SysPbPbTrk$Suffix \
      --DataFiles Root/Data.root,Root/DataLoose.root,Root/DataTight.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","Loose track selection","Tight track selection" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbYTrk$Suffix \
      --DataFiles Root/Data.root,Root/DataLoose.root,Root/DataTight.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","Loose track selection","Tight track selection" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY

   # VZ cut
   #./Execute --OutputBase Plots/SysRat/SysPbPbVZ$Suffix \
   #   --DataFiles Root/Data.root,Root/Data_VZ1.root,Root/Data_VZ2.root,Root/Data_VZ3.root,Root/Data_VZ4.root --SkipSystematics true \
   #   --CurveLabels "Nominal PbPb","v_{z} < -5 cm","-5 < v_{z} < 0 cm","0 < v_{z} < 5 cm","v_{z} > 5 cm" \
   #   --ToPlot "DeltaPhi" \
   #   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   #   $Plotting
   #./Execute --OutputBase Plots/SysRat/SysPbPbYVZ$Suffix \
   #   --DataFiles Root/Data.root,Root/Data_VZ1.root,Root/Data_VZ2.root,Root/Data_VZ3.root,Root/Data_VZ4.root --SkipSystematics true \
   #   --CurveLabels "Nominal PbPb","v_{z} < -5 cm","-5 < v_{z} < 0 cm","0 < v_{z} < 5 cm","v_{z} > 5 cm" \
   #   --ToPlot "DeltaY" \
   #   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   #   $PlottingY
   ./Execute --OutputBase Plots/SysRat/SysPbPbVZ$Suffix \
      --DataFiles Root/Data.root,Root/Data_VZ10.root,Root/Data_VZ20.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","|v_{z}| < 10 cm","|v_{z}| < 20 cm" \
      --ToPlot "DeltaPhi" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase Plots/SysRat/SysPbPbYVZ$Suffix \
      --DataFiles Root/Data.root,Root/Data_VZ10.root,Root/Data_VZ20.root --SkipSystematics true \
      --CurveLabels "Nominal PbPb","|v_{z}| < 10 cm","|v_{z}| < 20 cm" \
      --ToPlot "DeltaY" --CompareDivide true \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $PlottingY

done
   
