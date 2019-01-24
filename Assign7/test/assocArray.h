// Prabhas Kumra
// Assignment #7
// CS 302 - 1004


#ifndef assocArray_h
#define assocArary_h

#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>

using namespace std;



template <class myType>
class assocArray
{
private:
    unsigned int hashSize;
    unsigned int reSizeCount;
    unsigned int collisionCount;
    unsigned int entries;
    unsigned int currIteratorIndex;
    string * hashKeys;
    myType * hashValues;
    static constexpr double loadFactor = 0.65;
    static constexpr unsigned int initialHashSize = 1013;
    static constexpr unsigned int hashSizesCount = 13;
    static constexpr unsigned int hashSizes[13] = {9973, 30011, 60013, 120017, 240089,
                                                    480043, 960017, 1920013, 3840037,
                                                    7680103, 15360161, 30720299, 61440629};
    
    unsigned int hash(const string str) const;
    void rehash();

public:
    assocArray();
    ~assocArray();
    myType& operator[](const string str);
    string begin();
    string end();
    string next();
    bool exists(const string str) const ;
    bool erase(const string str);
    void printHash() const;
    void showStats() const;
};

template <class myType>
constexpr unsigned int assocArray<myType>::hashSizes[];

template <class myType>
assocArray<myType>::assocArray()
{
    hashSize = initialHashSize;
    collisionCount = 0;
    entries = 0;
    reSizeCount = 0;
    currIteratorIndex = 0;

    hashKeys = new string[hashSize];
    hashValues = new myType[hashSize];

    for(unsigned int i = 0; i < hashSize; i++)
        hashKeys[i] = "";
}

template <class myType>
assocArray<myType>::~assocArray()
{
    delete[] hashKeys;
    delete[] hashValues;

}

template <class myType>
unsigned int assocArray<myType>::hash(const string str) const
{
    unsigned int hashVal = 0;

    //for(unsigned int i = 0; i < str.length(); i++)
   // {
     //   hashVal = (str[i]) + (hashVal << 6) + (hashVal << 16) - hashVal;
   // }

    unsigned  sum = 0;
    string st ="";

	for(unsigned int i = 0; i < str.length(); i++)
    {
        //st = ss[i];
        sum += str[i];
    }
    hashVal = sum;

    hashVal = hashVal % hashSize;

    return hashVal;
}

template <class myType>
void assocArray<myType>::rehash()
{
    unsigned int oldSize = hashSize;
    
    hashSize = hashSizes[reSizeCount];

    string * oldhashKeys = hashKeys;
    myType * oldhashValues = hashValues;

    hashKeys = NULL;
    hashValues = NULL;

    hashKeys = new string[hashSize];
    hashValues = new myType[hashSize];


    for(unsigned int i = 0; i < oldSize; i++)
    {
            (*this)[oldhashKeys[i]] = oldhashValues[i];
    }

    delete[] oldhashKeys;
    delete[] oldhashValues;

    oldhashKeys = NULL;
    oldhashValues = NULL;

    reSizeCount++;

}


template <class myType>
myType& assocArray<myType>::operator[](const string str)
{
    
    if((double(entries)/double(hashSize)) > loadFactor)
        rehash();

    //unsigned int index = hash(str);  
    unsigned int idx = hash(str);
    unsigned int index = idx;   
     
     
    for (unsigned int i = 0; i < hashSize; i++) 
    {
        //index = (idx + i*i) % hashSize;

        if (hashKeys[index] == str)
            return hashValues[index];

        else if(hashKeys[index] == "")
            break;

        index = (idx + i*i) % hashSize;
    }

   index = idx; 

    for (unsigned int i = 0; i < hashSize; i++) 
    {
        index = (idx + i*i) % hashSize;

        if(hashKeys[index] == "" || hashKeys[index] == "*")
        {
            hashKeys[index] = str;
            entries++;
            return hashValues[index];
        }
        else
        {
            collisionCount++;
            //index = (idx + i*i) % hashSize;
        }

    }
}

template <class myType>
string assocArray<myType>::begin()
{
    string str;

    for (unsigned int i = 0; i < hashSize; i++)
    {
        if(hashKeys[i] != "" && hashKeys[i] != "*")
        {
            currIteratorIndex = i;
            str = hashKeys[i];
            return str;
        }
    }
    return "";

}

template <class myType>
string assocArray<myType>::end()
{
    return "";
}

template <class myType>
string assocArray<myType>::next()
{       
    string str;
    
    for (unsigned int i = currIteratorIndex + 1; i < hashSize; i++)
    {
        if(hashKeys[i] != "" && hashKeys[i] != "*")
        {
            currIteratorIndex = i;
            str = hashKeys[i];
            return str;
        }
    }
    return "";
}

template <class myType>
bool assocArray<myType>::exists(const string str) const
{

    //unsigned int index = hash(str); 
    unsigned int idx = hash(str);
    unsigned int index = idx;


    for (unsigned int i = 0; i < hashSize; i++) 
    {
        index = (idx + i*i) % hashSize;

        if (hashKeys[index] == str)
            return true;
        
        else if(hashKeys[index] == "")
            return false;

        //index = (idx + i*i) % hashSize;
    }


    return false;
}

template <class myType>
bool assocArray<myType>::erase(const string str)
{
    //unsigned int index = hash(str);       

    unsigned int idx = hash(str);
    unsigned int index = idx;

    for (unsigned int i = 0; i < hashSize; i++) 
    {
        index = (idx + i*i) % hashSize;

        if (hashKeys[index] == str)
        {
            hashKeys[index] = "*";
            entries--;
            return true;
        }
        //index = (idx + i*i) % hashSize;
    }
    return false;
}

template <class myType>
void assocArray<myType>::printHash() const
{
    string curr;

     for(curr = begin(); curr != end(); curr = next() )
   {
       if(curr != "" &&  curr != "*")
        cout << curr << endl;
   }
}

template <class myType>
void assocArray<myType>::showStats() const
{

    cout << "Hash Stats" << endl;
    cout << "   Current Entries Count " << entries << endl;
    cout << "   Hash Size: " << hashSize << endl;
    cout << "   Hash Resize Operations: " << reSizeCount << endl;
    cout << "   Hash Collisions: " << collisionCount << endl;

}


#endif /* assocArray_h */
