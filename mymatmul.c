#include <stdio.h>
#include <stdlib.h>

double **mymatmul(double**, double**, int, int, int);
void print_matrix(double**, int, int);
double** create_matrix(int, int);
void free_matrix(double** matrix);

double **mymatmul(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);

  int i, j, k;
  for (i = 1; i <= row1; i++)
    for (j = 1; j <= col2; j++)
      for (k = 1; k <= col1; k++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

void print_matrix(double** m, int row, int col)
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

double** create_matrix(int row, int col)
{
  int n;
  double** m = (double**) calloc(row+1, sizeof(double*));
  m[0] = (double*) calloc(row*col+1, sizeof(double));
  m[1] = m[0];
  for (n = 2; n <= row; n++)
    m[n] = m[n-1]+col;
  return m;
}

void free_matrix(double** matrix)
{
  free(matrix[0]);
  free(matrix);
}