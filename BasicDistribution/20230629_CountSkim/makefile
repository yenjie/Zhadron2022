default: CountSkim

CountSkim: ExecuteCount
	condor_submit Submit_CountSkim.condor

ExecuteCount: CountSkim.cpp
	g++ CountSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteCount `root-config --cflags --libs` -std=c++17