// Prabhas Kumra
// Assignment# 11
// CS 302-1004

#ifndef ganttUtils_h
#define ganttUtils_h

#include <iostream>
#include <string>

using namespace std;


struct graphNode
{
    int vertex;
    int weight;
    graphNode * next;
   
};

struct gList
{
    graphNode * head;
    graphNode * tail;
    int counts;
};

class ganttUtils
{

private:
    int edgeCount;
    int mileStones;
    int source;
    string title;
    gList * graphList;
     //graphNode * head;
    //graphNode * tail;
    int * dist;
    int * prev;
    int * topoNodes;
    bool * aps;
    int topoCount;
    int * crPath;
    int crPathCount;
    int * indegree;
    int * slackTimes;
    int duration, finalTask;

    float mileStonesRatio;
    float taskDensity;

    int keyMilestone, keyTask;
    int nodePoint, nodeTask;
    bool * indMilestone;
    
    int inMax, inMin, inminCount, inmaxCount;
    int outMax, outMin, outminCount, outmaxCount;

public:
    ganttUtils();
    ~ganttUtils();
    void destroyGraph();
    void newGraph(int);
    void addEdge(int, int, int);
    bool getArguments(int, char * [], string &, bool &);
    bool readGraph(string);
    bool isValidProject();
    bool isCycle(int, bool [], bool[]);
    int getTaskCount();
    int getTime(int, int);
    void findGraphInformation();
    void findinDegree();
    void findKeyMilestone();
    void findNodePoint();
    void findDependencyStats();
    void findIndependentMilestones();
    void findAPs();
    void findAPsHelper(int, bool [], int [], int [], int []);
    void topoSort();
    void criticalPath();
    void findSlackTimes();
    void printGraphInformation();
    void printGraph();
    void printDependencyStats();
    void printTopoSort();
    void printAPs();
    void printCriticalPath();
    void printSlackTimes();
    void printBars();

};


#endif 
