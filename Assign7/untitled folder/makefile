# Make file for hash table assignment

OBJS	= movieRatings.o
OBJS1	= assocTest.o
CC	= g++
DEPS	= assocArray.h

all: assocTest movieRatings

assocTest: $(OBJS1)
	$(CC) -Wall -g -o assocTest $(OBJS1)

assocTest.o:	assocTest.cpp $(DEPS)
	$(CC) -Wall -g -c assocTest.cpp

movieRatings.o: movieRatings.cpp $(DEPS)
	$(CC) -Wall -g -c movieRatings.cpp

movieRatings: movieRatings.o
	$(CC) -Wall -g -o movieRatings $(OBJS)

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

