//  Prabhas Kumra
//
//  sortAlgorithms.cpp
//  
//
//  Created by Prabhas Kumra on 9/11/18.
//

#include "sortAlgorithms.h"
#include <iostream>
#include <iomanip>


// constructer
sortAlgorithms::sortAlgorithms()
{
    length = 0;
    
}

void sortAlgorithms::generateData(int len)
{
    length = len;

    myArray = new short[length];

    //for(int i = 0; i < length; i++)
     //   myArray[i] = rand() % RANGE;

    int k = 0;
    for (int i = 0; i < length; i++)
        {
            myArray[i] = k;
            if (i %( (length/RANGE)+1) == 0)
                k++;
        }
}

int sortAlgorithms::getLength()
{
    return length;
    
}
int sortAlgorithms::getItem(int num)
{
    if(num < 0 || num > length -1 )
        {
        cout << "Error. Invalid Index" << endl;
        return 0;
        }

    else
        return myArray[num];
    
}
void sortAlgorithms::printData()
{
    for(int i = 0; i < length; i++)
    {
        cout << right << setw(4) << myArray[i] << " ";
        if( (i+1) % 12 == 0)
            cout << endl;
    }
}
void sortAlgorithms::bubbleSort()
{
    for(int i = 0; i < length -1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < length-i-1; j++)
        {
            if(myArray[j] > myArray[j+1])
            {
                short temp = myArray[j];
                myArray[j] = myArray[j+1];
                myArray[j+1] = temp;
                swapped = true;
            }
        }
            if(!swapped)
                break;
        
    }
    
}
void sortAlgorithms::insertionSort()
{
    insertionSort(0, length -1 );
    
}
void sortAlgorithms::quickSort()
{
    quickSort(0, length -1);
}
void sortAlgorithms::countSort()
{
    short * count;
    int p = 0;
    count = new short[RANGE];

    for(int i = 0; i < RANGE; i++)
        count[i] = 0;

    for(int i = 0; i < length; i++)
        count[myArray[i]]++;

    for(int i = 0; i < RANGE; i++)
        if(count[i]>0)
            for(int k = 0; k < count[i]; k++)
            {
                myArray[p] = i;
                p++;
            }

    
}

void sortAlgorithms::quickSort(int lo, int hi)
{
    if( lo < hi)
    {
        int piv = partition(lo, hi);

        if ((hi - lo) < 10)
            insertionSort(lo, hi);

        else
        {
            quickSort(lo, piv);
            quickSort(piv +1, hi);
        }

    }
    
}
void sortAlgorithms::insertionSort(int num, int len)
{

    int key =0, j = 0;
    for(int i = num + 1; i < len + 1; i++ )
    {
        key = myArray[i];
        j = i-1;

        while(j >= 0 && myArray[j] > key)
            {
                myArray[j+1] = myArray[j];
                j--;
            }
        myArray[j+1] = key;
    }
    
}
int sortAlgorithms::partition(int lo, int hi)
{
    int piv = medianOf3(hi, lo);
    //int piv = lo;

    int i = lo -1;
    int j = hi +1;

    while(true)
    {
       do
       {
           i++;
       } while ( myArray[i] < piv);
       
       do
       {
           j--;
       } while (myArray[j]> piv);

        if (i >= j)
            return j;

        short temp = myArray[i];
        myArray[i] = myArray[j];
        myArray[j] = temp;

    }
    
}
int sortAlgorithms::medianOf3(int hi , int lo)
{
    int low = myArray[lo];
    int high = myArray[hi];
    int mid = (low + high) / 2; 

   // if((low > high && low < mid) || (low < high && low > mid))
        return low;

    //if((high > low && high < mid) || (high < low && high > mid ))
    //    return high;

   // if((mid > low && mid < high) || (mid < low && mid > high))
    //    return mid;

}


sortAlgorithms::~sortAlgorithms()
{
    delete[] myArray;
    
}
