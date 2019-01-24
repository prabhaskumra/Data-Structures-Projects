// Prabhas Kumra
// CS 302-1004
// Assignment #8


#ifndef minHeap_h
#define minHeap_h

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

template <class myType>
class minHeap
{
private:
    unsigned int count;
    unsigned int heapSize;
    myType * myHeap;

    void reheapUp(unsigned int);
    void reheapDown(unsigned int);
    void heapify();
    void resize();

public:
    minHeap(unsigned int = 1000);
    ~minHeap();
    unsigned int getCount() const;
    void insert(const myType key);
    myType deleteMin();
    myType peek() const;
    bool isEmpty() const;
    void printHeap() const;
    void makeRandHeap1(const unsigned int, const unsigned int);
    void makeRandHeap2(const unsigned int, const unsigned int);
};


template <class myType>
minHeap<myType>::minHeap(unsigned int size)
{
    heapSize = size;

    myHeap = new myType[heapSize];

    //heapSize = size;
    count = 0;


}
template <class myType>
minHeap<myType>::~minHeap()
{
    delete[] myHeap;
}

template <class myType>
unsigned int minHeap<myType>::getCount() const
{
    return count;
}

template <class myType>
void minHeap<myType>::insert(const myType key)
{

    if( (count + 1) >= heapSize)
        resize();

    if(count == 0)
        myHeap[1] = key;
    else
        myHeap[count + 1] = key;
    
    reheapUp(count+1);

    count++;
}

template <class myType>
myType minHeap<myType>::deleteMin()
{
    if(isEmpty())
    {
        cout << "Error, min heap empty" << endl;
        return{};
    }

    myType top = peek();

    myHeap[1] = myHeap[count];
   // myHeap[count] = NULL;
    count--;

    reheapDown(1);

   

    return top;
}

template <class myType>
myType minHeap<myType>::peek() const
{
    return (myHeap[1]);
}

template <class myType>
bool minHeap<myType>::isEmpty() const
{
    if(count == 0)
        return true;
    else
        return false;
}

template <class myType>
void minHeap<myType>::printHeap() const
{
    for(unsigned int i = 1; i < count+1; i++)
    {
        cout << myHeap[i] << endl;

        if(i == 1)
            cout << endl;
        else if((ceil(log2(i+1)) == floor(log2(i+1))))
            cout << endl;
    }
}

template <class myType>
void minHeap<myType>::makeRandHeap1(const unsigned int size, const unsigned int limit)
{
    srand(73);

    //num%limit;
    //heapSize = size;

    for(unsigned int i = 0; i < size; i++)
        insert(rand()%limit);
}

template <class myType>
void minHeap<myType>::makeRandHeap2(const unsigned int size, const unsigned int limit)
{
    srand(73);
    

    for(unsigned int i = 1; i <= size; i++)
    {
        myHeap[i] = (rand()%limit);

        count++;
    }

    heapify();

}
 //********************
template <class myType>
void minHeap<myType>::reheapUp(unsigned int num)
{
    unsigned int temp;

    if(num > 1)
    {
        temp = num / 2;
        if(myHeap[num] < myHeap[temp])
        {
            swap(myHeap[num], myHeap[temp]);
            reheapUp(temp);
        }
    }
}

template <class myType>
void minHeap<myType>::reheapDown(unsigned int num)
{

    unsigned int left = num * 2;
    unsigned int right = (num * 2) + 1;

    if(num < count)
    {
        if(right > count)
        {
            if(left <= count)
            {
                if(myHeap[num] >= myHeap[left])
                {
                  swap(myHeap[num], myHeap[left]);
                  reheapDown(left);
                }
            }
        }
        else if(myHeap[right] < myHeap[left])
        {
            if(myHeap[num] > myHeap[right])
            {
                swap(myHeap[num], myHeap[right]);
                reheapDown(right);
            }
        }
        else if(myHeap[right] >= myHeap[left])
        {
            if(myHeap[num] > myHeap[left])
            {
                swap(myHeap[num], myHeap[left]);
                reheapDown(left);
            }
        }

    }



}

template <class myType>
void minHeap<myType>::heapify()
{
    //cout << count << endl;
    

    for(unsigned int i = (count/2); i >= 1; i--)
    {
        //cout << "i" << i << endl;
        reheapDown(i);
    }
}

template <class myType>
void minHeap<myType>::resize()
{
    unsigned int oldSize = heapSize;
    heapSize = 2 * heapSize;

    myType * oldHeap = myHeap;
    myHeap = NULL;
    myHeap = new myType[heapSize];

    for(unsigned int i = 0; i < oldSize; i++)
        myHeap[i] = oldHeap[i];

    delete[] oldHeap;
    oldHeap = NULL;
}



#endif 