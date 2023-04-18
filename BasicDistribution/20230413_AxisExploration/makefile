

default: RunWTACorrelation

RunZHadronCorrelation: Execute
	bash ZHadronExploration.sh

RunWTACorrelation: Execute
	bash WTAExploration.sh

TestRun: Execute
	./Execute \
		--File1 AllData.root \
		--EventCut1 "zMass[0] > 60 && zPt[0] > 60 && hiBin < 20" \
		--TrackCut1 "trackMuTagged == 0 && abs(DPhiWTA) > 2" \
		--Label1 "p_{T}^{Z} > 60 GeV" \
		--File2 AllData.root \
		--EventCut2 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && hiBin < 20" \
		--TrackCut2 "trackMuTagged == 0 && abs(DPhiWTA) > 2" \
		--Label2 "p_{T}^{Z} > 5-20 GeV" \
		--ToPlot "abs(DEtaWTA)" \
		--Title ";#Delta#eta;N_{ch} / event" --Bin 40 --Min 0 --Max 5 \
		--Output Plots.pdf

TestRun2: Execute
	./Execute \
		--File1 AllData.root \
		--EventCut1 "zMass[0] > 60 && zPt[0] > 60 && hiBin < 20 && abs(EtaWTA) < 1.5" \
		--TrackCut1 "trackMuTagged == 0 && abs(DPhiWTA) > 2 && trackPt > 1 && trackPt < 2" \
		--Label1 "p_{T}^{Z} > 60 GeV, PbPb" \
		--Fraction1 0.1 \
		--File2 AllDataBackground00.root \
		--EventCut2 same \
		--TrackCut2 same \
		--Label2 "p_{T}^{Z} > 60 GeV, Mix" \
		--Fraction2 0.2 \
		--ToPlot "abs(DEtaWTA)" \
		--Title ";#Delta#eta;N_{ch} / event" --Bin 40 --Min 0 --Max 5 \
		--Output Plots.pdf
	cp Plots.pdf ~/public/html/

TestRun2MC: Execute
	./Execute \
		--File1 AllMC7.root \
		--EventCut1 "zMass[0] > 60 && zPt[0] > 60 && hiBin < 20 && abs(maxOppositeWTADEta+zEta[0]) < 1.5" \
		--TrackCut1 "trackMuTagged == 0 && abs(DPhiWTA) > 2 && trackPt > 1" \
		--Label1 "p_{T}^{Z} > 60 GeV, PbPb" \
		--File2 AllMCBackground.root \
		--EventCut2 "zMass[0] > 60 && zPt[0] > 60 && hiBin < 20 && abs(maxOppositeWTADEta+zEta[0]) < 1.5" \
		--TrackCut2 "trackMuTagged == 0 && abs(DPhiWTA) > 2 && trackPt > 1" \
		--Label2 "p_{T}^{Z} > 60 GeV, Mix" \
		--ToPlot "abs(DEtaWTA)" \
		--Title ";#Delta#eta;N_{ch} / event" --Bin 40 --Min 0 --Max 5 \
		--Output Plots.pdf
	cp Plots.pdf ~/public/html/

TestRun3: Execute
	./Execute \
		--File1 AllData.root \
		--EventCut1 "zMass[0] > 60 && zPt[0] > 60 && hiBin < 20" \
		--TrackCut1 "trackMuTagged == 0 && trackPt > 1" \
		--Label1 "p_{T}^{Z} > 60 GeV, PbPb" \
		--File2 AllDataBackground00.root \
		--EventCut2 "zMass[0] > 60 && zPt[0] > 60 && hiBin < 20" \
		--TrackCut2 "trackMuTagged == 0 && trackPt > 1" \
		--Label2 "p_{T}^{Z} > 60 GeV, Mix" \
		--ToPlot "abs(trackDphi)" \
		--Title ";#Delta#phi;N_{ch} / event" --Bin 40 --Min 0 --Max 3.14159 \
		--Output Plots.pdf
	cp Plots.pdf ~/public/html/

TestRun4: Execute
	./Execute \
		--File1 AllData.root \
		--EventCut1 "zMass[0] > 60 && zPt[0] > 60 && hiBin < 20 && abs(EtaMax) < 2.4" \
		--TrackCut1 "trackMuTagged == 0 && abs(DPhiMax) > 2 && trackPt > 1 && trackPt < 2" \
		--Label1 "p_{T}^{Z} > 60 GeV, PbPb" \
		--Fraction1 1 \
		--File2 AllDataBackground00.root \
		--EventCut2 same \
		--TrackCut2 same \
		--Label2 "p_{T}^{Z} > 60 GeV, Mix" \
		--Fraction2 0.2 \
		--ToPlot "abs(DEtaMax)" \
		--Title ";#Delta#eta;N_{ch} / event" --Bin 40 --Min 0 --Max 5 \
		--Output Plots.pdf
	cp Plots.pdf ~/public/html/

Execute: SinglePlot.cpp
	g++ SinglePlot.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17
