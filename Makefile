CC = g++
CFLAGS = -g -std=c++11
LIBCV = `pkg-config --libs --cflags opencv`

all: 
	$(CC) $(CFLAGS) -o phantom phantom.cpp $(LIBCV)