// Prabhas Kumra
//  CS 302 Assignment #1
//	Provided Main Program

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "bestPath.h"

using namespace std;

// *********************************************************************

int main(int argc, char *argv[])
{

// ---------------
//  Initial declarations.

	enum	algorithmOption {RECURSIVE, DYNAMIC, NONE};
	string		stars;
	stars.append(60, '*');

	algorithmOption	algoOpt = NONE;
	int		order = 0;
	int		bestPathValue = 0;
	bestPath	myPathObj;
	stringstream	ss;

// ---------------
//  Validate command line argument.
//	<-rc|-dy> <order>

	if (argc == 1) {
		cout << "Usage: ./main <-rc|-dy> <order>" << endl;
		exit(1);
	}

	if (argc != 3) {
		cout << "Error, invalid command line options." << endl;
		exit(1);
	}

	if (string(argv[1]) == "-rc")
		algoOpt = RECURSIVE;

	if (string(argv[1]) == "-dy")
		algoOpt = DYNAMIC;

	if (algoOpt == NONE) {
		cout << "Error, invalid algorithm option." << endl;
		exit(1);
	}

	if (string(argv[2]) != "") {
		ss << argv[2];
		ss >> order;
	}

// ---------------
//  Solve (as per selected algorithm).

	if (!myPathObj.createMatrix(order)) {
		cout << "Program terminated." << endl;
		exit(1);
	}

	if (algoOpt == RECURSIVE)
		bestPathValue = myPathObj.bestPthREC();

	if (algoOpt == DYNAMIC)
		bestPathValue = myPathObj.bestPthDY();

// ---------------
//  Display headers, list, and result.

	cout << stars << endl;
	cout << "CS 302 - Assignment #1" << endl;
	cout << "Best Matrix Path Finder." << endl;
	cout << endl;

	cout << "Algorithm: ";
	switch (algoOpt) {
		case RECURSIVE:
			cout << "Recursive" << endl;
			break;
		case DYNAMIC:
			cout << "Dynamic Programming" << endl;
			break;
		default:
			cout << "Error, invalid selection." << endl;
			break;
	}
	cout << endl;
	myPathObj.displayMatrix();
	cout << endl;
	cout << "Best Possible = " << bestPathValue << endl;

// ---------------
//  Done, end program.

	return 0;
}


