//  CS 302
//  Provided Main Program
//  Sorting algorithms assignment

//  Implements:
//	bubble sort
//	inserton sort
//	quick sort
//	count sort

// ***********************************************************************
//  Includes and prototypes.
  
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

#include "sortAlgorithms.h"

// *******************************************************************

int main(int argc, char *argv[])
{
// ------------------------------
//  Declarations and headers.

	const	int	MIN_LENGTH = 50;
	const	int	MAX_LENGTH = 10000000;

	enum	algorithmOption {BUBBLE, INSERTION, COUNTING,
					QUICK, NOSORT, NONE};

	bool		showNumbers=false;
	int		length;
	string		stars;
	stringstream	mySS;
	algorithmOption	userChoice = NONE;

	stars.append(60,'*');

// ------------------------------
//  Verify command line arguments.
//	Error out if bad, set user selection if good.
//	Note, -p option only used for testing.

	if (argc == 1) {
		cout << "Usage: sorts <-bs|-is|-qs|-cs|-ns> -l <length> <-p>" << endl;
		exit(1);
	}

	if (argc < 4 || argc > 5) {
		cout << "Error, invalid command line options." << endl;
		exit(1);
	}

	if (string(argv[1]) == "-bs")
		userChoice = BUBBLE;

	if (string(argv[1]) == "-is")
		userChoice = INSERTION;

	if (string(argv[1]) == "-qs")
		userChoice = QUICK;

	if (string(argv[1]) == "-cs")
		userChoice = COUNTING;

	if (string(argv[1]) == "-ns")
		userChoice = NOSORT;

	if (userChoice == NONE) {
		cout << "Error, invalid sort option." << endl;
		exit(1);
	}

	if (string(argv[2]) != "-l") {
		cout << "Error, invalid length specifier." << endl;
		exit(1);
	}

	if (string(argv[3]) != "") {
		mySS << argv[3];
		mySS >> length;
		if (mySS.fail() || !mySS.eof()) {
			cout << "Error, invalid length value." << endl;
			exit(1);
		}
		if (length < MIN_LENGTH || length > MAX_LENGTH) {
			cout << "Error, invalid length." << endl;
			exit(1);
		}
	}

	if (argc == 5)
		if (string(argv[4]) == "-p")
			showNumbers = true;

// ------------------------------
//  Command line args ok, display initial headers.

	cout << stars << endl;
	cout << "CS 302 - Assignment #3" << endl;
	cout << "Sorting Algorithms." << endl;
	cout << endl;

// ------------------------------
//  Generate random values.

	sortAlgorithms	myData;
	myData.generateData(length);

// ------------------------------
//  Call selected sorted.
//	The NOSORT option is for testing...

	switch (userChoice) {

		case BUBBLE:
			cout << "Bubble Sort..." << endl;
			myData.bubbleSort();
			break;

		case INSERTION:
			cout << "Insertion Sort..." << endl;
			myData.insertionSort();
			break;

		case QUICK:
			cout << "Quick Sort..." << endl;
			myData.quickSort();
			break;

		case COUNTING:
			cout << "Count Sort..." << endl;
			myData.countSort();
			break;

		case NOSORT:
		case NONE:
			break;

	}

// ------------------------------
//  Verify sort worked correctly...

	if (userChoice != NOSORT) {
		for (int i=1; i<myData.getLength(); i++) {
			if (myData.getItem(i-1) > myData.getItem(i)) {
				cout << "Error, epic sort fail." << endl;
				cout << "Do not pass go, do not collect score." << endl;
			}
		}
	}

// ------------------------------
//  If print option, show numbers (if < 1000).

	if (showNumbers) {
		if (length <= 1000)
			myData.printData();
		else
			cout << "Printing, " << length <<
				" umm, I don't think so..." << endl;
	}

// ------------------------------
//  Done, terminate program.

	cout << endl;
	cout << "Game over, thanks for playing." << endl;

	return 0;
}

