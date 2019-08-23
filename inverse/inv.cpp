#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "fraction.h"

using namespace std;

void showMatrix(int, int, vector<vector<Fraction> >);
Fraction determinant(vector<vector<Fraction> >, int);

void cofactor(vector<vector<Fraction> >, int);

void transpose(vector<vector<Fraction> >, vector<vector<Fraction> >, int );

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

    std::cout << "ENTER THE SIZE OF THE (square) MATRIX () \n";
    std::cin >> size;
    rows = size;
    cols = size;

  // We must manually create these vectors of Fractions
  // In the process I initialize uppertriangle and lowertriangle elements to 0
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

    if (d.getNum() == 0)

     cout << "\nInverse of Entered Matrix is not possible since the determinant is " << d << "\n";

    else
     {
       cout << "\nThe determinant is " << d;
        cofactor(a, size);
     }



}

void showMatrix(int rows, int cols, vector<vector<Fraction> > mat)
{
   printf("___________________________________________________\n\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            cout << "\t" << mat[i][j];
        if (i != rows - 1) cout << "\n";
    }
    printf("\n___________________________________________________\n\n");
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



void cofactor(vector<vector<Fraction> > num, int f)

{
  string inputBuffer = "";
  vector<vector<Fraction> > b;
  vector<vector<Fraction> > fac;
  int rows = f;
  int cols = f;

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

  transpose(num, fac, f);

}

/*Finding transpose of matrix*/

void transpose(vector<vector<Fraction> >num, vector<vector<Fraction> >fac, int r)

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

   printf("\n\n\nThe inverse of matrix is : \n");

  showMatrix(r, r, inverse);

}
