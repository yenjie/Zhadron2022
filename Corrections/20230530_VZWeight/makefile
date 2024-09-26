default: TestRun

TestRun: Execute
	./Execute --MC AllMCV10_89.root --Data AllDataV10_89.root --Output PbPb.pdf
	./Execute --MC AllPPMCV10_89.root --Data AllPPDataV12_89.root --Output pp.pdf

Execute: Derive.cpp
	g++ Derive.cpp -o Execute `root-config --libs --cflags` \
		-I$(ProjectBase)/CommonCode/include/
