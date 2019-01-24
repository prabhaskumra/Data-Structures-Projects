// Prabhas Kumra
// Assignment#10
// CS 302-1004

#include <iostream>
#include "graphAlgorithms.h"
#include "minHeap.h"
#include "linkedQueue.h"
#include <limits>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <sstream>

using namespace std;


graphAlgorithms::graphAlgorithms(int size)
{
    if(size < 5)
    {
        graphMatrix = NULL;
        dist = NULL;
        prev = NULL;
        topoNodes = NULL;
       
        cout << "graphAlgorithms: Error, invalid graph size." << endl;
    }
    else
    {
        vertexCount = size;
        title = "";
        graphMatrix = NULL;
        dist = NULL;
        prev = NULL;
        topoNodes = NULL;
        topoCount = 0;

        newGraph(vertexCount);
    }
}
graphAlgorithms::~graphAlgorithms()
{
    destroyGraph();
}

void graphAlgorithms::newGraph(int size)
{
    destroyGraph();

    if(size >= 5)
    {
        vertexCount = size;
        graphMatrix = new int*[size];

        for(int i = 0; i < size; i++)
            graphMatrix[i] = new int[size];

        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                graphMatrix[i][j] = 0;
    }
    else
        cout << "newGraph: Error, invalid graph size" << endl;
}

void graphAlgorithms::addEdge(int start, int end, int weight)
{
    if(start <= vertexCount && end <= vertexCount && start != end && start >= 0 && end >= 0){
        graphMatrix[start][end] = weight;
    }
    else if(start == end){
        cout << "addEdge: Error, vertex to and from cannot be the same" << endl;
        return;
    }
    else{
        cout << "addEdge: Error, invalid vertex" << endl;
    }
        
}
bool graphAlgorithms::readGraph(const string fname)
{
    fstream inFile;
    inFile.open(fname);
    string count;
    string name;

    getline(inFile, name);
    getline(inFile, count);
    int size = stoi(count);
    
    if(vertexCount < 5)
    {
        cout << "Error, invalid graph size." << endl;
        return false;
    }
    else
    {
        newGraph(size);
    }

    vertexCount = size;
    title = name;
    int start, end, weight;

    inFile >> start;
    while(inFile)
    {
        inFile >> end >> weight;

        addEdge(start, end, weight);

        inFile >> start;
    }

    return true;
    
}
int graphAlgorithms::getVertexCount() const
{
    return vertexCount;
}
void graphAlgorithms::printMatrix() const
{


    bool error = false;

    /*for(int i = 0; i < vertexCount; i++)
    {
        for(int j = 0; j < vertexCount; j++)
        {
            if(graphMatrix[i][j] != 0)
               {
                   error = true;
                   break;
               } 
        }
        
    }*/

    if(graphMatrix != NULL)
        error = true;

    if(error == false)
    {
        cout << "printMatrix: Error, no graph data." << endl;
        return;
    }

    cout << "Graph Adjancency Matrix:" << endl;
    cout << "   Graph Title: " << title << endl;
    cout << endl;

    cout << setw(9);
    for(int i = 0; i < vertexCount; i++)
    {
        cout << i << setw(4);
    }
    cout << endl;
    cout  << setw(10);

     for(int i = 0; i < vertexCount; i++)
    {
        cout << "----";
    }
    cout << endl;

    for(int i = 0; i < vertexCount; i++)
    {
        cout << setw(4) << i << "|";
        for(int j = 0; j < vertexCount; j++)
        {
            cout << setw(4);

            if(i == j)
                cout << "0";
            else if(graphMatrix[i][j]==0)
                cout << "--";
            else
                cout << graphMatrix[i][j];
        }
        cout << endl;
    }
    cout << endl;

}
void graphAlgorithms::topoSort()
{
    bool error = false;

   /* for(int i = 0; i < vertexCount; i++)
    {
        for(int j = 0; j < vertexCount; j++)
        {
            if(graphMatrix[i][j] != 0)
               {
                   error = true;
                   break;
               } 
        }
        
    }*/

    if(graphMatrix != NULL)
        error = true;

    if(error == false)
    {
        cout << "topSort: Error, no graph data." << endl;
        return;
    }

    int * inDegree = new int[vertexCount];
    topoNodes = new int[vertexCount];

    for(int i = 0; i < vertexCount; i++)
    {
        inDegree[i] = 0;
        topoNodes[i] = 0;
    }

    topoCount = 0;

    for(int i = 0; i < vertexCount; i++)
        for(int j = 0; j < vertexCount; j++)
            if(graphMatrix[j][i] != 0)
                inDegree[i]++;

  
    linkedQueue<int> Q;

    for(int i = 0; i < vertexCount; i++)
        if(inDegree[i] == 0)
            Q.addItem(i);
    
    int dQ;

    while(!Q.isEmptyQueue())
    {
        dQ = Q.front();
        Q.deleteItem();

        topoNodes[topoCount] = dQ;
        topoCount++;

        for(int i = 0; i < vertexCount; i++)
        {
            if(graphMatrix[dQ][i] != 0)
            {
                inDegree[i]--;
                if(inDegree[i] == 0)
                    Q.addItem(i);
            }
        }
    }

    cout << "Topological Sort:" << endl;
    for(int i = 0; i < vertexCount; i++)
        cout << topoNodes[i] <<" ";
    cout << endl;
    cout << endl;
}

void graphAlgorithms::dijkstraSP(int source)
{
    bool error = false;

    /*for(int i = 0; i < vertexCount; i++)
    {
        for(int j = 0; j < vertexCount; j++)
        {
            if(graphMatrix[i][j] != 0)
               {
                   error = true;
                   break;
               } 
        }
        
    }*/

    if(graphMatrix != NULL)
        error = true;


    if(error == false)
    {
        cout << "dijkstra: Error, no graph data." << endl;
        return;
    }

    if(source < 0 || source >= vertexCount)
    {
        cout << "dijkstra: Error, invalid source" << endl;
        return;
    }

    dist = new int[vertexCount];
    prev = new int[vertexCount];

    for(int i = 0; i < vertexCount; i++)
    {
        dist[i] = std::numeric_limits<int>::max();
        prev[i] = -1;
    }

    minHeap<int> minH;
    dist[source] = 0;
    minH.insert(source, dist[source]);
    
    int uVertex, uDist, newDist;

    while(!minH.isEmpty())
    {
        uVertex = minH.deleteMin(uDist);

        for(int i = 0; i < vertexCount; i++)
        {
            if(graphMatrix[uVertex][i] != 0)
            {
                newDist = uDist + graphMatrix[uVertex][i];
                if(newDist < dist[i])
                {
                    dist[i] = newDist;// = dist[i];
                    prev[i] = uVertex;
                    minH.insert(i, newDist);
                }
            }   
        }
    }

    printDistances(source);
  
}

void graphAlgorithms::printPath(const int start, const int end) const
{
    if(end < vertexCount)
    {
        cout << "Path from " << start << " to " << end << endl;
        showPath(end);
        cout << endl;
    }
    else{
        cout << "Error, invalid to vertex" << endl;;
    }

}

void graphAlgorithms::showPath(const int j) const
{
    if(prev[j] == -1)
        cout << "  " << j;
    else
    {
        showPath(prev[j]);
        cout << " - "<<j;
    }
}

string graphAlgorithms::getGraphTitle() const
{
    return title;
}

void graphAlgorithms::setGraphTitle(const string name)
{
    title = name;
}

void graphAlgorithms::printDistances(const int source) const
{
    cout << "Shortest Paths:" << endl;
    cout << "From Node: " << source << " to:" << endl;
    cout <<setw(10) <<"Vertex" << setw(10) << "Dist" << setw(10) << "From" << endl;

    for(int i = source; i < vertexCount; i++)
    {
        cout <<setw(10) <<i;// <<setw(10);
        
        if(dist[i] != std::numeric_limits<int>::max())
            cout <<setw(10)<< dist[i] << setw(10);
        else
            cout << "        not reachable";

        if(i == source)
            cout << "-" << endl;
        else if(prev[i] == -1)
            cout << endl;
        else
            cout << prev[i] << endl;
    }

}

void graphAlgorithms::destroyGraph()
{
    if(graphMatrix != NULL)
    {
        for(int i = 0; i<vertexCount; i++)
        {
         delete [] graphMatrix[i];
        }
        delete[] graphMatrix;
    }

    if(dist != NULL)
        delete[] dist;

    if(prev != NULL)
        delete[] prev;

    if(topoNodes != NULL)
        delete[] topoNodes;

    title = "";
    dist = NULL;
    prev = NULL;
    graphMatrix = NULL;
    topoNodes = NULL;
    topoCount = 0;
}

bool graphAlgorithms::getArgs(int argc, char* argv[],bool & test, string & fname, int & start, int & end, bool & showMat)
{
    ifstream inFile;
    ofstream outFile;
    stringstream sn, ds;
    string st, en;

    bool fileSpeErr = false, snErr = false, dsErr = false;
    bool showErr = false, testErr = false;

    if(argc == 1)
    {
        cout << "usage: ./paths -gf <graphFile> -sn <source node> -dn <destination node> -sm(optional)" << endl;
        return false;
    }

    if( argc == 3|| argc == 4 || argc == 5 || argc == 6 || argc > 8)
    {
        cout << "Error, invalid command line options" << endl;
        return false;
    }

    if(argc == 2)
    {
        if(string(argv[1])== "-t")
        {
            test = true;
            testErr = true;
        }


        if(testErr == false)
            {
               cout << "Testing Specifier error" << endl;
               return false;
            }
    }

    else if(argc == 7 || argc == 8)
    {

        if(string(argv[1]) == "-gf")
        {
            inFile.open(argv[2]);

            if(inFile.fail())
            {
                cout << "Error, input file" << endl;
                return false;
            }
            else
                fname = argv[2];
            
            fileSpeErr = true;
        }

        if(string(argv[3])== "-sn")
        {
            sn << string(argv[4]);
            sn >> st;

            for(int i = 0; i < st.length(); i++)
            {
                if(!isdigit(st[i]))
                {
                    cout << "Invalid source node value" << endl;
                    return false;
                }
            }
            start = stoi(st);

            snErr = true;
        }

        if(string(argv[5]) == "-dn")
        {
            ds << string(argv[6]);
            ds >> en;

            for(int i = 0; i < en.length(); i++)
            {
                if(!isdigit(en[i]))
                {
                    cout << "Invalid destination node value" << endl;
                    return false;
                }
            }
            end = stoi(en);

            dsErr = true;
        }

        if(argc == 8)
        {
            if(string(argv[7]) == "-sm")
            {
                showMat = true;
                showErr = true;
            }   

            if(showErr == false)
            {
                cout << "Error, invalid show matrix specifier" << endl;
                return false;
            } 
        }
        else
        {
            showMat = false;
        }


        if(fileSpeErr == false)
            {
                cout << "Error, invalid file specifier" << endl;
                return false;
             }

        if(snErr == false)
            {
                cout << "Error, invalid source node specifier" << endl;
                return false;
            }    

        if(dsErr == false)
            {
                cout << "Error, invalid destination node specifier" << endl;
                return false;
            } 

        if(start == end)
        {
                cout << "Error, stating node and the destination cannot be the same" << endl;
                return false;
        }
       
    }

   

    return true;
}