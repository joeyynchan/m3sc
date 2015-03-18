#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

double **create_sigma_matrix(int);
double **create_smooth_sigma_matrix(int);
void print_matrix(double**, int, int);
double **MakeSN(int);
double **mymatmul(double** m1, double** m2, int row1, int col1, int col2);
double **calculate_gravitational_potential(int);
void free_matrix(double**);

int main()
{
  int m = 0, N = 8192;
  int should_stop = 0;
  clock_t start, end;
  double ** result;
  double time_taken;
  printf("  x     y          Result      \n");
  printf("----- ----- -------------------\n");

  
  result = calculate_gravitational_potential(N);
  for (m = 1; m < N; m++)
  {
    printf("%5d %5d %20.8f\n", m, N/2, result[m][N/2]);  	
  }

  return 0;
}

double** calculate_gravitational_potential(int N)
{
  double** M,
        ** Sn,
        ** sigma_jn,
        ** sigma_jk,
        ** psi_jn,
        ** psi_mn;

  int j, k;
  M = create_smooth_sigma_matrix(N);
  Sn = MakeSN(N);
  sigma_jn = mymatmul(Sn, M, N-1, N-1, N-1);
  free_matrix(M);
  sigma_jk = mymatmul(sigma_jn, Sn, N-1, N-1, N-1);
  free_matrix(sigma_jn);

  for (j = 1; j < N; j++)
    for (k = 1; k < N; k++)
      sigma_jk[j][k] *= (4./(N*N)) * (1/((j*j+k*k)*PI*PI));


  psi_jn = mymatmul(sigma_jk, Sn, N-1, N-1, N-1);
  free_matrix(sigma_jk);
  psi_mn = mymatmul(Sn, psi_jn, N-1, N-1, N-1);
  free_matrix(psi_jn);
  free_matrix(Sn);

  return psi_mn;
}

