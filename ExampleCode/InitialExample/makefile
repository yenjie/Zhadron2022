default: ExecuteZHadron

ExecuteZHadron: ZHadron.cpp
	g++ ZHadron.cpp -I. -I$(ProjectBase)/CommonCode/ \
		-o ExecuteZHadron `root-config --cflags --glibs` -std=c++17 \
		$(ProjectBase)/CommonCode/Messenger.o

TestRun: ExecuteZHadron
	./ExecuteZHadron --Input XXX1.root,XXX2.root --Output output.root
