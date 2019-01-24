// Prabhas Kumra
// Assignment# 11
// CS 302-1004

#ifndef ganttUtils_h
#define ganttUtils_h

#include <iostream>
#include <string>

using namespace std;

class ganttUtils
{

struct graphNode
{
    int weight;
    graphNode * next;
};

private:
    int vertexCount;
    string title;
    int ** graphList;
    int * dist;
    int * prev;
    int * topoNodes;
    int topoCount;

public:
    ganttUtils();
    ~ganttUtils();
    void newGraph(int);
    void addEdge(int, int, int);
    bool getArguments(int, char * [], string, bool);
    bool readGraph(string);
    bool isValidProject();
    int getTaskCount();
    void findGraphInformation();
    void findKeyMilestone();
    void findNodePrint();
    void findDependentMilestones();
    void findAps();
    void topSort();
    void criticalPath();
    void printGraphinformation();
    void printGraph();
    void printDependencyStats();
    void printTopoSort();
    void printAps();
    void printCriticalPath();
    void printSlackTime();

};


#endif 