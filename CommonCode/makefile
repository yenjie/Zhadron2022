default: all

all: Setup library/Messenger.o

Setup:
	mkdir -p library

library/Messenger.o: source/Messenger.cpp include/Messenger.h
	g++ source/Messenger.cpp -Iinclude -c -o library/Messenger.o `root-config --cflags` -std=c++17

