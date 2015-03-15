#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

double **create_sigma_matrix(int);
void print_matrix(double**, int, int);
double **MakeSN(int);
double **mymatmul(double** m1, double** m2, int row1, int col1, int col2);
double calculate_gravitational_potential(double, double, int);
void free_matrix(double**);

int main()
{
  int m = 0, N;
  int should_stop = 0;
  clock_t start, end;
  double result, time_taken;
  printf("    N            Result         Time taken \n");
  printf("--------- -------------------- ------------\n");

  for (N = 32; N <= 96; N+= 32)
  {
    start = clock();
    result = calculate_gravitational_potential(0.5, 0.5, N);
    end = clock();
    time_taken = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%9d %20.8f %12.6f\n", N, result, time_taken);  	
  }

  while (!should_stop)
  {
  	int i;
    for (i = 4; i <= 6; i++)
    {
      N = i*(int)pow(2, 5+m);
      start = clock();
      result = calculate_gravitational_potential(0.5, 0.5, N);
      end = clock();
      time_taken = (double) (end - start) / CLOCKS_PER_SEC;
      printf("%9d %20.8f %12.6f\n", N, result, time_taken);
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

double calculate_gravitational_potential(double x, double y, int N)
{
  double** M,
        ** Sn,
        ** sigma_jn,
        ** sigma_jk;

  double result = 0;
  int j, k;

  M = create_sigma_matrix(N);
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

