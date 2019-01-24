// Prabhas Kumra
// Assignment# 11
// CS 302-1004


#include "ganttUtils.h"
#include "linkedQueue.h"
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

ganttUtils::ganttUtils()
{
 
  edgeCount = 0;
  title = "";
  graphList = NULL;
  dist = NULL;
  prev = NULL;
  topoNodes = NULL;
  topoCount = 0;

  taskDensity = 0.0;
  mileStonesRatio = 0.0;


}
ganttUtils::~ganttUtils()
{
  destroyGraph();
}
void ganttUtils::destroyGraph()
{

  delete[] graphList;

}
void ganttUtils::newGraph(int size)
{
  graphList = new gList[size];

  for(int i = 0; i < size; i++)
  {
    graphList[i].head = NULL;
    graphList[i].counts = 0;
  }

}
void ganttUtils::addEdge(int start, int end, int value)
{
  if(start < 0 || end < 0)
  {
    cout << "addEdge: Error, invalid vertex " << endl;
    return;
  }
  if(start == end)
  {
    cout << "addEdge: Error, to and form vertex cannot be same" << endl;
    return;
  }

  
  if(graphList[start].head == NULL)
  {

    graphNode * node = new graphNode;
    node->vertex = end;
    node->weight = value;
    node->next = NULL;

    graphList[start].head = node;
    //graphList[start].tail = node;
    //graphList[start].tail->next = NULL;
    graphList[start].counts++;
  }
  else
  {
    graphNode * temp = graphList[start].head;
    while(temp->next != NULL)
    {
      if(temp->vertex == end)
      {
        temp->weight = value;
        return;
      }
      //if(temp->vertex > end)
        //break;
      temp = temp->next;
    }


    graphNode * node = new graphNode;
    node->vertex = end;
    node->weight = value;
    //node->next = NULL;
    node->next = graphList[start].head;

    graphList[start].head = node;

    graphList[start].counts++;
   
  }

  edgeCount++;

}
bool ganttUtils::getArguments(int argc, char * argv[], string & fname, bool & printFlag)
{
  ifstream inFile;
  //ofstream outFile;
  bool fileError = false, printSpec = false;

  
  if(argc == 1)
    {
      cout << "usage: ./projectInfo -f <filename>" << endl;
      return false;
    }
  
  if(argc < 3 || argc > 4)
    {
      cout << "Error, command line options" << endl;
      return false;
    }
  

  if(argc == 3)
    {
      if(string(argv[1]) == "-f")
	{
	  inFile.open(argv[2]);

	  if(inFile.fail())
	    {
	      cout << "Error, input file" << endl;
	      return false;
	    }
	  else
	    fname = argv[2];

	  fileError = true;
	}

      printFlag  = false;
    }

  if(argc == 4)
  {
      if(string(argv[1]) == "-f")
	    {
          inFile.open(argv[2]);

          if(inFile.fail())
            {
              cout << "Error, input file" << endl;
              return false;
            }
          else
            fname = argv[2];

          fileError = true;
        }

    if(string(argv[3]) == "-p")
	  {
	    printFlag = true;
	    printSpec = true;
	  }

    if(!printSpec)
	  {
	    cout << "Error, invalid print specifier" << endl;
	    return false;
	  }
  }

  if(!fileError)
    {
      cout << "Error, invalid file specifier" << endl;
      return false;
    }
 
  return true;
  
}
bool ganttUtils::readGraph(string fname)
{
  fstream inFile;
  inFile.open(fname);
  string count, count1 = "";
  string name;
  

  getline(inFile, title);
  getline(inFile, count);
  
  //int size = stoi(count);

  for(int i = 0; i < count.length(); i++)
    if(isdigit(count[i]))
      count1 = count1 + count[i];

  mileStones = stoi(count1);

  getline(inFile, count);
  count1 = "";

  for(int i = 0; i < count.length(); i++)
    if(isdigit(count[i]))
      count1 = count1 + count[i];
  
  source = stoi(count1);
 
  newGraph(mileStones);

  int start, end, value;

  inFile >> start;
  while(inFile)
  {
      inFile >> end >> value;

      addEdge(start, end, value);

      inFile >> start;
  }


  //cout <<"counts: " << graphList[4].counts << endl;

  return true;

}
bool ganttUtils::isValidProject()
{
  bool visited[mileStones];
  bool marked[mileStones];

  for(int i = 0; i < mileStones; i++)
  {
    visited[i] = false;
    marked[i] = false;
  }

  for(int i = 0; i < mileStones; i++)
  {
    if(!visited[i])
     if(isCycle(i, visited, marked))
        return false;
  }

  return true;
}

bool ganttUtils::isCycle(int v, bool  vist[], bool  mark[])
{

  if(!vist[v])
  {
    vist[v] = true;
    mark[v] = true;

    int u;
    graphNode * temp = graphList[v].head;
    int counter = 0;

      while(counter < graphList[v].counts)
      {
        u = temp->vertex;

        if (isCycle(u, vist, mark))
          return true;
        else if(mark[u])
          return true;

        temp = temp->next;
        counter++;

      }
     mark[v] = false;
  }

  return false;
}
int ganttUtils::getTaskCount()
{
  return edgeCount;
}

int ganttUtils::getTime(int v, int u)
{
  graphNode * temp =  graphList[v].head;

  while(temp->next != NULL)
  {
    if(temp->vertex == u)
      return temp->weight;
    temp = temp->next;
  }
}
void ganttUtils::findGraphInformation()
{
  mileStonesRatio = double(getTaskCount()) / double(mileStones);

  taskDensity = (2 * double(getTaskCount())) / (double(mileStones) * (double(mileStones) - 1));
}

void ganttUtils::findinDegree()
{

  indegree = new int[mileStones];

  for(int i =0;i<mileStones;i++)
    indegree[i] = 0;

  int index = 0;
  int counter = 0;
  graphNode * temp;

  while(index < mileStones)
  {
    counter = 0;
    temp = graphList[index].head;

    while(counter < graphList[index].counts)
    {
      indegree[temp->vertex]++;
      temp = temp->next;
      counter++;
    }
    index++;
  }
}
void ganttUtils::findKeyMilestone()
{
  keyMilestone = 0;
  keyTask = 0;
  
  for(int i = 0; i < mileStones; i++)
  {
    if(indegree[i] >= keyTask)
    {
      keyTask = indegree[i];
      keyMilestone = i;
    } 
  }
}
void ganttUtils::findNodePoint()
{
  nodePoint = 0;
  nodeTask = 0;
  

  for(int i = 0; i < mileStones; i++)
  {
    if(graphList[i].counts > nodeTask)
    {
      nodeTask = graphList[i].counts;
      nodePoint = i;
    }   

   // if(graphList[i].counts < )

  }
}
void ganttUtils::findDependencyStats()
{

  inMax = 0, inmaxCount = 0;
  inMin = std::numeric_limits<int>::max(); 
  inminCount = 0;
  outMax = 0, outmaxCount =0;
  outMin = std::numeric_limits<int>::max();
  outminCount = 0;

  for(int i = 0; i < mileStones; i++)
  {
    // in degree

    if(indegree[i] > inMax && i != source)
      inMax = indegree[i];

    if(indegree[i] < inMin && i != source)
      inMin = indegree[i];
    // **********************************************************
    // Out degrees

     if(graphList[i].counts > outMax && i != finalTask)
      outMax = graphList[i].counts;

    if(graphList[i].counts < outMin && i != finalTask)
      outMin = graphList[i].counts;
    
  //************************************** counts
  }

 
  for(int i = 0; i < mileStones; i++)
  {

    if(indegree[i] == inMax && i != source)
      inmaxCount++;

    if(indegree[i] == inMin && i != source)
      inminCount++;

     if(graphList[i].counts == outMax && i != finalTask)
      outmaxCount++;

    if(graphList[i].counts == outMin && i != finalTask)
      outminCount++;
  }
    

}
void ganttUtils::findIndependentMilestones()
{
  indMilestone = new bool[mileStones];
  for(int i = 0; i < mileStones; i++)
    indMilestone[i] = false;

  for(int i = 0; i < mileStones; i++)
  {
    if(graphList[i].counts == 0)
      indMilestone[i] = true;
  }
}
void ganttUtils::findAPs()
{
  bool visited[mileStones];
  //bool aps[mileStones];
  aps = new bool[mileStones];
  int parent[mileStones];
  int low[mileStones];
  int discovered[mileStones];

  for(int i = 0; i < mileStones; i++)
  {
    visited[i] = false;
    aps[i] = false;
    parent[i] = -1;
    low[i] = 0;
    discovered[i] = 0;
  }

  for(int v =0; v < mileStones; v++)
  {
    if(!visited[v])
      findAPsHelper(v, visited, discovered, low, parent);
  }


}

void ganttUtils::findAPsHelper(int v, bool visited[], int discovered[], int low[], int parent[])
{
  int children = 0, myTime = 0;
  visited[v] = true;
  
  myTime++;
  discovered[v] = myTime;
  low[v] = myTime;
  //discovered[v] = low[v] = ++myTime;
  graphNode * temp =  graphList[v].head;

  for(int i = 0; i < graphList[v].counts; i++)
  {
    if(!visited[temp->vertex])
    {
      children++;
      parent[temp->vertex] = v;

      findAPsHelper(temp->vertex, visited, discovered, low, parent);
      low[v] = min(low[v], low[temp->vertex]);

      if(parent[v] == -1 && children > 1)
        aps[v] = true;
      if(parent[v] != -1 && (low[temp->vertex] >= discovered[v]) )
        aps[v] = true;
    }
    else if(v != parent[v])
      low[v] = min(low[v], discovered[temp->vertex]);

    temp = temp->next;

  }

    
}

void ganttUtils::topoSort()
{
  int * inDegree = new int[mileStones];
  topoNodes = new int[mileStones];

  for(int i = 0; i < mileStones; i++)
  {
    inDegree[i] = indegree[i];
    
    topoNodes[i] = 0;
  }
  topoCount = 0;

  linkedQueue<int> Q;

  for(int i = 0; i < mileStones; i++)
      if(inDegree[i] == 0)
          Q.addItem(i);

  int dQ;
  graphNode * node;

  while(!Q.isEmptyQueue())
  {
    dQ = Q.front();
    Q.deleteItem();

    topoNodes[topoCount] = dQ;
    topoCount++;

    node = graphList[dQ].head;

    for(int i = 0; i < graphList[dQ].counts; i++)
    {
      inDegree[node->vertex]--;
      if(inDegree[node->vertex] == 0)
        Q.addItem(node->vertex);

      node = node->next;
    } 
  }
}
void ganttUtils::criticalPath()
{
  dist = new int[mileStones];
  int * inDegree = new int[mileStones];

  for(int i = 0; i < mileStones; i++)
  {
    dist[i] = 0;
    inDegree[i] = indegree[i];
  }


  linkedQueue<int> Q;

  for(int i = 0; i < mileStones; i++)
      if(inDegree[i] == 0)
          Q.addItem(i);

  int v;
  graphNode * node;

  int myTime;

  while(!Q.isEmptyQueue())
  {   
    v = Q.front();
    Q.deleteItem();

    node = graphList[v].head;

    while(node != NULL)
    {
      myTime = node->weight;

      dist[node->vertex] = max( dist[node->vertex], dist[v] + myTime);
      inDegree[node->vertex] -= 1;

      if(inDegree[node->vertex] == 0)
        Q.addItem(node->vertex);

      node = node->next;
      
    }
  }


  int x = 0;
  duration = 0;

  for(int i = 0; i < mileStones; i++)
  {
    if(i == 0)
      duration =dist[i];
    if(dist[i] > dist[x])
    {
      duration = dist[i];
      x = i;
    }
  }
  finalTask = x;

    crPath = new int[mileStones];

  for(int i = 0; i < mileStones; i++)
    {
      crPath[i] = -1;
    }

  crPathCount = 0;

  crPath[crPathCount] = x;
  crPathCount++;

  graphNode * gNode;

  while(x != source)
  {
    for(int v = 0; v < mileStones; v++)
    {
      gNode = graphList[v].head;

      while(gNode != NULL)
      {
        myTime = gNode->weight;
        if(x == gNode->vertex)
        {
          if(dist[x] == (dist[v] + myTime))
          {
            crPath[crPathCount] = v;
            crPathCount++;
            x = v;
          }
        }
        gNode = gNode->next;
      }
    }
  }
  cout << "NOT HERE" << endl;
  
 
}
void ganttUtils::findSlackTimes()
{
  slackTimes = new int[mileStones];

  for(int i = 0; i < mileStones; i++)
  {
    slackTimes[i] = -1;
  }

  for(int i = 0; i < mileStones; i++)
  {
      slackTimes[crPath[i]] = 0;
  }

  int myTime;
  graphNode * temp;
  for(int u = 0; u < mileStones; u++)
  { 
    if(slackTimes[u] == -1)
    {
      temp = graphList[u].head;
      
      while(temp != NULL)
      {
        myTime = temp->weight;
        slackTimes[u] = dist[temp->vertex] - (dist[u] + myTime);

        temp = temp->next;
      }
    }
  }


}
void ganttUtils::printGraphInformation()
{
  printBars();
  cout << "Graph Information" << endl;
  cout << "   Project title: " << title << endl;
  cout << "   Milestone Count: " << mileStones << endl;
  cout << "   Task Count: " << getTaskCount() << endl;
  cout << "   Source Milestones: " << source << endl;
  cout << "   Tasks/Milestones Ration: " << mileStonesRatio << endl;
  cout << "   Project Tasks Density: " << taskDensity << endl << endl;
  
  cout << "   Key Milestone: " << keyMilestone <<", in-degree: "<<keyTask <<  " tasks" << endl;
  cout << "   Node Point: " <<nodePoint<< ", out-degree: " <<nodeTask <<" tasks" << endl;
  cout << "   Independent Milestones" << endl << " ";
  
  for(int i = 0; i < mileStones; i++)
  {
    if(indMilestone[i])
      cout << i << " ";
  }
  cout << endl << endl;
}
void ganttUtils::printGraph()
{
  printBars();
  cout << "Graph Adjacency List" << endl;
  cout << "   Title: " << title << endl << endl;

  cout << "Vertex    " ;
  for(int i = 0; i < 3; i++)
  {
    cout << "vrt /weight | ";
  }
  cout << "..." << endl;

  cout << "------    ------------------------------------------------" << endl;

  graphNode * temp;
  for(int i = 0; i < mileStones; i++)
  {
    cout << setw(6) << i << " ->" << setw(5);
    temp = graphList[i].head;

    if(temp == NULL)
      cout << "    NONE";
    
    else
      {
        while(temp != NULL)
        {
      
          cout << temp->vertex << "/" << setw(6) << temp->weight << " |" << setw(5);

          temp = temp->next;
        }
      }
      cout << endl;
    }
    cout << endl << endl;
    

} 
void ganttUtils::printDependencyStats()
{
  printBars();
  cout << "Dependency Statistics (in-degree):" << endl;
  cout << "   Highest In-Degree: "<< inMax << endl;
  cout << "   Lowest In-Degree: " << inMin << endl;
  cout << "   Count of Highest In-Degree: "<< inmaxCount << endl;
  cout << "   Count of Lowest In-Degree: "<< inminCount << endl << endl;

  cout << "Dependency Statistics (out-degree):" << endl;
  cout << "   Highest Out-Degree: " << outMax <<endl;
  cout << "   Lowest Out-Degree: " << outMin << endl;
  cout << "   Count Out Highest In-Degree: "<< outmaxCount << endl;
  cout << "   Count Out Lowest In-Degree: " << outminCount << endl << endl;


}
void ganttUtils::printTopoSort()
{
  printBars();
  cout << "Topological Sort:" << endl;
    for(int i = 0; i < mileStones; i++)
        cout << topoNodes[i] <<" ";
    cout << endl << endl;
    
}
void ganttUtils::printAPs()
{
  printBars();
  cout << "Articulations Points:" << endl;
  for(int i = 0; i < mileStones; i++)
    if(aps[i] == true)
      cout << right <<  i << " " << setw(2);
  cout << endl << endl;
}
void ganttUtils::printCriticalPath()
{
  printBars();
  cout << "Critical Path" << endl;
  cout << "   Source Node: " << source << endl;
  cout << "   Final Task: " << finalTask << endl;
  cout << "   Total Duration: " << duration << endl << endl;

  cout << "Critical Path:" << endl;
   for(int i = crPathCount-1; i >=0; i--)
    cout << crPath[i] << " ";
  cout << endl << endl;

}
void ganttUtils::printSlackTimes()
{
  printBars();
  cout << "Slack Time (task-slacktime):" << endl;
  for(int i = 0; i < mileStones; i++)
  {
    if(slackTimes[i] != 0 && slackTimes[i] != -1)
      cout << " " << i  << "-" << slackTimes[i];
  }


  cout << endl << endl;
}

void ganttUtils::printBars()
{
  string		bars = "";
  bars.append(60, '-');
  cout << bars << endl;
}
