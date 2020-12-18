CC=g++
CFLAGS=-std=c++11 -g -Wall 

all: solver

solver: solver.cpp
	$(CC) $(CFLAGS) -o solver solver.cpp

clean:
	rm *.o *.exe *.stackdump