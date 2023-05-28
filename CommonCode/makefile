default: all

all: Setup library/Messenger.o binary/Reformat

Setup:
	mkdir -p library
	mkdir -p binary

library/Messenger.o: source/Messenger.cpp include/Messenger.h
	g++ source/Messenger.cpp -Iinclude -c -o library/Messenger.o `root-config --cflags` -std=c++14

binary/Reformat: source/Reformat.cpp
	g++ source/Reformat.cpp -o binary/Reformat


