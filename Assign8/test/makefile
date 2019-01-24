# Make file for minHeap and maxHeap

OBJS	= main.o
OBJS1	= pqTest.o
CC	= g++
DEPS	= minHeap.h maxHeap.h dynamicMedians.h

all: pqTest main

pqTest: $(OBJS1)
	$(CC) -Wall -g -o pqTest $(OBJS1)

pqTest.o:	pqTest.cpp $(DEPS)
	$(CC) -Wall -g -c pqTest.cpp

main.o: main.cpp $(DEPS)
	$(CC) -Wall -g -c main.cpp

main: main.o
	$(CC) -Wall -g -o main $(OBJS)

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

