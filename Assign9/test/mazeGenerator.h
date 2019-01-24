// Prabhas Kumra
// CS 302 - 1004
// Assignment #8

#include <iostream>
#include <string>
#include "disjointSets.h"
#include <cctype>


using namespace std;

class mazeGenerator
{
private:
    int rows;
    int cols;
    int ** walls;

    static constexpr int MIN_ROWS = 5;
    static constexpr int MIN_COLS = 5;
    static constexpr int MAX_ROWS = 100000;
    static constexpr int MAX_COLS = 100000;

public:
    mazeGenerator();
    ~mazeGenerator();
    void getSize(int &, int &) const;
    bool setSize(int, int);
    void generate();
    bool printMazeData(const string) const;
    void printMazeText() const;
    bool getArguments(int, char *[], int &, int &, string &, bool &);
    void randomize();
};