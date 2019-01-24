# Make file for Harshand Nums

OBJS1	= harshadNums.o
CC	= g++

all: harshadNums

harshadNums: $(OBJS1)
	$(CC) -Wall -pedantic -g -std=c++11 -pthread -o harshadNums $(OBJS1)

harshadNums.o:	harshadNums.cpp $(DEPS)
	$(CC) -Wall -pedantic -g -std=c++11 -pthread -c harshadNums.cpp

clean:
	rm	$(OBJS1)

