#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

double*** create_cube(int N);
void free_cube(double***, int);
void print_cube(double***, int);
double ***create_smooth_sigma_cube(int);

double ***calculate_gravitational_potential(int);
void FastSINE1(double*** S, double*** T, int N);
void FastSINE2(double*** S, double*** T, int N);
void FastSINE3(double*** S, double*** T, int N);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int m = 0, N;
  int should_stop = 0;
  clock_t start, end;
  double ***result;
  double time_taken;
  printf("    N            Result         Time taken \n");
  printf("--------- -------------------- ------------\n");

  for (N = 32; N <= 96; N+= 32)
  {
    start = clock();
    result = calculate_gravitational_potential(N);
    end = clock();
    time_taken = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%9d %20.8f %12.6f\n", N, result[N/2][N/2][N/2], time_taken);
    free_cube(result, N);
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
      time_taken = (double) (end - start) / CLOCKS_PER_SEC;
      printf("%9d %20.8f %12.6f\n", N, result[N/2][N/2][N/2], time_taken);
      free_cube(result, N);
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

double ***calculate_gravitational_potential(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  double*** x1 = create_smooth_sigma_cube(N);
  double*** x2 = create_cube(N-1);

  FastSINE1(x1, x2, N);
  FastSINE2(x2, x1, N);
  FastSINE3(x1, x2, N);

  for (i = 1; i < N; i++)
    for (j = 1; j < N; j++)
      for (k = 1; k < N; k++)
        x2[i][j][k] = x2[i][j][k] * 8./(N*N*N) / ((i*i+j*j+k*k)*PI*PI);

  FastSINE3(x2, x1, N);
  FastSINE2(x1, x2, N);
  FastSINE1(x2, x1, N);

  free_cube(x2, N-1);
  return x1;
}
