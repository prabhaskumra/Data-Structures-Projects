// Prabhas Kumra
// CS 302 - 1004
// Assignment #8


#include <iostream>
#include <string>
#include "mazeGenerator.h"
#include <ctype.h>
#include <sstream>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

using namespace std;



mazeGenerator::mazeGenerator()
{
    rows = 0;
    cols = 0;
}

mazeGenerator::~mazeGenerator()
{
    int num = ((rows -1) * cols) + ((cols -1) * rows);
    
    for(int i = 0; i<num; i++)
    {
        delete [] walls[i];
    }
    delete[] walls;
    
    
}
void mazeGenerator::getSize(int & row, int & col) const
{
    row = rows;
    col = cols; 
}
bool mazeGenerator::setSize(int row, int col)
{

    if(row < MIN_ROWS || row > MAX_ROWS)
        return false;

    if(col < MIN_COLS || col > MAX_COLS)
        return false;

    rows = row;
    cols = col;

    int num = ((row -1) * col) + ((col -1) * row);

    walls = new int * [num];
    
    for(int i = 0; i < num; i++)
        walls[i] = new int[2];

    int count = 0, count2 = 0, count3 = 1;



    for(int i = 0; i <row; i++)
    {
        for(int j = 0; j < (col-1); j++)
        {
            walls[count][0] = count2;
            walls[count][1] = count3;
            count++;
            count2++;
            count3++;
        }
        count2++;
        count3++;
    }

    count2 = 0;
    count3 = col;

     for(int i = 0; i < col; i++)
    {
         for(int j = 0; j < (row-1) ; j++)
        {
            walls[count][0] = count2;
            walls[count][1] = count3;
            count++;
            count2++;
            count3++;
        }

    }

    return true;

}
void mazeGenerator::generate()
{

    disjointSets sets(rows*cols);

    int sz = ((rows -1) * cols) + ((cols -1) * rows);

    randomize();

     for (int i=sz-1; i>=0; i--) {
        
        if(sets.setFind(walls[i][0]) != sets.setFind(walls[i][1]) )
        {
            sets.setUnion(walls[i][0],walls[i][1] );
            walls[i][1] = -1;
            walls[i][0] = -1;
        }
        
    }

}

bool mazeGenerator::printMazeData(const string fname) const
{
    ifstream inFile;
    ofstream outFile;

     outFile.open(fname);

    if(inFile.fail())
    {
        cout << "Error, unable to output file" << endl;
                return false;
    }
    else
    {
        int sz = ((rows -1) * cols) + ((cols -1) * rows);

        outFile << "ROWS " << rows << " COLS " << cols << endl;

        for (int i=sz-1; i>=0; i--)
        {
            if(walls[i][0] != -1 && walls[i][1] != -1)
                outFile << "WALL " << walls[i][0] << " " << walls[i][1] << endl;
        }
    }
            

    return true;
}
void mazeGenerator::printMazeText() const
{

    int sz = ((rows -1) * cols) + ((cols -1) * rows);

    bool ver[(cols-1)*rows];
    bool hori[(rows-1)*cols];

    for(int i = 0; i < (cols-1)* rows; i++)
        ver[i] = false;

    for(int i = 0; i < (rows-1)* cols; i++)
        hori[i] = false;


    int num;

     for (int i=sz-1; i>0; i--)
        {
            if(walls[i][0] != -1 && walls[i][1] != -1)
                {
                    if(walls[i][0] == (walls[i][1] - 1))
                        {
                            num = walls[i][0] - (walls[i][0]/(cols));
                            ver[num] = true;
                        }
                    else
                        {
                            hori[walls[i][0]] = true;
                        }
                }
        }

  
    int count = 0, count2 = 0;


    cout << "+  +";
    for(int i = 0; i < cols-1; i++)
        cout << "--+";
    cout << endl;

   for(int i = 0; i < (rows); i++)
   {
       cout << "|  ";

       for(int j = 0; j < (cols-1); j++)
       {
            if(ver[count] == true)
                cout << "|";
            else
                cout << " ";
            
            cout << "  ";
            count++;
       }

       cout <<"|" <<  endl;

       

        if(i != (rows-1))
       { 
           cout << "+";

            for(int j = 0; j < (cols); j++)
            {
                if(hori[count2] == true)
                    cout << "--";
                else
                    cout << "  ";
                cout << "+";

                count2++;
            }

            cout << endl;
       }
   }
     
    for(int i = 0; i < cols-1; i++)
        cout << "+--";

    cout << "+  +";
    cout << endl;
       
       
}

bool mazeGenerator::getArguments(int argc, char * argv[], int & row, int & col, string & fname, bool & doPrint)
{

    stringstream rw;
    stringstream cl;
    ifstream inFile;
    ofstream outFile;
    string temp;

    bool rowerr = false;
    bool colerr = false;
    bool printerr = false;
    bool fileerr = false;

   
    if(argc < 7 || argc > 8)
    {
        cout << "./maze -c <columns> -r <rows> -o <output file> [-p]" << endl;
        return false;
    }

    if(argc == 7)
        {
            doPrint = false;
            printerr = true;
        }
//////////////////////////////////////////////////////////////

    if( string(argv[1]) == "-r" )
    {
        rw << string(argv[2]);
        rw >> temp;

        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid rows value" << endl;
                return false;
            }
        }

        row = stoi(temp);
     
        rowerr = true;
    }

    else if( string(argv[1]) == "-c" )
    {
        cl << string(argv[2]);
        cl >> temp;

        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid columns value" << endl;
                return false;
            }
        }

        col = stoi(temp);

        colerr = true;

    }


    else if( string(argv[1]) == "-o" )
    {
        outFile.open(argv[2]);

        if(inFile.fail())
        {
            cout << "Error, unable to output file" << endl;
            return false;
        }
            else
            fname = argv[2];

        fileerr = true;
    }

    else if( string(argv[1]) == "-p" )
        {
            doPrint = true;
            printerr = true;
        }

///////////////////////////////////////////////////////////////////

    if( string(argv[2]) == "-r" )
    {
        rw << string(argv[3]);
        rw >> temp;

        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid rows value" << endl;
                return false;
            }
        }
        row = stoi(temp);
        rowerr = true;
    }

    else if( string(argv[2]) == "-c" )
    {
        cl << string(argv[3]);
        cl >> temp;


         for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid columns value" << endl;
                return false;
            }
        }

        col = stoi(temp);
        colerr = true;

    }


    else if( string(argv[2]) == "-o" )
    {
        outFile.open(argv[3]);

        if(inFile.fail())
        {
            cout << "Error, unable to output file" << endl;
            return false;
        }
            else
            fname = argv[3];

        fileerr = true;
    }

    else if( string(argv[2]) == "-p" )
        {
            doPrint = true;
            printerr = true;
        }

///////////////////////////////////////////////////////////////////


    if( string(argv[3]) == "-r" )
    {
        rw << string(argv[4]);
        rw >> temp;

        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid rows value" << endl;
                return false;
            }
        }

        row = stoi(temp);
        rowerr = true;
    }

    else if( string(argv[3]) == "-c" )
    {
        cl << string(argv[4]);
        cl >> temp;


        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid columns value" << endl;
                return false;
            }
        }

        col = stoi(temp);
        colerr = true;
    }


    else if( string(argv[3]) == "-o" )
    {
        outFile.open(argv[4]);

        if(inFile.fail())
        {
            cout << "Error, unable to output file" << endl;
            return false;
        }
            else
            fname = argv[4];

        fileerr = true;
    }

    else if( string(argv[3]) == "-p" )
        {
            doPrint = true;
            printerr = true;
        }

///////////////////////////////////////////////////////////////////

 if( string(argv[4]) == "-r" )
    {
        rw << string(argv[5]);
        rw >> temp;

         for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid rows value" << endl;
                return false;
            }
        }

        row = stoi(temp);
        rowerr = true;
    }

    else if( string(argv[4]) == "-c" )
    {
        cl << string(argv[5]);
        cl >> temp;


        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid columns value" << endl;
                return false;
            }
        }

        col = stoi(temp);
        colerr = true;
    }


    else if( string(argv[4]) == "-o" )
    {
        outFile.open(argv[5]);

        if(inFile.fail())
        {
            cout << "Error, unable to output file" << endl;
            return false;
        }
            else
            fname = argv[5];

        fileerr = true;
    }


    else if( string(argv[4]) == "-p" )
        {
            doPrint = true;
            printerr = true;
        }

///////////////////////////////////////////////////////////////////

     if( string(argv[5]) == "-r" )
    {
        rw << string(argv[6]);
        rw >> temp;

        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid rows value" << endl;
                return false;
            }
        }

        row = stoi(temp);
        rowerr = true;

    }

    else if( string(argv[5]) == "-c" )
    {
        cl << string(argv[6]);
        cl >> temp;

        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid columns value" << endl;
                return false;
            }
        }
        
        col = stoi(temp);
        colerr = true;
    }


    else if( string(argv[5]) == "-o" )
    {
        outFile.open(argv[6]);

        if(inFile.fail())
        {
            cout << "Error, unable to output file" << endl;
            return false;
        }
            else
            fname = argv[6];

        fileerr = true;
    }

     else if( string(argv[5]) == "-p" )
        {
            doPrint = true;
            printerr = true;
        }

///////////////////////////////////////////////////////////////////
        
    if( string(argv[6]) == "-r" )
    {
        rw << string(argv[7]);
        rw >> temp;

        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid rows value" << endl;
                return false;
            }
        }

        row = stoi(temp);
        rowerr = true;
    }

    else if( string(argv[6]) == "-c" )
    {
        cl << string(argv[7]);
        cl >> temp;

        for(int i = 0; i < temp.length(); i++)
        {
            if(!isdigit(temp[i]))
            {
                cout << "Invalid columns value" << endl;
                return false;
            }
        }
        col = stoi(temp);
        colerr = true;
    }


    else if( string(argv[6]) == "-o" )
    {
        outFile.open(argv[7]);

        if(inFile.fail())
        {
            cout << "Error, unable to output file" << endl;
            return false;
        }
            else
            fname = argv[7];

        fileerr = true;
    }

    else if( string(argv[6]) == "-p" )
        {
            doPrint = true;
            printerr = true;
        }

///////////////////////////////////////////////////////////////////

    if(argc == 8)
        if( string(argv[7]) == "-p" )
        {
            doPrint = true;
            printerr = true;
        }

        

    if(rowerr == false)
    {
        cout << "Error, invalid rows specifier" << endl;
        return false;
    }

    if(colerr == false)
    {
        cout << "Error, invalid column specifier" << endl;
        return false;
    }

     if(fileerr == false)
    {
        cout << "Error, invalid file specifier" << endl;
        return false;
    }

     if(printerr == false)
    {
        cout << "Error, invalid print specifier" << endl;
        return false;
    }

    return true;

}

void mazeGenerator::randomize()
{
    int sz = ((rows -1) * cols) + ((cols -1) * rows);
    int idx;

    for (int i=sz-1; i>0; i--) 
    {
        idx = rand() % i+1;

        swap(walls[idx][0], walls[i][0]);
        swap(walls[idx][1], walls[i][1]);
    }
}
