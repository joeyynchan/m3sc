#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

double **create_sigma_matrix(int);
double **create_smooth_sigma_matrix(int);
double **MakeSN(int);
double **mymatmul(double** m1, double** m2, int row1, int col1, int col2);
double **calculate_gravitational_potential(int);
void free_matrix(double**);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int m, n, N = 192;
  clock_t start_time, end_time;
  double ** result, time_diff;
  //printf("  x     y          Result      \n");
  //printf("----- ----- -------------------\n");

  start_time = clock();
  result = calculate_gravitational_potential(N);
  end_time = clock();
  time_diff = (double) (end_time - start_time);
  time_diff = (time_diff == 0) ? 1. : time_diff;
  
  /*
  for (m = 1; m < N; m++)
  {
    //printf("%5d %5d ", m, N/2);
    printf("%20.8f\n", m/(double)N);  	
  }
  printf("\n\n\n\n\n\n");
  for (m = 1; m < N; m++)
  {
    //printf("%5d %5d ", m, N/2);
    printf("%20.8f\n", result[m][N/2]);  	
  }
  printf("\n\n\n\n\n\n");
  for (m = 1; m < N; m++)
  {
    //printf("%5d %5d ", N/2, m);
    printf("%20.8f\n", result[N/2][m]);   
  }*/
  
  
  
  printf("%10s ", "");
  for (m = 1; m < N; m++)
    printf("%10.6f ", m/(double) N);
  printf("\n");
  
  for (m = 1; m < N; m++)
  {
    printf("%10.6f ", m/(double)N);
    for (n = 1; n < N; n++)
	  printf("%10.6f ", result[m][n]);
	printf("\n");
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

