#include <string>
#include <iostream>
using namespace std;

class bestPath
{
public:
    bestPath();
    ~bestPath();
    void displayMatrix();
    bool createMatrix(const int);
    int bestPthDY();
    int bestPthREC();    
    
private:
    int matrixOrder;
    int ** matrix;
    static const int LIMIT = 999;
    static const int MIN_ORDER = 5;
    static const int MAX_ORDER = 100;

    int bestPthREC1(int, int);
    
    
};

