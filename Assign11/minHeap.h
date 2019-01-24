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
    struct nodeType
    {
        int distance;
        myType value;
    };

private:
    unsigned int count;
    unsigned int heapSize;
    nodeType * myHeap;

    void reheapUp(unsigned int);
    void reheapDown(unsigned int);
    void heapify();
    void resize();

public:
    minHeap(unsigned int = 1000);
    ~minHeap();
    unsigned int getCount() const;
    void insert(const myType vertx, const int dist);
    myType deleteMin(int & num);
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

    myHeap = new nodeType[heapSize];

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
void minHeap<myType>::insert(const myType vertx, const int dist)
{

    if( (count + 1) >= heapSize)
        resize();

    if(count == 0)
    {
        myHeap[1].distance = dist;
        myHeap[1].value = vertx;
    }
        //myHeap[1] = vertx;
    else
    {
        myHeap[count+1].distance = dist;
        myHeap[count+1].value = vertx;
    }
        //myHeap[count + 1] = vertx;
    
    //reheapUp(count+1);

   

    reheapUp(count+1);
    count++;
}

template <class myType>
myType minHeap<myType>::deleteMin(int & num)
{
    if(isEmpty())
    {
        cout << "Error, min heap empty" << endl;
        return{};
    }

    myType top = myHeap[1].value; // peek();
    num = myHeap[1].distance;

    myHeap[1].distance = myHeap[count].distance;
    myHeap[1].value = myHeap[count].value;
   // myHeap[count] = NULL;
    count--;

    reheapDown(1);

   

    return top;
}

template <class myType>
myType minHeap<myType>::peek() const
{
    return (myHeap[1].distance);
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
        if(myHeap[num].distance < myHeap[temp].distance)
        {
            swap(myHeap[num].distance, myHeap[temp].distance);
            swap(myHeap[num].value, myHeap[temp].value);
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
                if(myHeap[num].distance >= myHeap[left].distance)
                {
                  swap(myHeap[num].distance, myHeap[left].distance);
                  swap(myHeap[num].value, myHeap[left].value);
                  reheapDown(left);
                }
            }
        }
        else if(myHeap[right].distance < myHeap[left].distance)
        {
            if(myHeap[num].distance > myHeap[right].distance)
            {
                swap(myHeap[num].distance, myHeap[right].distance);
                swap(myHeap[num].value, myHeap[right].value);
                reheapDown(right);
            }
        }
        else if(myHeap[right].distance >= myHeap[left].distance)
        {
            if(myHeap[num].distance > myHeap[left].distance)
            {
                swap(myHeap[num].distance, myHeap[left].distance);
                swap(myHeap[num].value, myHeap[left].value);
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

    nodeType * oldHeap = myHeap;
    myHeap = NULL;
    myHeap = new nodeType[heapSize];

    for(unsigned int i = 0; i < oldSize; i++)
        myHeap[i] = oldHeap[i];

    delete[] oldHeap;
    oldHeap = NULL;
}



#endif 