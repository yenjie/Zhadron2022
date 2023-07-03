default: CountSkim

CountSkim: ExecuteCount
	mkdir -p SkimCount/20230630
	mkdir -p SkimCount/log/20230630
	condor_submit Submit_CountSkim.condor

ExecuteCount: CountSkim.cpp
	g++ CountSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteCount `root-config --cflags --libs` -std=c++17