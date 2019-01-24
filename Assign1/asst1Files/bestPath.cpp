#include "bestPath.h"
#include <iostream>
#include <iomanip>

using namespace std;


// this will initilize class variables
bestPath::bestPath()
{

}

// displays matrix in formatted manner
void bestPath::displayMatrix()
{
    cout << "Matrix:" << endl << "Order: " << matrixOrder << endl << endl;

    for(int j = 0; j<matrixOrder; j++){
        for(int k = 0; k < matrixOrder; k++){
            cout <<fixed <<right << setw(4) << matrix[j][k] <<" ";
        }
        cout << endl;
    }
    //cout << matrix[][] << endl;
}

// create matrix
bool bestPath::createMatrix(const int order)
{
    matrixOrder = order;

    if(order < MIN_ORDER || order > MAX_ORDER)
    {
        cout << "Error, invalid matrix order" << endl;
        return false;
    }
   
        matrix = new int* [matrixOrder];
        for(int i = 0; i<matrixOrder; i++)
            matrix[i] = new int[matrixOrder];

    // populating the array
        for(int j = 0; j<matrixOrder; j++)
            for(int k = 0; k < matrixOrder; k++)
                matrix[j][k] = rand()%LIMIT+1;

        return true;

}
// solve the matrix path using dynamic programming apptoach
int bestPath::bestPthDY()
{

     int ** matrix2 = new int* [matrixOrder];
    for(int i = 0; i<matrixOrder; i++)
        matrix2[i] = new int[matrixOrder];

    for(int j = 0; j<matrixOrder; j++)
        for(int k = 0; k < matrixOrder; k++)
            matrix2[j][k] = matrix[j][k];


    for(int i = 1; i < matrixOrder; i++)
    {
        for (int j = 0; j < matrixOrder; j++)
        {   

            if(j > 0 && j < matrixOrder -1)
                matrix2[i][j] += max(matrix2[i-1][j-1], matrix2[i-1][j+1]);

            else if(j==0)
                matrix2[i][j] += matrix2[i-1][j+1];

            else if(j==matrixOrder-1)
                matrix2[i][j] += matrix2[i-1][j-1];

        }
    }
 
    int sum = 0;
    for(int i = 0; i < matrixOrder; i++)
        sum = max(matrix2[matrixOrder-1][i], sum);
    

    for(int i = 0; i<matrixOrder; i++)
    {
     delete [] matrix2[i];   
    }
    delete[] matrix2;

    return sum;
}
// solve matrix using maximal sum path problem by calling the private recursive function
int bestPath::bestPthREC()
{
    int arr[matrixOrder];


        for(int c = 0; c < matrixOrder; c++)
            arr[c] = bestPthREC1(0, c); 

    int temp = 0;

    for(int i=0 ;i<matrixOrder; i++)
    {
        if(arr[i] > temp)
         temp = arr[i];
    }

    return temp;
}


// solve the path problem recursively
int bestPath::bestPthREC1(int r, int c)
{
    if(c < 0 || c >= matrixOrder)
        return 0;

    else if(r == matrixOrder - 1)
        return matrix[r][c];

    else 
    {
        int value = 0;

        value = (max ( (matrix[r][c] + bestPthREC1(r+1, c-1)) , (matrix[r][c] + bestPthREC1(r+1, c+1))) );
        
        return value;
    } 
    
}

//destructer
bestPath::~bestPath()
{
   for(int i = 0; i<matrixOrder; i++)
    {
     delete [] matrix[i];   
    }
    delete[] matrix;


    
}












