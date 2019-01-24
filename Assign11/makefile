# Make file for final project

OBJS	= projectInfo.o ganttUtils.o
CC	= g++ -g -Wall -pedantic -pthread -std=c++11
DEPS	= ganttUtils.h linkedQueue.h

all: projectInfo

projectInfo: projectInfo.o $(OBJS)
	$(CC)  -o projectInfo $(OBJS)	

projectInfo.o: projectInfo.cpp $(DEPS)
	$(CC) -c projectInfo.cpp

ganttUtils.o: ganttUtils.cpp ganttUtils.h
	$(CC) -c ganttUtils.cpp

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

