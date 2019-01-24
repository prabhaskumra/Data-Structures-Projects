# Make file for Disjoint Sets assignment

OBJS	= maze.o disjointSets.o mazeGenerator.o
OBJS1	= testDSclass.o disjointSets.o
CC	= g++ -g -Wall -pedantic -std=c++11
DEPS	= disjointSets.h mazeGenerator.h

all: maze testDSclass

testDSclass: $(OBJS1) disjointSets.o
	$(CC) -o testDSclass $(OBJS1)

testDSclass.o:	testDSclass.cpp $(DEPS)
	$(CC) -c testDSclass.cpp

maze: maze.o disjointSets.o mazeGenerator.o
	$(CC) -o maze $(OBJS)

maze.o: maze.cpp $(DEPS)
	$(CC) -c maze.cpp

# -----c
# clean by removing object files.

clean:
	rm	$(OBJS)


