

default: TestRun

TestRun: Execute
	./Execute

Execute: SinglePlot.cpp
	g++ SinglePlot.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17
