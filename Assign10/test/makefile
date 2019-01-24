# Make file for stack and queue assignment

OBJS	= paths.o graphAlgorithms.o
CC	= g++ -g -Wall -pedantic -std=c++11
DEPS	= graphAlgorithms.h minHeap.h linkedQueue.h

all: paths

paths: paths.o $(OBJS)
	$(CC)  -o paths $(OBJS)	

paths.o: paths.cpp $(DEPS)
	$(CC) -c paths.cpp

graphAlgorithms.o: graphAlgorithms.cpp graphAlgorithms.h
	$(CC) -c graphAlgorithms.cpp

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

