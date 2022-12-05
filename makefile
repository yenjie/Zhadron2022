default: ExecuteZHadron

Messenger.o: Messenger.cpp Messenger.h
	g++ Messenger.cpp -I. -c -o Messenger.o `root-config --cflags` -std=c++17

ExecuteZHadron: ZHadron.cpp Messenger.o
	g++ ZHadron.cpp -I. -o ExecuteZHadron `root-config --cflags --glibs` -std=c++17 Messenger.o
