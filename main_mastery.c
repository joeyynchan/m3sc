#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

void free_matrix(double**);
void free_cube(double***, int);
void print_cube(double***, int);
void print_matrix(double**, int, int);

double ***calculate_gravitational_potential(int);

double **MakeSN(int);
double **create_sigma_matrix(int);
double **mymatmul(double** m1, double** m2, int row1, int col1, int col2);

double ***create_sigma_cube(int);
double ***create_smooth_sigma_cube(int);
double ***to_sigma_imn(double***, double**, int);
double ***to_sigma_ijn(double***, double**, int);
double ***to_sigma_ijk(double***, double**, int);
double ***to_psi_ijk(double***, int);


int main()
{
  int m = 0, N;
  int should_stop = 0;
  clock_t start, end;
  double ***result;
  double time_taken;
  printf("    N            Result         Time taken \n");
  printf("--------- -------------------- ------------\n");

  for (N = 32; N <= 32; N+= 32)
  {
    start = clock();
    result = calculate_gravitational_potential(N);
    end = clock();
    time_taken = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%9d %20.8f %12.6f\n", N, result[N/2][N/2][N/2], time_taken);
    free_cube(result, N);
  }

  while (should_stop)
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

double*** calculate_gravitational_potential(int N)
{
  double*** sigma_lmn,
        *** sigma_imn,
        *** sigma_ijn,
        *** sigma_ijk,
        *** psi_ijk,
        *** psi_ijn,
        *** psi_imn,
        *** psi_lmn;

  double** Sn = MakeSN(N);

  double result = 0;
  int i, j, k;


  sigma_lmn = create_smooth_sigma_cube(N);

  sigma_imn = to_sigma_imn(sigma_lmn, Sn, N); 
  free_cube(sigma_lmn, N);

  sigma_ijn = to_sigma_ijn(sigma_imn, Sn, N);
  free_cube(sigma_imn, N);

  sigma_ijk = to_sigma_ijk(sigma_ijn, Sn, N);
  free_cube(sigma_ijn, N);

  psi_ijk   = to_psi_ijk(sigma_ijk, N);
  free_cube(sigma_ijk, N);

  for (i = 1; i < N; i++) 
    for (j = 1; j < N; j++)
      for (k = 1; k < N; k++)
        result += psi_ijk[i][j][k] *sin(i*PI*1)*sin(j*PI*1)*sin(k*PI*1);
  //printf("Result = %20.10f\n", result);
        

  psi_ijn = to_sigma_ijk(psi_ijk, Sn, N);
  free_cube(psi_ijk, N);

  psi_imn = to_sigma_ijn(psi_ijn, Sn, N);
  free_cube(psi_ijn, N);

  psi_lmn = to_sigma_imn(psi_imn, Sn, N);
  //print_cube(psi_lmn, N);
  free_cube(psi_imn, N);

  free_matrix(Sn);
  return psi_lmn;
}

