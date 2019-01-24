//  Prabhas Kumra
// Assignment #5
// CS 302-1004
//  wordPuzzle.h
//  
//
//  Created by Prabhas Kumra on 9/25/18.
//

#ifndef wordPuzzle_h
#define wordPuzzle_h

#include <stdio.h>
#include "avlTree.h"

class wordPuzzle: public avlTree<string>
{
public:
    wordPuzzle();
    ~wordPuzzle();
    bool readLetters(const string str);
    bool readDictionary(const string str);
    bool getArguments(int argc, char * argv[], string & str, string & st);
    void findWords();
    void showTitle() const;
    void showWordCount() const;
    void showWords() const;
    void printLetters() const;

private:
    string title;
    int order;
    string ** letters;
    avlTree<string> wordsFound;
    void findWords(int num, int value, string str);

};





#endif /* wordPuzzle_h */
