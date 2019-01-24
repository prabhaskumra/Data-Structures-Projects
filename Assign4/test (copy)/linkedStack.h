//
//  linkedStack.h
//  
//
//  Created by Prabhas Kumra on 9/18/18.
//

#ifndef linkedStack_h
#define linkedStack_h

#include <iostream>
#include <stdio.h>
#define SIZE 32000

using namespace std;

template <class myType>
struct nodeType {
    myType dataSet[SIZE];
    int top;
    nodeType<myType> *link;
};

template <class myType>
class linkedStack
{
public:
    linkedStack();
    ~linkedStack();
    bool isEmptyStack() const;
    void initializeStack();
    int stackCount();
    void push(const myType& newItem);
    myType top() const;
    void pop();
    
private:
    nodeType<myType> * stackTop;
    int count;
};

template <class myType>
linkedStack<myType>::linkedStack()
{
    count = 0;
    stackTop = NULL;

    initializeStack();
}


template <class myType>
linkedStack<myType>::~linkedStack()
{

    
   if(!isEmptyStack())
    {
     if(stackTop->link == NULL)
      {
          delete stackTop;
          stackTop = NULL;
      }

      else
      {
          nodeType<myType> * temp = stackTop;

             while(stackTop->link != NULL) 
         {
                temp = stackTop;
                stackTop = stackTop->link;
                delete temp;
         } 
      }
    }
    else 
        return;


}


template <class myType>
bool linkedStack<myType>::isEmptyStack() const
{
    if(count == 0)
        return true;

    else    
        return false;
}


template <class myType>
void linkedStack<myType>::initializeStack()
{
    stackTop = new nodeType<myType>;
    stackTop->link = NULL;

    stackTop->top = 0;
}


template <class myType>
int linkedStack<myType>::stackCount()
{
    return count;
}
template <class myType>
void linkedStack<myType>::push(const myType& newItem)
{
    if(stackTop->top == SIZE -1)
        {
            nodeType<myType> * temp = new nodeType<myType>;
            temp->link = stackTop;
            stackTop = temp;

            stackTop->top = 0;
            stackTop->dataSet[stackTop->top] = newItem;
        }

    else if(count == 0)
    {
        stackTop->dataSet[stackTop->top] = newItem;
    }

    else
    {
        stackTop->top++;
        stackTop->dataSet[stackTop->top] = newItem;
    }

    count++;
}
template <class myType>
myType linkedStack<myType>::top() const
{
    return stackTop->dataSet[stackTop->top];
}
template <class myType>
void linkedStack<myType>::pop()
{
    if(count == 0)
    {
        return;
    }

    else
    {
        if(stackTop->top == 0)
        {
            nodeType<myType> * temp = stackTop->link;

            delete[] stackTop;
            stackTop = temp;
            temp = NULL;
        }

        else
            stackTop->top--;

        count--;
    }

    
}




#endif /* linkedStack_h */
