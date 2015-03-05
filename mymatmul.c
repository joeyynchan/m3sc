#include <stdio.h>
#include <stdlib.h>

#define ARC4RANDOM_MAX      0x100000000

/* Matrix Construction and Destruction*/
double** create_matrix(int, int);
double**create_random_matrix(int, int);
double** create_matrix_with_entries(int, int, double*);
void free_matrix(double**);
void print_matrix(double**, int, int);

/* Matrix Multiplication with different loop order*/
double **mymatmul(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_ijk(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_ikj(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_jik(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_jki(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_kij(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_kji(double** m1, double** m2, int row1, int col1, int col2);

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

double** create_random_matrix(int row, int col)
{
  int i, j;
  double** m = create_matrix(row, col);
  for (i = 1; i <= row; i++)
    for (j = 1; j <= col; j++)
      /*m[i][j] = (double)arc4random()/(double)ARC4RANDOM_MAX;*/
      m[i][j] = (double)rand() / RAND_MAX;
  return m;
}

double** create_matrix_with_entries(int row, int col, double* e)
{
  int n, i, j, k = 0;
  double** m = (double**) calloc(row+1, sizeof(double*));
  m[0] = (double*) calloc(row*col+1, sizeof(double));
  m[1] = m[0];
  for (n = 2; n <= row; n++)
    m[n] = m[n-1]+col;
  for (i = 1; i <= row; i++)
    for (j = 1; j <= col; j++)
      m[i][j] = *(e+(k++));
  return m;
}

void free_matrix(double** matrix)
{
  free(matrix[0]);
  free(matrix);
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





double **mymatmul(double** m1, double** m2, int row1, int col1, int col2)
{
  return mymatmul_ikj(m1, m2, row1, col1, col2);
}

double **mymatmul_ijk(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (i = 1; i <= row1; i++)
    for (j = 1; j <= col2; j++)
      for (k = 1; k <= col1; k++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_ikj(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (i = 1; i <= row1; i++)
    for (k = 1; k <= col1; k++)
      for (j = 1; j <= col2; j++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_jik(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (j = 1; j <= col2; j++)
    for (i = 1; i <= row1; i++)
      for (k = 1; k <= col1; k++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_jki(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (j = 1; j <= col2; j++)
    for (k = 1; k <= col1; k++)
      for (i = 1; i <= row1; i++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_kij(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (k = 1; k <= col1; k++)
    for (i = 1; i <= row1; i++)
      for (j = 1; j <= col2; j++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_kji(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (k = 1; k <= col1; k++)
    for (j = 1; j <= col2; j++)
      for (i = 1; i <= row1; i++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}


