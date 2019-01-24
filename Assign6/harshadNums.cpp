// Prabhas Kumra
// Assignment #6
// CS 302 - 1004

#include <iostream>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <mutex>

using namespace std;

static      const unsigned long long    MIN_THREAD_COUNT = 1;
static      const unsigned long long    MAX_THREAD_COUNT = 64;
static      const unsigned long long    MIN_LIMIT = 10;
static      const unsigned long long    MAX_LIMIT = 10000000000;
static      const unsigned long long    HARSHAD_STEP = 10000;

mutex myMutex;
unsigned long long limitValue = 0;
int count  = 0;
int tCount = 0;

bool getArguments(int argc, char * argv[], unsigned long long & threadCount);

void digitSum();

void incCounter();

int inctCount();




int main(int argc, char * argv[])
{ 
    string bars;
	bars.append(60, '-');

    unsigned long long threadCount = 0;
    
    //int count = 0;
    unsigned long hwthd = thread::hardware_concurrency();


    if (!getArguments(argc, argv, threadCount))
         exit(1);

    auto t1 = chrono::high_resolution_clock::now();

    cout << bars << endl;
    cout << "CS 302 - Assignment #6" << endl << endl;
    cout << "Hardware Cores: " << hwthd <<  endl;
    
    cout << "Thread Count: " << threadCount << endl;
    cout << "Number Limit: " << limitValue << endl << endl;

    thread * thd = new thread[threadCount];

    for(unsigned int i = 0; i < threadCount; i++)
    {
        thd[i] = thread(digitSum);
    }

    for(unsigned int i = 0; i < threadCount; i++)
    {
        thd[i].join();
    }

    cout << "Results:" << endl;
    cout << "   Count of Harshad numbers between 1 and "<< limitValue 
            << " is " << count << endl << endl;
    
    auto t2 = chrono::high_resolution_clock::now();


    cout << "Thread took: " 
            << std::chrono::duration_cast<std::chrono::milliseconds> 
                (t2-t1).count() << " milliseconds"<< endl; 

    delete [] thd;

    return 0;
}

bool getArguments(int argc, char * argv[], unsigned long long & threadCount)
{


    stringstream	ss, sr;

    if (argc == 1) {
		cout << "Usage: ./harshadNums -t <threadCount> -l <limitValue>" << endl;
		exit(1);
	}


    if (argc != 5) {
		cout << "Error, invalid command line options." << endl;
		exit(1);
	}

    if (string(argv[1]) != "-t"){
		cout << "Error, invalid command line options." << endl;
		exit(1);
	}

    if (string(argv[3]) != "-l"){
		cout << "Error, invalid command line options." << endl;
		exit(1);
	}

    if (string(argv[2]) != "") {
		ss << argv[2];
		ss >> threadCount;
	}


     if (string(argv[4]) != "") {
		sr << argv[4];
		sr >> limitValue;
	}
   
    if(threadCount < MIN_THREAD_COUNT || threadCount > MAX_THREAD_COUNT)
        {
            cout << "invalid thread count" << endl;
            return false;
        }
    if(limitValue < MIN_LIMIT || limitValue > MAX_LIMIT)
        {
            cout << "invalid number limit ("<< limitValue <<")" << endl;
            return false;
        }
    
    return true;
    
}

void digitSum()
{

    while(true)
    {

    int num = inctCount();

    
    int lower = num * 10000 + 1;
    int upper = lower + 10000;

    if(upper > limitValue)
        upper = limitValue;

    if(lower > limitValue)
        return;

    for(unsigned int k = lower; k < upper + 1; k++)
    {
        //int sum = digitSum(i);
    string ss = to_string(k);
    int sum = 0;
    string str ="";

    for( unsigned int i = 0; i < ss.length(); i++)
    {
        str = ss[i];
        int j = stoi(str);
        sum = sum +  j;
    }

       if(k % sum == 0)
        incCounter();

    }

    }
}

void incCounter()
{
    lock_guard<mutex> guard(myMutex);
    count++;
    
}

int inctCount()
{
    lock_guard<mutex> guard(myMutex);
    int num1 = tCount;
    tCount++;

    return num1;
}
