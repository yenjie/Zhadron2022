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

# ./Execute \
#    --Caption "Track-WTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| < 1" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 250" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiWTA) < 1" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
#    --ToPlot "abs(DEtaWTA)" \
#    --Title ";|#Delta#eta^{track,WTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA019.pdf

# ./Execute \
#    --Caption "Track-Jet(#pi/2) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| < 1, Jet(#pi/2) p_{T} > 30 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet12Pt > 30" --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && maxOppositeJet12Pt > 30" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet12) < 1" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaJet12)" \
#    --Title ";|#Delta#eta^{track,Jet(#pi/2)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA020.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(#pi/2) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(#pi/2) p_{T} > 30 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet12Pt > 30" --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && maxOppositeJet12Pt > 30" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet12) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaJet12)" \
#    --Title ";|#Delta#eta^{track,Jet(#pi/2)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA021.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(#pi/2) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(#pi/2) p_{T} > 30 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet12Pt > 30" --EventCut2 "zMass[0] > 60 && zPt[0] > 120 && maxOppositeJet12Pt > 30" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet12) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
#    --ToPlot "abs(DEtaJet12)" \
#    --Title ";|#Delta#eta^{track,Jet(#pi/2)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA022.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(3#pi/4) p_{T} > 30 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet34Pt > 30" --EventCut2 "zMass[0] > 60 && zPt[0] > 120 && maxOppositeJet34Pt > 30" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet34) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
#    --ToPlot "abs(DEtaJet34)" \
#    --Title ";|#Delta#eta^{track,Jet(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA023.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(5#pi/6) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(5#pi/6) p_{T} > 30 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet56Pt > 30" --EventCut2 "zMass[0] > 60 && zPt[0] > 120 && maxOppositeJet56Pt > 30" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet56) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
#    --ToPlot "abs(DEtaJet56)" \
#    --Title ";|#Delta#eta^{track,Jet(5#pi/6)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA024.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(7#pi/8) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(7#pi/8) p_{T} > 30 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet78Pt > 30" --EventCut2 "zMass[0] > 60 && zPt[0] > 120 && maxOppositeJet78Pt > 30" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet78) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
#    --ToPlot "abs(DEtaJet78)" \
#    --Title ";|#Delta#eta^{track,Jet(7#pi/8)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA025.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(3#pi/4) x_{jZ} > 0.5" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet34Pt > zPt[0] * 0.5" --EventCut2 "zMass[0] > 60 && zPt[0] > 120 && maxOppositeJet34Pt > zPt[0] * 0.5" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet34) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
#    --ToPlot "abs(DEtaJet34)" \
#    --Title ";|#Delta#eta^{track,Jet(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA027.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(3#pi/4) x_{jZ} > 0.75" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet34Pt > zPt[0] * 0.75" --EventCut2 "zMass[0] > 60 && zPt[0] > 120 && maxOppositeJet34Pt > zPt[0] * 0.75" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet34) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
#    --ToPlot "abs(DEtaJet34)" \
#    --Title ";|#Delta#eta^{track,Jet(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA028.pdf

# ./Execute \
#    --Caption "Track-Jet(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(3#pi/4) p_{T} > 30 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet34Pt > 30" --EventCut2 "zMass[0] > 60 && zPt[0] > 250 && maxOppositeJet34Pt > 30" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet34) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
#    --ToPlot "abs(DEtaJet34)" \
#    --Title ";|#Delta#eta^{track,Jet(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA029.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(3#pi/4) p_{T} > 60 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet34Pt > 60" --EventCut2 "zMass[0] > 60 && zPt[0] > 250 && maxOppositeJet34Pt > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet34) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
#    --ToPlot "abs(DEtaJet34)" \
#    --Title ";|#Delta#eta^{track,Jet(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA030.pdf
# 
# ./Execute \
#    --Caption "Track-Jet(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, Jet(3#pi/4) p_{T} > 90 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && maxOppositeJet34Pt > 90" --EventCut2 "zMass[0] > 60 && zPt[0] > 250 && maxOppositeJet34Pt > 90" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiJet34) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
#    --ToPlot "abs(DEtaJet34)" \
#    --Title ";|#Delta#eta^{track,Jet(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA031.pdf

# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#phi" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt > 0" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "DPhiChargedWTACorr" \
#    --Title ";#Delta#phi^{track,ChargedWTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
#    --Output PlotsWTA032.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#phi, p_{T} = 0.5-2 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5 && trackPt < 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "DPhiChargedWTACorr" \
#    --Title ";#Delta#phi^{track,ChargedWTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
#    --Output PlotsWTA033.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#phi, p_{T} > 4 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt > 4" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "DPhiChargedWTACorr" \
#    --Title ";#Delta#phi^{track,ChargedWTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
#    --Output PlotsWTA034.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";#Delta#eta^{track,ChargedWTA};1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA035.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| < 1" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) < 1" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";#Delta#eta^{track,ChargedWTA};1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA036.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA037.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 80" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 80 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA038.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 100" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 100 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA039.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTAMore) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaChargedWTAMore)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA040.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA(3#pi/4) #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, |#eta^{ChargedWTA}| < 1.5" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && abs(EtaChargedWTAMore) < 1.5" --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && abs(EtaChargedWTAMore) < 1.5" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTAMore) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaChargedWTAMore)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA(3#pi/4)}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA041.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, |#eta^{ChargedWTA}| < 1.5" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && abs(EtaChargedWTA) < 1.5" --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && abs(EtaChargedWTA) < 1.5" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA042.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, |#eta^{ChargedWTA}| < 1.5, 0-30%" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && abs(EtaChargedWTA) < 1.5 && hiBin < 60" \
#    --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && abs(EtaChargedWTA) < 1.5 && hiBin < 60" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA043.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 120" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA044.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 150" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 150 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA045.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 200" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 200 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA046.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 250" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA047.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 300" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) > 2" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 300 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA048.pdf
# 
# ./Execute \
#    --Caption "Track-ChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| < 1" \
#    --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
#    --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 250" \
#    --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiChargedWTA) < 1" --TrackCut2 same \
#    --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
#    --ToPlot "abs(DEtaChargedWTA)" \
#    --Title ";|#Delta#eta^{track,ChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
#    --Output PlotsWTA049.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#phi" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
   --ToPlot "DPhiHardChargedWTACorr" \
   --Title ";#Delta#phi^{track,HardChargedWTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
   --Output PlotsWTA050.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#phi, p_{T} = 0.5-2 GeV" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 0.5 && trackPt < 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
   --ToPlot "DPhiHardChargedWTACorr" \
   --Title ";#Delta#phi^{track,HardChargedWTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
   --Output PlotsWTA051.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#phi, p_{T} > 4 GeV" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt > 4" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
   --ToPlot "DPhiHardChargedWTACorr" \
   --Title ";#Delta#phi^{track,HardChargedWTA} (#pi);1/N_{event} dN_{ch}/dx" --Bin 20 --Min -0.5 --Max 1.5 \
   --Output PlotsWTA052.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";#Delta#eta^{track,HardChargedWTA};1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA053.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| < 1" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) < 1" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";#Delta#eta^{track,HardChargedWTA};1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA054.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA055.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 80" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 80 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA056.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 100" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 100 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA057.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, |#eta^{HardChargedWTA}| < 1.5" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && abs(EtaHardChargedWTA) < 1.5" --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && abs(EtaHardChargedWTA) < 1.5" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA058.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2, |#eta^{HardChargedWTA}| < 1.5, 0-30%" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && abs(EtaHardChargedWTA) < 1.5 && hiBin < 60" \
   --EventCut2 "zMass[0] > 60 && zPt[0] > 60 && abs(EtaHardChargedWTA) < 1.5 && hiBin < 60" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 60 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA059.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 120" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 120 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA060.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 150" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 150 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA061.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 200" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 200 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA062.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 250" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA063.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| > 2" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 300" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) > 2" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 300 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA064.pdf

./Execute \
   --Caption "Track-HardChargedWTA #Delta#eta, p_{T} = 0.5-2.0 GeV, |#Delta#phi| < 1" \
   --File1 $File1 --File2 $File2 --Fraction1 $Fraction1 --Fraction2 $Fraction2 \
   --EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20" --EventCut2 "zMass[0] > 60 && zPt[0] > 250" \
   --TrackCut1 "trackMuTagged == 0 && trackPt < 2 && abs(DPhiHardChargedWTA) < 1" --TrackCut2 same \
   --Label1 "p_{T}^{Z} = 5-20 GeV" --Label2 "p_{T}^{Z} > 250 GeV" \
   --ToPlot "abs(DEtaHardChargedWTA)" \
   --Title ";|#Delta#eta^{track,HardChargedWTA}|;1/N_{event} dN_{ch}/dx" --Bin 20 --Min 0 --Max 5 \
   --Output PlotsWTA065.pdf




cp PlotsWTA*pdf ~/public/html/
