#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

double **create_matrix(int, int);
void free_matrix(double**);
void print_matrix(double**, int, int);
double **create_smooth_sigma_matrix(int);
void FastSINE1(double** S, double** T, int N);
void FastSINE2(double** S, double** T, int N);
double** calculate_gravitational_potential(int N);

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
    time_diff = (double) (end - start);
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
      end = clock();
      time_diff = (double) (end- start);
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
  int j, k;
  double** x1 = create_smooth_sigma_matrix(N);
  double** x2 = create_matrix(N-1, N-1);

  FastSINE1(x1, x2, N);
  FastSINE2(x2, x1, N);

  for (j = 1; j < N; j++)
    for (k = 1; k < N; k++)
      x1[j][k] *= (4./(N*N)) * (1/((j*j+k*k)*PI*PI));

  FastSINE2(x1, x2, N);
  FastSINE1(x2, x1, N);
  
  free_matrix(x2);
  return x1;
}
