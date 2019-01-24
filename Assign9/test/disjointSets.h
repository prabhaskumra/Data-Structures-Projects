// Prabhas Kumra
// CS 302 - 1004
// Assignment #8

#include <iostream>
#include <string>

using namespace std;

class disjointSets
{
private:
    int setSize;
    int * links;
    int * ranks;
    static constexpr int MIN_SIZE = 10;

public:
    disjointSets(int = 10);
    ~disjointSets();
    int entries() const;
    void printSets() const;
    int setUnion(int, int);
    int setFind(int);
};