/* Leaving original matrix unchanged while making copies and transforming the copy,
   I have the option of displaying Row Space and Column Space of the Matrix
   after finding the nonzero rows of the final matrix in echelon form.
  */

#include <iostream>
#include <string>
#include <vector>
#include "fraction.h"

using namespace std;

void showMatrix(int, int, vector<vector<Fraction> >);
vector< vector<Fraction> > swap_rows(vector< vector<Fraction> >, int, int);
vector< vector<Fraction> > divide_row(Fraction, vector< vector<Fraction> >, int);
vector< vector<Fraction> > mRowAdd(Fraction, vector< vector<Fraction> >, int, int);
vector< vector<Fraction> > rref(vector< vector<Fraction> >, int, int);


void showMatrix(int rows, int cols, vector<vector<Fraction> > mat)
{
   printf("_________________________________________________________\n\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            cout << "\t" << mat[i][j];
        if (i != rows - 1) cout << "\n";
    }
  printf("\n_________________________________________________________\n\n");
}

vector< vector<Fraction> > swap_rows(vector< vector<Fraction> > M, int row1, int row2)  {

  vector< vector<Fraction> > T;
  string inputBuffer = "";

  // It is necessary when using STL <vector> of my own Fraction objects
  // otherwise SEGMENTATION FAULT (core dump) when attemting to initialize.
  // These are NOT arrays!

  // Once created, we can use array-like index accessing

      for(int j = 0; j < M.size(); j++)
      {
          vector<Fraction> row_vector;
          T.push_back(row_vector);

          for(int k = 0; k < M[j].size(); k++)
          {
            inputBuffer = "0 1";
            Fraction fracBuffer(inputBuffer);
            T[j].push_back(fracBuffer);
            T[j][k] = M[j][k];
          }
     }

     cout << "\nswapping row " << row1 + 1 << " with row " << row2 + 1 << "\n";
      // SWAP ( T[row1][i], T[row2][i] )
     for (int i = 0; i < T[row1].size(); i++)  {
       Fraction temp = T[row1][i];
       T[row1][i] = T[row2][i];
       T[row2][i] = temp;
     }

    return T;
}



vector< vector<Fraction> > divide_row(Fraction f, vector< vector<Fraction> > M, int row)  {

  if (f.getNum() == 0)  {
    std::cout << "Prevented division by zero\n";
    return M;
  }

  vector< vector<Fraction> > T;
  string inputBuffer = "";

  // It is necessary when using STL <vector> of my own Fraction objects
  // otherwise SEGMENTATION FAULT (core dump) when attemting to initialize.
  // These are NOT arrays!

  // Once created, we can use array-like index accessing

      for(int j = 0; j < M.size(); j++)
      {
          vector<Fraction> row_vector;
          T.push_back(row_vector);

          for(int k = 0; k < M[j].size(); k++)
          {
            inputBuffer = "0 1";
            Fraction fracBuffer(inputBuffer);
            T[j].push_back(fracBuffer);
            T[j][k] = M[j][k];
          }
     }
  cout << "\nDividing row " << row + 1 << " by " << f << endl;
  for (int i = 0; i < T[row].size(); i++)
       T[row][i] = T[row][i]/f;

  return T;
}

// in matrix M, add f times row j to row k
vector< vector<Fraction> > mRowAdd(Fraction f, vector< vector<Fraction> > M, int row_j, int row_k)    {
  int size = M[0].size();  // number of columns

  vector< vector<Fraction> > T;
  string inputBuffer = "";

  // It is necessary when using STL <vector> of my own Fraction objects
  // otherwise SEGMENTATION FAULT (core dump) when attemting to initialize.
  // These are NOT arrays!

  // Once created, we can use array-like index accessing

      for(int r = 0; r < M.size(); r++)
      {
          vector<Fraction> row_vector;
          T.push_back(row_vector);

          for(int c = 0; c < size; c++)
          {
            inputBuffer = "0 1";
            Fraction fracBuffer(inputBuffer);
            T[r].push_back(fracBuffer);
            T[r][c] = M[r][c];
          }
     }
 cout << "\nMultiplying row " << row_j + 1 << " by " << f << " and adding result to row " << row_k + 1 << endl;
  for (int i = 0; i < size; i++)
         T[row_k][i] = T[row_k][i] + ( f * T[row_j][i]);

  return T;

}

// convert matrix M to reduced row echelon form
vector< vector<Fraction> > rref(vector< vector<Fraction> > M, int nrows, int ncols)  {
  Fraction negativeFrac(-1/1);
  int lead = 0;
  string inputBuffer = "";

  vector< vector<Fraction> > R;

  // It is necessary when using STL <vector> of my own Fraction objects
  // otherwise SEGMENTATION FAULT (core dump) when attemting to initialize.
  // These are NOT arrays!

  // Once created, we can use array-like index accessing

  // Copy matrix M into matrix R

      for(int j = 0; j < nrows; j++)
      {
          vector<Fraction> row_vector;
          R.push_back(row_vector);

          for(int k = 0; k < ncols; k++)
          {
            inputBuffer = "0 1";
            Fraction fracBuffer(inputBuffer);
            R[j].push_back(fracBuffer);
            R[j][k] = M[j][k];
          }
     }


  for (int row = 0; row < nrows; row++)   {
    if (lead > (ncols-1) ) return R;
    int i = row;
    while (R[i][lead].getNum() == 0)  {
      ++i;
      if (i > (nrows-1) )  {
        i = row;
        ++lead;
        if ( lead > (ncols-1) )  return R;
      }
    }

    //R = swap_rows(R, i, row);   // UNNECESSARY since it swaps a row with itself!

    R = divide_row(R[row][lead], R, row);
    showMatrix(nrows, ncols, R);
    for (i = 0; i < nrows; i++)   {
      if (i != row)  {
         R = mRowAdd(negativeFrac * R[i][lead], R, row, i);
         showMatrix(nrows, ncols, R);
       }
    }
  }
  return R;

}

int main(void)
{
    int rows, cols;
    string inputBuffer = "";
    vector<vector<Fraction> > mat;
    vector<Fraction> buffer;
    Fraction negativeFrac(-1/1);

    cout << "Enter the number of rows in the matrix: ";
    cin >> rows;
    cout << "Enter the number of columns in the matrix: ";
    cin >> cols;

    cout << endl;

    for(int i = 0; i < rows; i++)
    {
        vector<Fraction> row;
        mat.push_back(row);
        for(int j = 0; j < cols; j++)
        {
            cout << "Enter row " << i + 1 << ", column " << j + 1 << " : ";
            cin >> inputBuffer;
            Fraction fracBuffer(inputBuffer);
            mat[i].push_back(fracBuffer);
        }
        cout << endl;
    }
    cout << "\nOriginal Matrix:\n\n";
    showMatrix(rows, cols, mat);

vector< vector<Fraction> > echelon;

// It is necessary when using STL <vector> of my own Fraction objects
// otherwise SEGMENTATION FAULT (core dump) when attemting to initialize.
// These are NOT arrays!

// Once created, we can use array-like index accessing

    for(int j = 0; j < rows; j++)
    {
        vector<Fraction> row_vector;
        echelon.push_back(row_vector);

        for(int k = 0; k < cols; k++)
        {
          inputBuffer = "0 1";
          Fraction fracBuffer(inputBuffer);
          echelon[j].push_back(fracBuffer);
        }
   }

    echelon = rref(mat, rows, cols);
    cout << "************************************************************\n";
    cout << "Row reduced echelon form: " << endl;
    showMatrix(rows, cols, echelon);
    cout << "************************************************************\n";
    cout << endl;

}
