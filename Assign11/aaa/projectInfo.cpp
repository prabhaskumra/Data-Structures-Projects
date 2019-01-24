//  CS 302 - Assignment #11
//  Find project gantt information.

#include <cstdlib>
#include <iostream>
#include <thread>

using namespace std;

#include "ganttUtils.h"

int main(int argc, char *argv[])
{

// *****************************************************************
//  Headers...

	const int	LIMIT = 10;
	const char	*bold = "\033[1m";
	const char	*unbold = "\033[0m";
	string		stars = "";
	string		tasksFile = "";
	string		dotFile = "";
	bool		printFlag = false;
	ganttUtils	myProject;

	stars.append(65, '*');

	//thread * thd = new thread[8];

// ------------------------------------------------------------------
//  Perform initial checks.
//	command line arguments
//	read project tasks file
//	basic validation of tasks file



	//thd[1]  = thread(myProject::getArguments(argc, argv, tasksFile, printFlag)) 
	if (!myProject.getArguments(argc, argv, tasksFile, printFlag))
		exit(1);

	if (!myProject.readGraph(tasksFile)) {
		cout << "Error, can not find project file." << endl;
		exit(1);
	}

	if(!myProject.isValidProject()) {
		cout << "Invalid task list." << endl;
		exit(1);
	}

// ------------------------------------------------------------------
//  Display headers, verify enough tasks...

	cout << stars << endl << bold << "CS 302 - Assignment #11" << endl;
	cout << "Gantt Analysis Project" << unbold << endl;
	cout << endl;

	if (myProject.getTaskCount() < LIMIT) {
		cout << "Error, too few tasks." << endl;
		exit(1);
	}

// ------------------------------------------------------------------
//  Find project information
//	Note, some of these function can be threaded...



// ----------
//  To initiate a thread for an object function:
//	thread thd1(&<objectName>::<functionName>);
//  Note, as usual, must join to ensure completed:
//	thd1.join()
	thread thd1(&ganttUtils::findinDegree, &myProject);
	thd1.join();


	myProject.findGraphInformation();
	myProject.findKeyMilestone();
	myProject.findNodePoint();
	myProject.findIndependentMilestones();

	thread thd2(&ganttUtils::findAPs, &myProject);
	thd2.join();

	//myProject.findAPs();
	thread thd3(&ganttUtils::topoSort, &myProject);
	thd3.join();

	//myProject.topoSort();

	thread thd4(&ganttUtils::criticalPath, &myProject);
	thd4.join();

	//myProject.criticalPath();

	thread thd5(&ganttUtils::findSlackTimes, &myProject);
	thd5.join();


	/*thd1.join();
	thd2.join();
	thd3.join();
	thd4.join();
	thd5.join();*/
	
	//myProject.findSlackTimes();
	myProject.findDependencyStats();

// -----
//  Display project information.
//	Note, all calculations done, just display results.

	myProject.printGraphInformation();

	if (printFlag)
		myProject.printGraph();

	myProject.printDependencyStats();
	myProject.printTopoSort();
	myProject.printAPs();
	myProject.printCriticalPath();
	myProject.printSlackTimes();

// *****************************************************************
//  All done.

	cout << stars << endl;
	cout << "Game Over, thank you for playing." << endl;

	return 0;
}

