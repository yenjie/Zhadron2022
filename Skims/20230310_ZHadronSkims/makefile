

default: TestRun

TestRun: Execute
	./Execute

Execute: DoZHadronSkim.cpp
	g++ DoZHadronSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --glibs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o
