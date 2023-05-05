

default: RunPlots

RunPlots: Execute
	bash RunPlots.sh

TestRun: Execute
	./Execute \
		--File1 AllData.root \
		--EventCut1 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && hiBin < 60" \
		--TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
		--Label1 "Data" \
		--File2 AllMC89.root \
		--EventCut2 same \
		--TrackCut2 same \
		--Label2 "MC" \
		--File3 AllMCGen89.root \
		--EventCut3 "genZMass[0] > 60 && genZPt[0] > 5 && genZPt[0] < 20 && hiBin < 60" \
		--TrackCut3 same \
		--Label3 "Gen" \
		--Fraction1 0.1 --Fraction2 0.1 --Fraction3 0.1 \
		--ToPlot "trackDeta" \
		--Title ";#Delta#eta(track,Z);N_{ch} / event" --Bin 80 --Min -8 --Max 8 \
		--Output Plots.pdf

Execute: SinglePlot.cpp
	g++ SinglePlot.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17
