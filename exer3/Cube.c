#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define PI                3.14159265359

/* Function Declarations */
double*** create_cube(int N);
void free_cube(double*** m, int N);
void print_cube(double*** m, int N);
double*** create_smooth_sigma_cube(int N);
double*** to_sigma_imn(double*** c, double** Sn, int N);
double*** to_sigma_ijn(double*** c, double** Sn, int N);
double*** to_sigma_ijk(double*** c, double** Sn, int N);
double*** to_psi_ijk(double*** c, int N);

double*** create_cube(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  double*** m = (double***) calloc(N+1, sizeof(double**));
  for (i = 1; i <=N; i++)
    m[i] = create_matrix(N, N);
  return m;
}

void free_cube(double*** m, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  for (i = 1; i <=N; i++)
    free_matrix(m[i]);
  free(m);
}

void print_cube(double*** m, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
   int i, j, k;
   for (i = 1; i <= N; i++)
     for (j = 1; j <= N; j++)
       for (k = 1; k <= N; k++)
        printf("M[%5d][%5d][%5d] = %10.5f\n", i, j, k, m[i][j][k]);
}

double*** create_smooth_sigma_cube(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  double*** cube = create_cube(N);

  double lower_i1 = N*3/8,   lower_i2 = N*7/16,
         lower_j1 = N*7/16,  lower_j2 = N*15/32,
         lower_k1 = N*3/8,   lower_k2 = N/2,
         upper_i1 = N/2,     upper_i2 = N*9/16,
         upper_j1 = N*9/16,  upper_j2 = N*17/32,
         upper_k1 = N/2,     upper_k2 = N*9/16;

  for (i = lower_i1; i <= upper_i1; i++)
    for (j = lower_j1; j <= upper_j1; j++)
      for (k = lower_k1; k <= upper_k1; k++)
        if ((i == lower_i1 && j == lower_j1 && k == lower_k1) ||
            (i == lower_i1 && j == lower_j1 && k == upper_k1) ||
            (i == lower_i1 && j == upper_j1 && k == lower_k1) ||
            (i == lower_i1 && j == upper_j1 && k == upper_k1) ||
            (i == upper_i1 && j == lower_j1 && k == lower_k1) ||
            (i == upper_i1 && j == lower_j1 && k == upper_k1) ||
            (i == upper_i1 && j == upper_j1 && k == lower_k1) ||
            (i == upper_i1 && j == upper_j1 && k == upper_k1) )
          cube[i][j][k] += 1250.;
        else if ((i == lower_i1 && j == lower_j1) ||
                 (i == lower_i1 && j == upper_j1) ||
                 (i == lower_i1 && k == lower_k1) ||
                 (i == lower_i1 && k == upper_k1) ||
                 (k == lower_k1 && j == lower_j1) ||
                 (k == lower_k1 && j == lower_j1) )
          cube[i][j][k] += 2500.;
        else if (i == lower_i1 || i == upper_i1 ||
                 j == lower_j1 || j == upper_j1 ||
                 k == lower_k1 || k == upper_k1 )
          cube[i][j][k] += 5000.;
        else
          cube[i][j][k] += 10000.;

  for (i = lower_i2; i <= upper_i2; i++)
    for (j = lower_j2; j <= upper_j2; j++)
      for (k = lower_k2; k <= upper_k2; k++)
        if ((i == lower_i1 && j == lower_j1 && k == lower_k1) ||
            (i == lower_i1 && j == lower_j1 && k == upper_k1) ||
            (i == lower_i1 && j == upper_j1 && k == lower_k1) ||
            (i == lower_i1 && j == upper_j1 && k == upper_k1) ||
            (i == upper_i1 && j == lower_j1 && k == lower_k1) ||
            (i == upper_i1 && j == lower_j1 && k == upper_k1) ||
            (i == upper_i1 && j == upper_j1 && k == lower_k1) ||
            (i == upper_i1 && j == upper_j1 && k == upper_k1) )
              cube[i][j][k] += 1250.;
        else if ((i == lower_i1 && j == lower_j1) ||
                 (i == lower_i1 && j == upper_j1) ||
                 (i == lower_i1 && k == lower_k1) ||
                 (i == lower_i1 && k == upper_k1) ||
                 (k == lower_k1 && j == lower_j1) ||
                 (k == lower_k1 && j == lower_j1) )
          cube[i][j][k] += 2500.;
        else if (i == lower_i1 || i == upper_i1 ||
                 j == lower_j1 || j == upper_j1 ||
                 k == lower_k1 || k == upper_k1 )
          cube[i][j][k] += 5000.;
        else
          cube[i][j][k] += 10000.;

  return cube;
}

double*** to_sigma_imn(double*** c, double** Sn, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, l, m, n;
  double*** c_new = create_cube(N);
  
  #pragma omp parallel for
  for (i = 1; i < N; i++)
    for (l = 1; l < N; l++)
      for (m = 1; m < N; m++)
        for (n = 1; n < N; n++)
          c_new[i][m][n] += c[l][m][n] * Sn[i][l];
  return c_new;
}

double*** to_sigma_ijn(double*** c, double** Sn, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, m, n;
  double*** c_new = create_cube(N);
  
  #pragma omp parallel for
  for (i = 1; i < N; i++)
    for (j = 1; j < N; j++)
      for (m = 1; m < N; m++)
        for (n = 1; n < N; n++)
          c_new[i][j][n] += c[i][m][n] * Sn[j][m];
  return c_new;
}

double*** to_sigma_ijk(double*** c, double** Sn, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k, n;
  double*** c_new = create_cube(N);
  
  #pragma omp parallel for
  for (i = 1; i < N; i++)
    for (n = 1; n < N; n++)
      for (j = 1; j < N; j++)
        for (k = 1; k < N; k++)
          c_new[i][j][k] += c[i][j][n] * Sn[n][k];
  return c_new;
}

double*** to_psi_ijk(double*** c, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  double*** c_new = create_cube(N);
  
  #pragma omp parallel for
  for (i = 1; i < N; i++)
    for (j = 1; j < N; j++)
      for (k = 1; k < N; k++)
        c_new[i][j][k] = c[i][j][k] * 8./(N*N*N) / ((i*i+j*j+k*k)*PI*PI);
  return c_new;
}