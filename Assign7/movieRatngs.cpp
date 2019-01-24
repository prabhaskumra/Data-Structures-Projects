// Prabhas Kumra
// Assignment #7
// CS 302-1004


#include "assocArray.h"
#include <iostream>
#include <string>
#include <fstream>


using namespace std;


bool getArguments(int argc, char * argv[], string & input, string & output);



int main(int argc, char * argv[])
{

  string stars;
	stars.append(60, '*');

  string input, output;


  if(!getArguments(argc, argv, input, output))
    exit(1);

  cout << stars << endl;

  cout <<"CS 302 - Assignment #7" << endl;











  return 0;
}


bool getArguments(int argc, char * argv[], string & input, string & output)
{


    if (argc == 1) {
		cout << "Usage: ./movieRatings -i <moviesFile> -o <outputFile>" << endl;
		  return false;//exit(1);
	}

    if (argc != 5) {
		cout << "Error, invalid command line options." << endl;
		return false; //exit(1);
	}

    if (string(argv[1]) != "-i"){
		cout << "Error, invalid intput file specifier." << endl;
		return false; //exit(1);
	}

    if (string(argv[3]) != "-o"){
		cout << "Error, invalid output file specifier." << endl;
		return false; //exit(1);
	}

    ifstream inFile;
    ofstream outFile;

    inFile.open(argv[2]);

    if(inFile.fail())
    {
      cout << "Error, unable to input File" << endl;
      return false;
    }
      else
        input = argv[2];


    outFile.open(argv[4]);

    if(inFile.fail())
    {
      cout << "Error, invalid output file specifier" << endl;
      return false;
    }
    else
      output = argv[4];
   
    inFile.close();

    return true;
    
}