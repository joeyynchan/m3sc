#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

double **create_sigma_matrix(int);
void print_matrix(double**, int, int);
double **MakeSN(int);
double **mymatmul(double** m1, double** m2, int row1, int col1, int col2);
double calculate_gravitational_potential(double, double, double, int);
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
    result = calculate_gravitational_potential(0.5, 0.5, 0.5, N);
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
      result = calculate_gravitational_potential(0.5, 0.5, 0.5, N);
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

double calculate_gravitational_potential(double x, double y, double z, int N)
{
  double*** sigma_lmn,
        *** sigma_imn,
        *** sigma_ijn,
        *** sigma_ijk;

  double result = 0;
  int i, j, k;

  sigma_lmn = create_sigma_cube(N);
  sigma_imn = to_sigma_imn(sigma_lmn, N); 
  sigma_ijn = to_sigma_ijn(sigma_imn, N);
  sigma_ijk = to_sigma_ijk(sigma_ijn, N);

  for (i = 1; i < N; i++) 
    for (j = 1; j < N; j++)
      for (k = 1; k < N; k++)
        result += sigma_ijk[i][j][k] * (8./(N*N*N)) * (1/((i*i+j*j+k*k)*PI*PI)) *sin(i*PI*x)*sin(j*PI*y)*sin(k*PI*z);

  free_cube(sigma_lmn);
  free_cube(sigma_imn);
  free_cube(sigma_ijn);
  free_cube(sigma_ijk);

  return result;
}

