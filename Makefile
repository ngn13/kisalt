SRCS:=$(wildcard src/*.cpp)
CC=g++

kisalt: $(SRCS)
	$(CC) -o $@ $^ -lcrypto -ljsoncpp 
