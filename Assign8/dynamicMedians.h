// Prabhas Kumra
// CS 302-1004
// Assignment #8


#ifndef dynamicMediansp_h
#define dynamicMediansp_h

#include <iostream>
#include <string>
#include "minHeap.h"
#include "maxHeap.h"

using namespace std;

template <class myType>
class dynamicMedians
{
private:
    int arrLength;
    myType * myData;
    myType * mediansArr;
    static const unsigned int MIN_LENGTH = 5;

public:
    dynamicMedians();
    ~dynamicMedians();
    bool setData(myType [], const int);
    bool generateData(const int, const int);
    void showData() const;
    void showMedians() const;
    myType getDataItem(const unsigned int) const;
    myType getMediansItem(const unsigned int) const;
    void findMedians();
};

template <class myType>
dynamicMedians<myType>::dynamicMedians()
{
    arrLength = 1000;
    myData = NULL;//new myType[arrLength];

    mediansArr = NULL;//new myType[arrLength];

}

template <class myType>
dynamicMedians<myType>::~dynamicMedians()
{
    delete[] myData;
    delete[] mediansArr;
}

template <class myType>
bool dynamicMedians<myType>::setData(myType arr[], const int size)
{
    if(size >= MIN_LENGTH)
    {
        myData = new myType[size];
        arrLength = size;

        for(unsigned int i = 0; i < size; i++)
            myData[i] = arr[i];

        return true;
    }
    else
    {
        cout << "Error, invalid size" << endl;
        return false;
    }
}

template <class myType>
bool dynamicMedians<myType>::generateData(const int size, const int limit)
{
    if(size >= MIN_LENGTH)
    {
        myData = new myType[size];
        arrLength = size;

        for(unsigned int i = 0; i < size; i++)
            myData[i] = rand()%limit;

        return true;
    }
    else
    {
        cout << "Error, invalid size" << endl;
        return false;
    }
}

template <class myType>
void dynamicMedians<myType>::showData() const
{
    cout << "Data:" << endl;
    cout << "-----" << endl;
    for(int i = 0; i < arrLength; i++)
        cout << myData[i] << " ";
    cout << endl << endl;
}

template <class myType>
void dynamicMedians<myType>::showMedians() const
{
    cout << "Dynamic Medians:" << endl;
    cout << "----------------" << endl;
     for(int i = 0; i < arrLength; i++)
        cout << mediansArr[i] << " ";
    cout << endl << endl;
}

template <class myType>
myType dynamicMedians<myType>::getDataItem(const unsigned int index) const
{
    return (myData[index]);
}

template <class myType>
myType dynamicMedians<myType>::getMediansItem(const unsigned int index) const
{
    return (mediansArr[index]);
}

template <class myType>
void dynamicMedians<myType>::findMedians()
{
    minHeap<myType> minH;
    maxHeap<myType> maxH;

    int currMedian = -1;

    mediansArr = new myType[arrLength];

    for(int i = 0; i < arrLength; i++)
    {

        if(minH.getCount() == maxH.getCount())
        {
            if(myData[i] < currMedian)
            {
                maxH.insert(myData[i]);
                currMedian = maxH.peek();
            }
            else
            {
                minH.insert(myData[i]);
                currMedian = minH.peek();
            }
        }

        else if(maxH.getCount() > minH.getCount())
        {
            if(myData[i] < currMedian)
            {
                minH.insert(maxH.deleteMax());
                maxH.insert(myData[i]);
            }
            else
            {
                minH.insert(myData[i]);
            }

            currMedian = (minH.peek() + maxH.peek())/2;
    
        }

        else if(minH.getCount() > maxH.getCount())
        {
            if(myData[i] < currMedian)
            {
                maxH.insert(myData[i]);
            }
            else
            {
                maxH.insert(minH.deleteMin());
                minH.insert(myData[i]);
            }

            currMedian = (minH.peek() + maxH.peek())/2;
        }

        mediansArr[i] = currMedian;

    }
}




#endif 