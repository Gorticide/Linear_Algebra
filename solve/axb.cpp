// to compile with g++ in versions of gcc < 6.3, compile with -std=c++11
// or -std=gnu++11:
// g++ -g axb.cpp fraction.cpp fraction.h -std=gnu++11 -o axb


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "fraction.h"

using namespace std;

void showMatrix(int, int, vector<vector<Fraction> >);
Fraction determinant(vector<vector<Fraction> >, int);

vector<vector<Fraction>> cofactor(vector<vector<Fraction> >, int);

vector<vector<Fraction>> transpose(vector<vector<Fraction> >, vector<vector<Fraction> >, int );
vector<Fraction> solve(vector<vector<Fraction>>, vector<Fraction>, int);

int main(void)
{
    int rows, cols;
    Fraction d;

    string inputBuffer = "";
    vector<vector<Fraction> > a;
    vector<Fraction> buffer;
    Fraction multNumber2;

    int currentRow = 0, currentCol = 0;

    int size,row,column,ctr1,ctr2;

    vector<Fraction> b;
    vector<Fraction> x;

    std::cout << "ENTER THE SIZE OF THE (square) MATRIX () \n";
    std::cin >> size;
    rows = size;
    cols = size;

  // We must manually create these vectors of Fractions
  std::cout << "\nEnter the elements of the original matrix.\n\n";
    for(int i = 0; i < rows; i++)
    {
        vector<Fraction> row;
        a.push_back(row);
        for(int j = 0; j < cols; j++)
        {
            cout << "Enter row " << i + 1 << ", column " << j + 1 << " : ";
            cin >> inputBuffer;
            Fraction fracBuffer(inputBuffer);
            a[i].push_back(fracBuffer);
        }
        cout << endl;
    }
    std::cout << "\nOriginal Matrix:\n";
    showMatrix(rows, cols, a);
    d = determinant(a, size);


    if (d.getNum() == 0)  {

     cout << "\nInverse of Entered Matrix is not possible since the determinant is " << d << "\n";
     cout << "\nThere is either NO SOLUTION or an INFINITE NUMBER of SOLUTIONS\n\n";
     return 0;
   }
    else {
      cout << "The determinant is " << d;

      std::cout << "\nEnter the elements of the constants [RHS] column vector.\n\n";
      for(int j = 0; j < size; j++)
      {
       cout << "Enter element " << j + 1 << " : ";
       cin >> inputBuffer;
       Fraction fracBuffer(inputBuffer);
       b.push_back(fracBuffer);
      }
      std::cout << "\nThe constant column vector:\n\n";
      for (int j = 0; j < size; j++)   {
         std::cout << b[j] << std::endl;
      }
      printf("\n");
      x = solve(cofactor(a, size), b, size);


  std::cout << "\nThe solution column vector x is:\n\n";
  for (int i = 0; i < size; i++)
    std:cout << x[i] << std::endl;
  }
 std::cout << std::endl;

}

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

/*For calculating Determinant of the Matrix */

Fraction determinant(vector<vector<Fraction> > a, int k)

{

  Fraction s(1);
  Fraction det(0);
  vector<vector<Fraction> >  b;
  string inputBuffer = "";
  int i, j, m, n, c;


  // These seems redundant, but it is necessary when using STL <vector>
  // of my own Fraction objects otherwise SEGMENTATION FAULT (core dump) when
  // attemting to initialize.   These are NOT arrays!

  // Once created, we can use array-like index accessing

  int rows = k;
  int cols = k;

      for(int i = 0; i < rows; i++)
      {
          vector<Fraction> row;
          b.push_back(row);

          for(int j = 0; j < cols; j++)
          {
              inputBuffer = "0 1";
              Fraction fracBuffer(inputBuffer);
              b[i].push_back(fracBuffer);
          }
     }


  if (k == 1)

    {

     return (a[0][0]);

    }

  else

    {

     det = Fraction(0,1);

     for (c = 0; c < k; c++)

       {

        m = 0;

        n = 0;

        for (i = 0;i < k; i++)

          {

            for (j = 0 ;j < k; j++)

              {

                b[i][j] = 0;

                if (i != 0 && j != c)

                 {

                   b[m][n] = a[i][j];

                   if (n < (k - 2))

                    n++;

                   else

                    {

                     n = 0;

                     m++;

                     }

                   }

               }

             }

          det = det + s * (a[0][c] * determinant(b, k - 1));

          s = Fraction(-1) * s;

          }

    }



    return (det);

}



vector<vector<Fraction>> cofactor(vector<vector<Fraction> > num, int f)

{
  string inputBuffer = "";
  vector<vector<Fraction> > b;
  vector<vector<Fraction> > fac;
  int rows = f;
  int cols = f;

  vector<vector<Fraction>> A_inv;

  // These may seem redundant, but it is necessary when using STL <vector>
  // of my own Fraction objects otherwise SEGMENTATION FAULT (core dump) when
  // attemting to initialize.   These are NOT arrays!

  // Once created, we can use array-like index accessing

      for(int i = 0; i < rows; i++)
      {
          vector<Fraction> row;
          b.push_back(row);
          fac.push_back(row);

          for(int j = 0; j < cols; j++)
          {
              inputBuffer = "0 1";
              Fraction fracBuffer(inputBuffer);
              b[i].push_back(fracBuffer);
              fac[i].push_back(fracBuffer);
          }
     }

 int p, q, m, n, i, j;

 for (q = 0;q < f; q++)

 {

   for (p = 0;p < f; p++)

    {

     m = 0;

     n = 0;

     for (i = 0;i < f; i++)

     {

       for (j = 0;j < f; j++)

        {

          if (i != q && j != p)

          {

            b[m][n] = num[i][j];

            if (n < (f - 2))

             n++;

            else

             {

               n = 0;

               m++;

               }

            }

        }

      }

      fac[q][p] = Fraction(pow(-1, q + p)) * determinant(b, f - 1);

    }

  }

  A_inv = transpose(num, fac, f);

  return A_inv;

}

/*Finding transpose of matrix*/

vector<vector<Fraction>> transpose(vector<vector<Fraction> >num, vector<vector<Fraction> >fac, int r)

{

  int i, j;
  Fraction d;
  int rows = r;
  int cols = r;

  string inputBuffer = "";
  vector<vector<Fraction> > b;
  vector<vector<Fraction> > inverse;

  // These may seem redundant, but it is necessary when using STL <vector>
  // of my own Fraction objects otherwise SEGMENTATION FAULT (core dump) when
  // attemting to initialize.   These are NOT arrays!

  // Once created, we can use array-like index accessing

      for(int i = 0; i < rows; i++)
      {
          vector<Fraction> row;
          b.push_back(row);
          inverse.push_back(row);

          for(int j = 0; j < cols; j++)
          {
              inputBuffer = "0 1";
              Fraction fracBuffer(inputBuffer);
              b[i].push_back(fracBuffer);
              inverse[i].push_back(fracBuffer);
          }
     }

  for (i = 0;i < r; i++)

    {

     for (j = 0;j < r; j++)

       {

         b[i][j] = fac[j][i];

        }

    }

  d = determinant(num, r);

  for (i = 0;i < r; i++)

    {

     for (j = 0;j < r; j++)

       {

        inverse[i][j] = b[i][j] / d;

        }

    }

   printf("\n\nThe inverse of the original matrix is: \n");

  showMatrix(r, r, inverse);

  return inverse;

}

vector<Fraction> solve(vector< vector<Fraction> > A_inv, \
                      vector<Fraction> b, int size)  {

  vector<Fraction> result;

  for(int i = 0; i < size; i++)
   {
     string inputBuffer = "0 1";
     Fraction fracBuffer(inputBuffer);
     result.push_back(fracBuffer);
  }
    for (int r = 0; r < size; r++)  {
      Fraction sum(0);
      for (int c = 0; c < size; c++)  {
        sum = sum + A_inv[r][c]*b[c];
      }
      result[r] = sum;
    }

    return result;

}
