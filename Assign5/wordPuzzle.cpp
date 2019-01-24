//  Prabhas Kumra
// Assignment #5
// CS 302-1004
//  wordPuzzle.cpp
//  
//
//  Created by Prabhas Kumra on 9/25/18.
//

#include "wordPuzzle.h"
#include <iostream>
#include <string>
#include <fstream>



using namespace std;


wordPuzzle::wordPuzzle()
{
    title = "";
    order = 0;
    
}
wordPuzzle::~wordPuzzle()
{

}
bool wordPuzzle::readLetters(const string str)
{
    fstream inFile;

    inFile.open(str);

    //if(inFile.fail());
      //  return false;

    string st = "";
    int num = 0;

    getline(inFile,st);
    title = st;

    inFile >> num;
    order = num;

    char ch;


    letters = new string* [order];
    for(int i = 0; i<order; i++)
        letters[i] = new string[order];

    for(int i = 0; i<order; i++)
        for(int j = 0; j < order; j++)
        {
            inFile >> ch;
            letters[i][j] = ch;
            cout << ch;
        }

    return true;
}
bool wordPuzzle::readDictionary(const string str)
{
    fstream inFile;

    inFile.open(str);

    if(inFile.fail())
        return false;

    string data = "";

    //getline(inFile, data);
    
    inFile >> data;
    while(inFile)
    {
        insert(data);
        inFile >> data;
    }

    inFile.close();

    return true;

}

bool wordPuzzle::getArguments(int argc, char * argv[], string & str, string & st)
{
    if (argc == 1) {
        cout << "Usage: ./findWords -d <dictionaryFile> -w <wordsFile>" << endl;
        return false;
    }
    
   /* if(argv[1] != "-d")
    {
        cout << "Error1, command line arrguments invalid." << endl;
        return false;
    }

    if(argv[3] != "-w")
    {
        cout << "Error2, command line arrguments invalid." << endl;
        return false;
    }*/

    if (argc != 5) {
        cout << "Error, command line arrguments invalid." << endl;
        return false;
    }

    
    
    ifstream inFile;
    
    inFile.open(argv[2]);
    
    if(inFile.fail()){
        cout << "Error, command line arguments invalid" << endl;
        return false;
    }
    else{
        //getline(inFile, str);
        str = argv[2];
    }
    
    inFile.close();
    
    inFile.open(argv[4]);
    
    if(inFile.fail()){
        cout << "Error, command line arguments invalid" << endl;
        return false;
    }
    else{
        st = argv[4];
        //getline(inFile, st);
    }
    
    inFile.close();
    
    return true;
}
void wordPuzzle::findWords()
{

}
void wordPuzzle::showTitle() const
{

}
void wordPuzzle::showWordCount() const
{

}
void wordPuzzle::showWords() const
{

}
void wordPuzzle::printLetters() const
{

}
void wordPuzzle::findWords(int, int, string)
{

}


