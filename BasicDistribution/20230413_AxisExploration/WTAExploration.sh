#!/bin/bash

Fraction1=1
Fraction2=1
File1=AllData.root
File2=AllData.root

# ./Execute \
#    --Caption "Track-WTA #Delta#phi" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt > 0" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "DPhiWTACorr" \
#    --Title ";#Delta#phi^{track,WTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
#    --Output PlotsWTA001.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#phi, p_{T} = 0.5-2 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5 && trackPt < 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "DPhiWTACorr" \
#    --Title ";#Delta#phi^{track,WTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
#    --Output PlotsWTA002.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#phi, p_{T} > 4 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt > 4" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "DPhiWTACorr" \
#    --Title ";#Delta#phi^{track,WTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
#    --Output PlotsWTA003.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";#Delta#eta^{track,WTA};1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA004.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| < 1" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) < 1" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";#Delta#eta^{track,WTA};1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA005.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA006.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 80" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 80 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA007.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 100" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 100 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA008.pdf
# 
# ./Execute \
#    --Caption "Track-WTA(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTAMore) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaWTAMore)" \
#    --Title ";|#Delta#eta^{track,WTA(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA009.pdf
# 
# ./Execute \
#    --Caption "Track-WTA(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, |#eta^{WTA}| < 1.5" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && abs(EtaWTAMore) < 1.5" --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && abs(EtaWTAMore) < 1.5" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTAMore) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaWTAMore)" \
#    --Title ";|#Delta#eta^{track,WTA(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA010.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, |#eta^{WTA}| < 1.5" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && abs(EtaWTA) < 1.5" --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && abs(EtaWTA) < 1.5" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA011.pdf
# 
# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, |#eta^{WTA}| < 1.5, 0-30%" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && abs(EtaWTA) < 1.5 && hiBin < 60" \
#    --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && abs(EtaWTA) < 1.5 && hiBin < 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA012.pdf

# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 120" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA014.pdf

# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 150" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 150 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA015.pdf

# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 200" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 200 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA016.pdf

# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 250" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA017.pdf

# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 300" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 300 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA018.pdf

./Execute \
   --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| < 1" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 250" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) < 1" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
   --ToPlot "abs(DEtaWTA)" \
   --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA019.pdf



cp PlotsWTA*pdf ~/public/html/
