// Prabhas Kumra
// CS 302 - 1004
//  sortAlgorithms.h
//  
//
//  Created by Prabhas Kumra on 9/11/18.
//

#ifndef sortAlgorithms_h
#define sortAlgorithms_h
using namespace std;



class sortAlgorithms
{
    
public:
    sortAlgorithms();
    ~sortAlgorithms();
    void generateData(int);
    int getLength();
    int getItem(int);
    void printData();
    void bubbleSort();
    void insertionSort();
    void quickSort();
    void countSort();
    
private:
    int length;
    short *myArray;
    static const int RANGE = 1000;
    void quickSort(int, int);
    void insertionSort(int, int);
    int partition(int, int);
    int medianOf3(int, int);
    
};


#endif /* sortAlgorithms_h */
