#include <stdio.h>

double **mymatmul(double** m1, double** m2, int row1, int col1, int col2)
{
  return 0;
}

void printMatrix(double** m, int row, int col)
{
  int i, j;
  for (i = 1; i <= row; i++)
  {
  	printf("(");
    for (j = 1; j < col; j++)
    {
        printf("%10.5f, ", m[i][j]);
    }
    printf("%10.5f)\n", m[i][col]);
  }
}