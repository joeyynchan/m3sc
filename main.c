#include <stdio.h>
#include <stdlib.h>

void printMatrix(double**, int, int);

int main()
{

  double** matrix;
  int row, col, n, i, j;

  double m[3][3] = {{1., 2., 3.},{4., 5., 6.},{7., 8., 9.}};

  row = 3;
  col = 3;
  matrix = (double**) malloc((row+1)*sizeof(double*));
  matrix[0] = (double*) malloc((row*col+1)*sizeof(double));
  matrix[1] = matrix[0];
  for (n = 2; n <= row; n++)
  {
  	matrix[n] = matrix[n-1]+col;
  }

  for (i = 0; i < row; i++)
  	for (j = 0; j < col; j++)
  	{
  		matrix[i+1][j+1] = m[i][j];
  	}

  printMatrix(matrix, row, col);

  free(matrix[0]);
  free(matrix);

  return 0;
}