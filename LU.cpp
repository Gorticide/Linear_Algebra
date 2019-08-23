#include <iostream>
#include <string>
#include <vector>
#include "fraction.h"

using namespace std;

void showMatrix(int, int, vector<vector<Fraction> >);

int main(void)
{
    int rows, cols;
    string inputBuffer = "";
    vector<vector<Fraction> > matrix;
    vector<vector<Fraction> > lowertriangle;
    vector<vector<Fraction> > uppertriangle;
    vector<Fraction> buffer;
    Fraction negativeFrac(-1/1);
    Fraction multNumber2;

    int currentRow = 0, currentCol = 0;

    int size,row,column,ctr1,ctr2;

    std::cout << "ENTER THE SIZE OF THE MATRIX (size<10) \n";
    std::cin >> size;
    rows = size;
    cols = size;

  // We must manually create these vectors of Fractions
  // In the process I initialize uppertriangle and lowertriangle elements to 0
    for(int i = 0; i < rows; i++)
    {
        vector<Fraction> row;
        matrix.push_back(row);
        for(int j = 0; j < cols; j++)
        {
            cout << "Enter row " << i + 1 << ", column " << j + 1 << " : ";
            cin >> inputBuffer;
            Fraction fracBuffer(inputBuffer);
            matrix[i].push_back(fracBuffer);
        }
        cout << endl;
    }
    std::cout << "\nOriginal Matrix:\n";
    showMatrix(rows, cols, matrix);


// These seems redundant, but it is necessary when using STL <vector>
// of my own Fraction objects otherwise SEGMENTATION FAULT (core dump) when
// attemting to initialize.   These are NOT arrays!

// Once created, we can use array-like index accessing

    for(int i = 0; i < rows; i++)
    {
        vector<Fraction> row;
        uppertriangle.push_back(row);
        lowertriangle.push_back(row);

        for(int j = 0; j < cols; j++)
        {
            inputBuffer = "0 1";
            Fraction fracBuffer(inputBuffer);
            uppertriangle[i].push_back(fracBuffer);
            lowertriangle[i].push_back(fracBuffer);
        }
   }

    for(row = 0; row < size; row++)
        for(column = 0; column < size; column++)
            {
                if(row > column)  {    // initialise all elements of lower triangle
                                       // in upper triangular matrix as 0
                       uppertriangle[row][column] = 0;
                }
                if(row < column)   {   // initialise all elements of upper triangle
                                       // in lower triangular matix as 0
                      lowertriangle[row][column] = 0;
                }
                if(row == column)   { // initialise all diagonal elements
                                      // of lower triangular matrix as 1
                    lowertriangle[row][column] = 1;
                  }
            }
/*The algorithm used later is from the book Introduction to algorithms by Thomas Cormen.
For a better understaning one can read this text under chapter Matrix Operations. */
    for(ctr1 = 0; ctr1 < size; ctr1++)
    {
        uppertriangle[ctr1][ctr1] = matrix[ctr1][ctr1];
            for(ctr2 = ctr1+1; ctr2 < size; ctr2++)
            {
                uppertriangle[ctr1][ctr2] = matrix[ctr1][ctr2];
                lowertriangle[ctr2][ctr1] = matrix[ctr2][ctr1]/uppertriangle[ctr1][ctr1];
            }
             for(row=ctr1+1;row<size;row++)
                for(column=ctr1+1;column<size;column++)
                    matrix[row][column] = matrix[row][column] \
                     - lowertriangle[row][ctr1]*uppertriangle[ctr1][column];
    }
    std::cout << "UPPER TRIANGULAR MATRIX\n\n";
    showMatrix(size, size, uppertriangle);

    std::cout << "LOWER TRIANGULAR MATRIX\n\n";
    showMatrix(size, size, lowertriangle);
    //getchar();
}

void showMatrix(int rows, int cols, vector<vector<Fraction> > mat)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            cout << "\t" << mat[i][j];
        if (i != rows - 1) cout << "\n";
    }
    cout << endl << endl;
}
