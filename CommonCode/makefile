default: all

all: Messenger.o

Messenger.o: Messenger.cpp Messenger.h
	g++ Messenger.cpp -I. -c -o Messenger.o `root-config --cflags` -std=c++17

