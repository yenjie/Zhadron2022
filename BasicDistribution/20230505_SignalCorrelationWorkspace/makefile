

default: TestRun

TestRun: Execute
	./Execute \
		--File1 AllData.root \
		--EventCut2 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && hiBin < 180" \
		--TrackCut1 "trackMuTagged == 0 && trackPt > 0.5" \
		--Label1 "Data" \
		--File2 AllData.root \
		--EventCut2 "zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && hiBin < 180" \
		--TrackCut2 "trackMuTagged == 0 && trackPt > 0.5" \
		--Label2 "MC" \
		--File3 AllData.root \
		--EventCut3 "genZMass[0] > 60 && genZPt[0] > 5 && genZPt[0] < 20 && hiBin < 180" \
		--TrackCut3 "trackMuTagged == 0 && trackPt > 0.5" \
		--Label3 "Gen" \
		--ToPlot "trackDeta" \
		--Title ";#Delta#eta(track,Z);N_{ch} / event" --Bin 40 --Min -5 --Max 5 \
		--Output Plots.pdf

Execute: SinglePlot.cpp
	g++ SinglePlot.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17
