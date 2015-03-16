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
double calculate_gravitational_potential(double, double, int);
void free_matrix(double**);

int main()
{
  int m = 0, N = 8192;
  int should_stop = 0;
  clock_t start, end;
  double result, time_taken;
  printf("  x     y          Result      \n");
  printf("----- ----- -------------------\n");

  
  for (m = 1; m < 8192; m++)
  {
    result = calculate_gravitational_potential(0.5, 0.5, 96);
    printf("%5d %5d %20.8e\n", m, N/2, result);  	
  }

  return 0;
}

double calculate_gravitational_potential(double x, double y, int N)
{
  double** M,
        ** Sn,
        ** sigma_jn,
        ** sigma_jk;

  double result = 0;
  int j, k;

  M = create_smooth_sigma_matrix(N);
  Sn = MakeSN(N);
  sigma_jn = mymatmul(Sn, M, N-1, N-1, N-1);
  sigma_jk = mymatmul(sigma_jn, Sn, N-1, N-1, N-1);

  for (j = 1; j < N; j++)
    for (k = 1; k < N; k++)
      result += sigma_jk[j][k] * (4./(N*N)) * (1/((j*j+k*k)*PI*PI)) *sin(j*PI*x)*sin(k*PI*y);

  free_matrix(M);
  free_matrix(Sn);
  free_matrix(sigma_jn);
  free_matrix(sigma_jk);

  return result;
}

