// Prabhas Kumra
// Assignment#10
// CS 302-1004

#ifndef graphAlgorithms_h
#define graphAlgorithms_h

#include <iostream>
#include <string>

using namespace std;

class graphAlgorithms
{
private:
    int vertexCount;
    string title;
    int ** graphMatrix;
    int * dist;
    int * prev;
    int * topoNodes;
    int topoCount;

public:
    graphAlgorithms(int=5);
    ~graphAlgorithms();
    void newGraph(int);
    void addEdge(int, int, int);
    bool readGraph(const string);
    int getVertexCount() const;
    void printMatrix() const;
    void topoSort();
    void dijkstraSP(int);
    void printPath(const int, const int) const;
    void showPath(const int) const;
    string getGraphTitle() const;
    void setGraphTitle(const string);
    void printDistances(const int) const;
    void destroyGraph();
    bool getArgs(int, char*[],bool &, string &, int &, int &, bool &);
};

#endif  // graphAlgorithms_h