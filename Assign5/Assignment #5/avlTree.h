//  Prabhas Kumra
//  CS 302 - 1004
//  Assignment #5
//  avlTree.h
//  
//
//  Created by Prabhas Kumra on 9/25/18.
//

#ifndef avlTree_h
#define avlTree_h
#include "linkedQueue.h"
#include <string>
#include <iostream>
#include <stdio.h>

#include <algorithm>

using namespace std;

template <class myType>
struct nodeType {
    myType keyValue;
    int nodeHeight;
    nodeType<myType> *left;
    nodeType<myType> *right;
};

enum treeTraversalOptions {INORDER, PREORDER, 
                        POSTORDER, LEVELORDER, NONE};

template <class myType>
class avlTree
{
public:
    avlTree();
    ~avlTree();
    void destroyTree();
    int countNodes() const;
    int height() const;
    bool search(myType) const;
    void printTree(treeTraversalOptions num) const;
    void insert(myType num);
    void deleteNode(myType num);
    bool isPrefix(string st) const;
    
private:
    nodeType<myType> * root;
    void destroyTree(nodeType<myType> * nd );
    int countNodes(nodeType<myType> * nd) const;
    int height(nodeType<myType> * nd) const;
    nodeType<myType> * search(myType num, nodeType<myType> * nd) const;
    void printTree(nodeType<myType> * nd, treeTraversalOptions num) const;
    void printLevelOrder() const;
    nodeType<myType> * insert(myType num, nodeType<myType> * nd);
    nodeType<myType> * rightRotate(nodeType<myType> * nd);
    nodeType<myType> * leftRotate(nodeType<myType> * nd);
    int getBalance(nodeType<myType> * nd) const;
    nodeType<myType> * deleteNode(myType num, nodeType<myType> * nd);
    nodeType<myType> * minValueNode(nodeType<myType> * nd) const;
};

template <class myType>
avlTree<myType>::avlTree()
{
    root = NULL;

}
template <class myType>
avlTree<myType>::~avlTree()
{
    destroyTree();
}

template <class myType>
void avlTree<myType>::destroyTree()
{
    destroyTree(root);
}
template <class myType>
int avlTree<myType>::countNodes() const
{
    return countNodes(root);
}

template <class myType>
int avlTree<myType>::height() const
{
    return height(root);
}

template <class myType>
bool avlTree<myType>::search(myType num) const
{
    nodeType<myType> * value;
    value = search(num, root);

    if(value != NULL)
        return true;
    else
        return false;
    
}

template <class myType>
void avlTree<myType>::printTree(treeTraversalOptions num) const
{
    printTree(root, num);
}

template <class myType>
void avlTree<myType>::insert(myType num)
{
    bool value;
    value = search(num);

    if(value != true)
        root = insert(num, root);
    
}

template <class myType>
void avlTree<myType>::deleteNode(myType num)
{
    //nodeType<myType> * value;
    //value = deleteNode(num, root);

    bool value;
    value = search(num);

    if(value == true)
        root = deleteNode(num, root);

}

template <class myType>
bool avlTree<myType>::isPrefix(string str) const
{
    nodeType<myType> * curr = root;
    
        if(curr == NULL)
            return false;

        if(str == (curr->keyValue).substr(0,str.length()))
            return true;

        else if(str < curr->keyValue)
            {
                curr = curr->left;
                isPrefix(str);
            }
        else if(str > curr->keyValue)
            {
                curr = curr->right;
                isPrefix(str);
            }
}


////////////////////////////////////////////////////////////////
///// PRIVATE CLASS //////////////////////
///////////////////////////////////////////////////////////////


template <class myType>
void avlTree<myType>::destroyTree(nodeType<myType> * nd)
{
    if(nd != NULL)
    {
        destroyTree(nd->left);
        destroyTree(nd->right);
        delete nd;
    }
    
}

template <class myType>
int avlTree<myType>::countNodes(nodeType<myType> * nd) const
{
    int ld, rd;

    if(nd == NULL)
    {
        return 0;
    }
    else
    {
        ld = countNodes(nd->left);
        rd = countNodes(nd->right);

        int count = ld + rd + 1;
        return count;
    }
}

template <class myType>
int avlTree<myType>::height(nodeType<myType> * nd) const
{
    int ld, rd;

    if(nd == NULL)
    {
        return 0;
    }
        ld = height(nd->left);
        rd = height(nd->right);

        if(ld > rd)
            return (ld +1);
        else
            return (rd +1);
    
}

template <class myType>
nodeType<myType> * avlTree<myType>::search(myType num, nodeType<myType> * nd) const
{
    if(nd == NULL)
        return NULL;
    else
    {
        if(num == nd->keyValue)
            return nd;

        else if(num < nd->keyValue)
            {
                return search(num, nd->left);
            }
        else if(num > nd->keyValue)
            {
                return search(num, nd->right);
            }
    }

}

template <class myType>
void avlTree<myType>::printTree(nodeType<myType> * nd , treeTraversalOptions num) const
{
    if( num == INORDER)
    {
        if(nd != NULL)
        {
            printTree(nd->left, num);
            cout << " " << nd->keyValue;
            printTree(nd->right, num);
        }
    }
    else if (num == POSTORDER)
    {
        if(nd != NULL)
        {
            printTree(nd->left, num);
            printTree(nd->right, num);
            cout << " " << nd->keyValue;
        }
    }else if(num == PREORDER)
    {
        if(nd != NULL){
            cout << " " << nd->keyValue;
            printTree(nd->left, num);
            printTree(nd->right,num);
        }
    }else if(num == NONE)
    {

    }
    else if(num == LEVELORDER)
    {
        printLevelOrder();
    }

}

template <class myType>
void avlTree<myType>::printLevelOrder() const
{
    linkedQueue<nodeType <myType> * >  Q;
    nodeType<myType> * curr = root;

    while(true)
    {
        cout << " " << curr->keyValue;

        if(curr->left != NULL)
        Q.addItem(curr->left);

        if(curr->right != NULL)
        Q.addItem(curr->right);

        if(Q.isEmptyQueue())
        {
            break;
        }
                
        curr = Q.front();
        Q.deleteItem();
    }
}

template <class myType>
nodeType<myType> * avlTree<myType>::insert(myType num, nodeType<myType> * nd)
{
    if(nd == NULL)
    {
        nd = new nodeType<myType>;
        nd->keyValue = num;
        nd->left = NULL;
        nd->right = NULL;
    }
    else
    {
        if(num < nd->keyValue)
        {
            nd->left = insert(num, nd->left);
        }
        else
        {
            nd->right = insert(num, nd->right);
        }
    }

    int diff = getBalance(nd);
            
    if(diff > 1 && num < nd->left->keyValue)
    {
        return rightRotate(nd);
    }
    if(diff < -1 && num > nd->right->keyValue)
    {
        return leftRotate(nd);
    }
    if(diff > 1 && num > nd->left->keyValue)
    {
        nd->left = leftRotate(nd->left);
        return rightRotate(nd);
    }
    if(diff < -1 && num < nd->right->keyValue)
    {
        nd->right = rightRotate(nd->right);
        return leftRotate(nd);
    }

    return nd;
}


template <class myType>
nodeType<myType> * avlTree<myType>::rightRotate(nodeType<myType> * nd)
{
    
    nodeType<myType> * tmpLft = nd->left;
    nodeType<myType> * tmpRht = tmpLft->right;

    tmpLft->right = nd;
    nd->left = tmpRht;

    nd->nodeHeight = max(height(nd->left), height(nd->right)) +1;
    tmpLft->nodeHeight = max(height(tmpLft->left), height(tmpLft->right)) + 1;

    return tmpLft;
    
}

template <class myType>
nodeType<myType> * avlTree<myType>::leftRotate(nodeType<myType> * nd)
{
    nodeType<myType> * tmpRht = nd->right;
    nodeType<myType> * tmpLft = tmpRht->left;

    tmpRht->left = nd;
    nd->right = tmpLft;

    nd->nodeHeight = max(height(nd->left), height(nd->right)) + 1;
    tmpRht->nodeHeight = max(height(tmpRht->left), height(tmpRht->right)) + 1;

    return tmpRht;
    
}

template <class myType>
int avlTree<myType>::getBalance(nodeType<myType> * nd) const
{
    int lheight = height(nd->left);
    int rheight = height(nd->right);

    return (lheight - rheight);
    
}

template <class myType>
nodeType<myType> * avlTree<myType>::deleteNode(myType num, nodeType<myType> * nd)
{
    if(nd == NULL)
        return NULL;

    if(num < nd->keyValue)
    {
        nd->left = deleteNode(num, nd->left);
    }
    else if(num > nd-> keyValue)
    {
        nd->right = deleteNode(num , nd->right);
    }

    else
    {
        if(nd->left == NULL)
        {
            nd = nd->right;
        }
        else if(nd->right == NULL)
        {
            nd = nd->left;
        }


        else
        {
            nodeType<myType> * minVal = minValueNode(nd->right);
            nd->keyValue = minVal->keyValue;
            nd->right = deleteNode(minVal->keyValue, nd->right); 
        }
    }

    if(nd == NULL)
        return NULL;

   
   // cout << "Gettong there" << endl;

    int diff = getBalance(nd);
            
    if(diff > 1 && num < nd->left->keyValue)
    {
        return rightRotate(nd);
    }
    if(diff < -1 && num > nd->right->keyValue)
    {
        return leftRotate(nd);
    }
    if(diff > 1 && num > nd->left->keyValue)
    {
        nd->left = leftRotate(nd->left);
        return rightRotate(nd);
    }
    if(diff < -1 && num < nd->right->keyValue)
    {
        nd->right = rightRotate(nd->right);
        return leftRotate(nd);
    }
    
    return nd;
}

template <class myType>
nodeType<myType> * avlTree<myType>::minValueNode(nodeType<myType> * nd) const
{
    //if(nd == NULL)
     //   return NULL:
    
    if(nd->left == NULL)
        return nd;
    else
        return minValueNode(nd->left);
    
}



#endif /* avlTree_h */
