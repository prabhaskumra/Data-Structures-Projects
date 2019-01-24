// Prabhas Kumra
// Assignment #7
// CS 302-1004


#include "assocArray.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>


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

  //cout << input << endl;

  assocArray<double> hashTable;

  string names;
  double ratings;
  string ratStr;
  string year;


  ifstream inFile;
  ofstream outFile;

  inFile.open(input);
 

  int count = 0;
  double sum = 0;
  double average = 0;
  double min1, min2, min3;
  double max1, max2, max3;

/*
  getline(inFile, names, '\t');

  while( inFile >>  ratings >> year)
  {
    //inFile >> ratings >> year;
    if (names != "\n")
  {
    if(hashTable.exists(names + "-" + year))
    {
      average = hashTable[names + "-" + year];
      average = (ratings + average) / 2;
      hashTable[names + "-" + year] = average;
    }
    else
    {
      hashTable[names + "-" + year] = ratings;
      count++;
    }
    
    sum += ratings;
    

    getline(inFile, names, '\t');
    }
  }*/

  while( getline(inFile, names, '\t'))
  {

        if (names != "\n")
        {
          getline(inFile, ratStr, '\t');

          getline(inFile, year);
          ratings = stod(ratStr);

          if(hashTable.exists(names + "-" + year))
          {
            average = hashTable[names + "-" + year];
            average = (ratings + average) / 2;
            hashTable[names + "-" + year] = average;
          }
          else
          {
            hashTable[names + "-" + year] = ratings;
           
          }

           count++;
          sum += ratings;

        }

  }


    outFile.open(output);

    min1 = 10;
    min2 = 10;
    min3 = 10;

    max1 = 0;
    max2 = 0;
    max3 = 0;

    string mi1, mi2, mi3, ma1, ma2, ma3;

    for (string curr = hashTable.begin(); curr != hashTable.end(); curr = hashTable.next())
    {
      if(min1 > hashTable[curr])
        {
          min3 = min2;
          mi3 = mi2;
          min2 = min1;
          mi2 = mi1;

          min1 = hashTable[curr];
          mi1 = curr;

        }
      else if(min2 > hashTable[curr])
      {
        min3 = min2;
        mi3 = mi2;
        min2 = hashTable[curr];
        mi2 = curr;
      }
      else if(min3 > hashTable[curr])
      {
        min3 = hashTable[curr];
        mi3 = curr;
      }

      if(min2 > hashTable[curr] && hashTable[curr] < min1 )
        min2 = hashTable[curr];

      if(min3 > hashTable[curr] && hashTable[curr] < min2 )
        min3 = hashTable[curr];




      //************************************************
        if(max1 < hashTable[curr])
        {
          max3 = max2;
          ma3 = ma2;
          max2 = max1;
          ma2 = ma1;

          max1 = hashTable[curr];
          ma1 = curr;

        }
      else if(max2 < hashTable[curr])
      {
        max3 = max2;
        ma3 = ma2;
        max2 = hashTable[curr];
        ma2 = curr;
      }
      else if(max3 < hashTable[curr])
      {
        max3 = hashTable[curr];
        ma3 = curr;
      }

      if(max2 < hashTable[curr] && hashTable[curr] > max1 )
        max2 = hashTable[curr];

      if(max3 < hashTable[curr] && hashTable[curr] > max2 )
        max3 = hashTable[curr];


        //***********************************************************

      outFile  << curr << " " <<  "Score: " << hashTable[curr] << endl;
	  
    }

    cout << "Overall Average: " << ((sum)/double(count)) << endl << endl;

    cout << "Lowest Ratingd Movies:" << endl;
    cout <<  "  Movie: "  << left << setw(60)<< mi1 << " Score: " << min1 << endl;
    cout <<  "  Movie: "  << setw(60) << mi2 <<" Score: " << min2 << endl;
    cout <<  "  Movie: "  << setw(60) << mi3 <<" Score: " << min3 << endl;

    cout << endl;
    cout << "Highest Rated Movies: " << endl;
     cout << "  Movie: "  << setw(60)<< ma1 << " Score: " << max1 << endl;
    cout <<  "  Movie: "  << setw(60) << ma2 <<" Score: " << max2 << endl;
    cout <<  "  Movie: "  << setw(60) << ma3 <<" Score: " << max3 << endl;


      //outFile << endl << "Values Sum: " << sum << endl;
    //cout << curr <<  left << setw(8) << "   " << hashTable[curr] <<  endl;
	  //cout <<  endl << endl;

    cout << endl;
    //cout << " Count: " << count << endl;





  hashTable.showStats();
  cout << endl;
  cout << stars << endl;
  cout << "Game Over, thank you for playing." << endl;

  inFile.close();
	outFile.close();

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


    //getline(inFile, input);
    //outFile << input;


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
