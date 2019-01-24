// Prabhas Kumra
// CS 302 - 1004
// Assignment #9


#include <iostream>
#include <string>
#include "disjointSets.h"
#include <iomanip>

using namespace std;



disjointSets::disjointSets(int size)
{


    if(size >= MIN_SIZE)
    {
        setSize = size;
        links = new int[size];
        ranks = new int[size];

        for(int i = 0; i < setSize; i++)
        {
            links[i] = -1;
            ranks[i] = 1;
        }
    }
    else
    {
        setSize = MIN_SIZE;
        links = new int[MIN_SIZE];
        ranks = new int[MIN_SIZE];

        for(int i = 0; i < setSize; i++)
        {
            links[i] = -1;
            ranks[i] = 1;
        }
    }
}

disjointSets::~disjointSets()
{
    delete[] ranks;
    delete[] links;
}

int disjointSets::entries() const
{
    return setSize;
}

void disjointSets::printSets() const
{
    

    for(int i = 0; i < setSize; i++)
    {
        if(i == 0)
            cout << "   Index:";

        cout << setw(3) << i;
    }
    cout << endl;

    for(int i = 0; i < setSize; i++)
    {
        if(i == 0)
            cout << "   links:";

        cout << setw(3) << links[i];
    }
    cout << endl;


     for(int i = 0; i < setSize; i++)
    {
        if(i == 0)
            cout << "   ranks:";

        cout << setw(3) << ranks[i];
    }
    cout << endl;   
}


int disjointSets::setUnion(int r1, int r2)
{
    if(r1 >= setSize || r2 >= setSize || r1 < 0 || r2 < 0)
        return -1;

    int p, c;

    if(setFind(r1) != -1)
        r1 = setFind(r1);

    if(setFind(r2) != -1)
        r2 = setFind(r2);

    if(ranks[r1] <= ranks[r2])
    {
        p = r2;
        c = r1;
    }
    else
    {
        p = r1;
        c = r2;
    }

    links[c] = p;

    if(ranks[r1] ==  ranks[r2])
        ranks[p]++;

    return p;

}

int disjointSets::setFind(int index)
{

    if(index >= setSize)
        return -1;

    if(links[index] < 0)
        return index;

    else
        return (links[index] = setFind(links[index]));
}
