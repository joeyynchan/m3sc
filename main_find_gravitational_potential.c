#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

void free_matrix(double**);
void print_matrix(double**, int, int);

double **MakeSN(int);
double **create_sigma_matrix(int);
double **create_smooth_sigma_matrix(int);
double **calculate_gravitational_potential(int);
double **mymatmul(double** m1, double** m2, int row1, int col1, int col2);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int m = 0, N;
  int should_stop = 0;
  clock_t start, end;
  double **result, time_taken, time_diff;
  printf("    N            Result         Time taken \n");
  printf("--------- -------------------- ------------\n");

  for (N = 32; N <= 96; N+= 32)
  {
    start = clock();
    result = calculate_gravitational_potential(N);
    end = clock();
    time_diff = (double) (end_time - start_time);
    time_diff = (time_diff == 0) ? 1. : time_diff;
    time_taken = (double) time_diff/CLOCKS_PER_SEC;
    printf("%9d %20.8f %12.6f\n", N, result[N/2][N/2], time_taken);  	
  }

  while (!should_stop)
  {
  	int i;
    for (i = 4; i <= 6; i++)
    {
      N = i*(int)pow(2, 5+m);
      start = clock();
      result = calculate_gravitational_potential(N);
      time_diff = (double) (end_time - start_time);
      time_diff = (time_diff == 0) ? 1. : time_diff;
      time_taken = (double) time_diff/CLOCKS_PER_SEC;
      printf("%9d %20.8f %12.6f\n", N, result[N/2][N/2], time_taken);
      if (time_taken > 600)
      {
        should_stop = 1;
        break;
      }
    }
    m++;
  }
  return 0;
}

double** calculate_gravitational_potential(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  double** M,
        ** Sn,
        ** sigma_jn,
        ** sigma_jk,
        ** psi_jn,
        ** psi_mn;

  int j, k;
  M = create_sigma_matrix(N);
  /*M = create_smooth_sigma_matrix(N);*/
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

