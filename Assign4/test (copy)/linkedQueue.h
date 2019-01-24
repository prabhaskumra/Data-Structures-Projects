//
//  linkedQueue.h
//  
//
//  Created by Prabhas Kumra on 9/18/18.
//

#ifndef linkedQueue_h
#define linkedQueue_h

#include <iostream>
#include <stdio.h>
#define SIZE 32000

using namespace std;

template <class myType>
struct queueNode
{
    myType dataSet[SIZE];
    int front, back;
    queueNode<myType> *link;
};


template <class myType>
class linkedQueue
{
public:
    linkedQueue();
    ~linkedQueue();
    bool isEmptyQueue() const;
    void initializeQueue();
    void addItem(const myType& newItem);
    myType front() const;
    myType back() const;
    void deleteItem();
    int queueCount();
    void printQueue();
    
private:
    queueNode<myType> * queueFront;
    queueNode<myType> * queueRear;
    int count;
};



template <class myType>
linkedQueue<myType>::linkedQueue()
{
    queueFront = NULL;
    queueRear = NULL;
    count = 0;

    initializeQueue();
}


template <class myType>
linkedQueue<myType>::~linkedQueue()
{

    if(!isEmptyQueue())
    {
     if(queueFront == queueRear)
        {
            delete queueFront;
            queueFront = queueRear = NULL;
        }
     else
        {
             queueNode<myType> * temp = queueFront;

             while(queueFront->link != NULL) 
              {
              temp = queueFront;
              queueFront = queueFront->link;
              delete temp;
        
            }
         }
    }
    else    
        return;


}

template <class myType>
bool linkedQueue<myType>::isEmptyQueue() const
{
    if(count != 0)
        return false;

    else
        return true;
}
template <class myType>
void linkedQueue<myType>::initializeQueue()
{
    queueFront = new queueNode<myType>;
    queueRear = queueFront;
    count = 0;
    queueFront->front = 0;
    queueRear->back = 0;
    queueFront->link = NULL;
}
template <class myType>
void linkedQueue<myType>::addItem(const myType& newItem)
{
    if((queueRear->front == 0 && queueRear->back == SIZE -1) || (queueRear->front - queueRear->back == 1))
    {
        queueNode<myType> * temp = new queueNode<myType>;
        queueRear->link = temp;
        queueRear = temp;
        queueRear->link = NULL;

        queueRear->front = 0;
        queueRear->back = 0;

        queueRear->dataSet[queueRear->back] = newItem;
      }

    else if(count == 0)
        {
            queueRear->dataSet[queueRear->back] = newItem;
        }

    else
        {
            if(queueRear->back == SIZE -1)
                queueRear->back = 0;

            else
                queueRear->back++;

            queueRear->dataSet[queueRear->back] = newItem;

        }

    count++;

}
template <class myType>

myType linkedQueue<myType>::front() const
{
    return queueFront->dataSet[queueFront->front];
}


template <class myType>
myType linkedQueue<myType>::back() const
{
    return queueRear->dataSet[queueRear->back];
}


template <class myType>
void linkedQueue<myType>::deleteItem()
{
    if(count == 0)
        {
            return;
        }


    else
    {
        if(queueFront->front == queueFront->back)
        {
            queueNode<myType> * temp = queueFront->link;
            delete[] queueFront;
            queueFront = temp;
            temp = NULL;
        }

        else
        {
            if(queueFront->front == SIZE-1)
            {
                queueFront->front = 0;
            }

            else
                queueFront->front++;
        }

        count--;
    }
}
template <class myType>
int linkedQueue<myType>::queueCount()
{
    return count;
}
template <class myType>
void linkedQueue<myType>::printQueue()
{
    queueNode<myType> * temp = queueFront;
    int num;
    num = temp->front;

    do
    {
        num = temp->front;
        while(num != queueFront->back)
            {
                cout  <<temp->dataSet[num] << " ";

                if(num == SIZE -1)
                    num = 0;
                else
                    num++;
            }
        cout <<temp->dataSet[num] << " ";

        temp = temp->link;
    }while(temp != NULL);

}



#endif /* linkedQueue_h */
