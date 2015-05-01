#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define PI                3.14159265359

/* Matrix Construction and Destruction*/
double **create_matrix(int, int);
void free_matrix(double**);
void print_matrix(double**, int, int);

/* Matrix Multiplication with different loop order*/
double **mymatmul(double**, double**, int, int, int);

/* Construct Symmetric Matrix */
double **MakeSN(int);
double **create_smooth_sigma_matrix(int);


double** create_matrix(int row, int col)
{
  /* Chan, Joey, JMCSC, ync12 */
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
  /* Chan, Joey, JMCSC, ync12 */
  free(matrix[0]);
  free(matrix);
}

void print_matrix(double** m, int row, int col)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j;
  for (i = 1; i <= row; i++)
    for (j = 1; j <= col; j++)
      printf("M[%4d][%4d] = %15.6f\n", i, j, m[i][j]);
}

double **mymatmul(double** m1, double** m2, int row1, int col1, int col2)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  double** m = create_matrix(row1, col2);

  #pragma omp parallel for
  for (i = 1; i <= row1; i++)
  {
    double* m1_row_i = m1[i];
    double* m_row_i = m[i];
    for (k = 1; k <= col1; k++)
    {
      double* m2_row_k = m2[k];
      double m1_ik = m1_row_i[k];
      for (j = 1; j <= col2; j++)
        m_row_i[j] += m1_ik * m2_row_k[j];
    }
  }
  return m;
}

double **MakeSN(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j;
  double** M = create_matrix(N-1, N-1);
  for (i = 1; i < N; i++)
    for (j = 1; j < N; j++)
      M[i][j] = sin((double)i*(double)j*PI/(double)N);
  return M;
}

double **create_smooth_sigma_matrix(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j;
  int lower_i1 = N*3/8,
      upper_i1 = N/2,
      lower_j1 = N*7/16,
      upper_j1 = N*9/16,
      lower_i2 = N/2,
      upper_i2 = N*9/16,
      lower_j2 = N*15/32,
      upper_j2 = N*17/32;
  double** M = create_matrix(N, N);

  if (N % 32 != 0)
  {
    printf("%d is not a valid value for N\n", N);
    return 0;
  }

  for (i = lower_i1; i <= upper_i1; i++)
    for (j = lower_j1; j <= upper_j1; j++)
      if ((i == lower_i1 && (j == lower_j1 || j == upper_j1)) ||
          (i == upper_i1 && (j == lower_j1 || j == upper_j1)))
        M[i][j] = 250.;
      else if (i == lower_i1 || i == upper_i1 ||
               j == lower_j1 || j == upper_j1)
        M[i][j] = 500.;
      else
        M[i][j] = 1000.;

  for (i = lower_i2; i <= upper_i2; i++)
    for (j = lower_j2; j <= upper_j2; j++)
      if ((i == lower_i2 && (j == lower_j2 || j == upper_j2)) ||
          (i == upper_i2 && (j == lower_j2 || j == upper_j2)))
        M[i][j] = (M[i][j] != 0) ?  (M[i][j] + 125.)/2. : 125.;
      else if (i == lower_i2 || i == upper_i2 ||
               j == lower_j2 || j == upper_j2)
        M[i][j] = (M[i][j] != 0) ?  (M[i][j] + 250.)/2. : 250.;
      else
        M[i][j] = (M[i][j] != 0) ?  (M[i][j] + 500.)/2. : 500.;
  return M;
}
