#!/bin/bash

# 0.2 0.2 0.1 for test
Fraction1=1
Fraction2=1
Fraction3=1

./Execute --Output Plot001.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} = 5-20 GeV, p_{T} > 0.5 GeV, 0-30%"\
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 5 && ZPt < 20 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "trackDeta" --Title ";#Delta#eta(track,Z);N_{ch} / event" --Bin 80 --Min -8 --Max 8

./Execute --Output Plot002.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} = 5-20 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 5 && ZPt < 20 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "trackDeta+ZEta" --Title ";#eta(track);N_{ch} / event" --Bin 80 --Min -2.5 --Max 2.5

./Execute --Output Plot003.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 20 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 20 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "trackDeta+ZEta" --Title ";#eta(track);N_{ch} / event" --Bin 80 --Min -2.5 --Max 2.5

./Execute --Output Plot004.pdf --Caption "N_{ch} vs p_{T}^{Z}, p_{T} > 0.5 GeV" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && hiBin < 60 && zPt > 0" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "ZPt+trackPt*0" --Title ";p_{T}^{Z};N_{ch}, a.u." --Bin 80 --Min 0 --Max 100

./Execute --Output Plot005.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 40 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 40 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "trackDeta+ZEta" --Title ";#eta(track);N_{ch} / event" --Bin 80 --Min -2.5 --Max 2.5

./Execute --Output Plot006.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 60 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 60 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "trackDeta+ZEta" --Title ";#eta(track);N_{ch} / event" --Bin 80 --Min -2.5 --Max 2.5

./Execute --Output Plot007.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 10 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 10 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "trackDeta+ZEta" --Title ";#eta(track);N_{ch} / event" --Bin 80 --Min -2.5 --Max 2.5

./Execute --Output Plot008.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 5 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 5 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "trackDeta+ZEta" --Title ";#eta(track);N_{ch} / event" --Bin 80 --Min -2.5 --Max 2.5

./Execute --Output Plot009.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 5 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 5 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "TrackPhi" --Title ";#phi(track);N_{ch} / event" --Bin 80 --Min -3.1416 --Max 3.1416

./Execute --Output Plot010.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 5 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 5 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "TrackDPhiCorr" --Title ";#Delta#phi(Z,track);N_{ch} / event" --Bin 80 --Min -0.5 --Max 1.5

./Execute --Output Plot011.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 5 GeV, p_{T} > 0.5 GeV, 30-90%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 5 && hiBin >= 60 && hiBin < 180" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "TrackDPhiCorr" --Title ";#Delta#phi(Z,track);N_{ch} / event" --Bin 80 --Min -0.5 --Max 1.5

./Execute --Output Plot012.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 20 GeV, p_{T} > 0.5 GeV, 30-90%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 20 && hiBin >= 60 && hiBin < 180" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "TrackDPhiCorr" --Title ";#Delta#phi(Z,track);N_{ch} / event" --Bin 80 --Min -0.5 --Max 1.5

./Execute --Output Plot014.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 20 GeV, p_{T} > 0.5 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 20 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "TrackDPhiCorr" --Title ";#Delta#phi(Z,track);N_{ch} / event" --Bin 80 --Min -0.5 --Max 1.5

./Execute --Output Plot015.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 20 GeV, p_{T} > 1 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 20 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 1" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "TrackDPhiCorr" --Title ";#Delta#phi(Z,track);N_{ch} / event" --Bin 80 --Min -0.5 --Max 1.5

./Execute --Output Plot016.pdf --Caption "M_{Z} > 60 GeV, p_{T}^{Z} > 20 GeV, p_{T} > 2 GeV, 0-30%" \
   --File1 AllData.root --Fraction1 $Fraction1 --Label1 "Data" \
   --EventCut1 "ZMass > 60 && ZPt > 20 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 2" \
   --File2 AllMC89.root --Fraction2 $Fraction2 --Label2 "MC" \
   --EventCut2 same --TrackCut2 same \
   --File3 AllMCGen89.root --Fraction3 $Fraction3 --Label3 "Gen" --File3IsGen true \
   --EventCut3 same --TrackCut3 same \
   --ToPlot "TrackDPhiCorr" --Title ";#Delta#phi(Z,track);N_{ch} / event" --Bin 80 --Min -0.5 --Max 1.5



cp Plot*pdf ~/public/html/
