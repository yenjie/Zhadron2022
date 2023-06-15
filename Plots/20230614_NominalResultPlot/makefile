
default: Prepare RunSystematics

Prepare:
	ln -sf $(ProjectBase)/BasicDistribution/20230605_DeltaPhiReproduction/ Root

TestRun: Execute
	./Execute --OutputBase Test

Execute: MakePlot.cpp
	g++ MakePlot.cpp -o Execute `root-config --cflags --libs` -I$(ProjectBase)/CommonCode/include/

RunSystematics: Execute
	bash MakeSystematicPlots.sh

