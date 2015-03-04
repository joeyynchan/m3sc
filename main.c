#include <stdio.h>
#include <stdlib.h>

void print_matrix(double**, int, int);
double** mymatmul(double**, double**, int, int, int);
double** create_matrix(int, int);
void free_matrix(double**);

int main()
{

  double** matrix1, **matrix2;
  int row, col, n, i, j;

  double m[3][3] = {{1., 2., 3.},{4., 5., 6.},{7., 8., 9.}};

  row = 3;
  col = 3;
  matrix1 = create_matrix(row, col);
  for (i = 0; i < row; i++)
  	for (j = 0; j < col; j++)
  	{
  		matrix1[i+1][j+1] = m[i][j];
  	}

  matrix2 = mymatmul(matrix1, matrix1, row, col, col);
  print_matrix(matrix2, row, col);

  free_matrix(matrix1);
  free_matrix(matrix2);

  return 0;
}