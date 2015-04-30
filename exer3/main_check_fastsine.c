#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>

#define PI                3.14159265359

/* Function Declarations */
void printInfo();

double **create_matrix(int, int);
void free_matrix(double**);
double **mymatmul(double**, double**, int, int, int);
double **MakeSN(int);

void FastSINE(double* rx, double* ry,int N);
int check_result(double** y1, double* y2, int N);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, N;
  double time_diff1 = 0;
  double time_diff2 = 0;
  clock_t start_time, end_time;
  double **x1, **y1, **Sn;
  double *x2, *y2;

  printInfo();

  printf("Enter N: ");
  scanf("%d", &N);

  x1 = create_matrix(N-1, 1);
  x2 = (double *)malloc(N*sizeof(double));
  y2 = (double *)malloc(N*sizeof(double));
  Sn = MakeSN(N);
  
  /* Vector S construction */
  for (i = 1; i < N; i++)
  {
    x1[i][1] = i;
    x2[i]  = i;
  }

  /* Time Direct Matrix Multiplication Method */
  start_time = clock();
  y1 = mymatmul(Sn, x1, N-1, N-1, 1);
  end_time = clock();
  time_diff1 = (double) (end_time - start_time);
  time_diff1 = (time_diff1 == 0) ? 1. : time_diff1;

  /* Time Fast Since Method */
  start_time = clock();
  FastSINE(x2, y2, N);
  end_time = clock();
  time_diff2 = (double) (end_time - start_time);
  time_diff2 = (time_diff2 == 0) ? 1. : time_diff2;

  /* Output Result */
  printf("N = %d\n", N);
  printf("Time taken for Matrix Multiplication (y1) = %12.6fs\n", time_diff1/CLOCKS_PER_SEC);
  printf("Time taken for Fast Sine Transform   (y2) = %12.6fs\n", time_diff2/CLOCKS_PER_SEC);
  printf("   i      2*y1[i]        y2[i]     %% Error \n");
  printf("------- ------------ ------------ ----------\n");
  /*
  for (i = 1; i < N; i++)
  {
  	printf("%7d ", i);
    printf("%12.6f ", y1[i][1]);
    printf("%12.6f", y2[i]);
  	printf("%10.5f\n", (y2[i]-y1[i][1])/y2[i]);
  }
  */
  /*check_result(y1, y2, N);*/

  /* Memory Desctruction */
  free_matrix(x1);
  free_matrix(y1);
  free_matrix(Sn);
  free(x2);
  free(y2);

  return 0;
}

int check_result(double** y1, double* y2, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  int result = 1;
  for (i = 1; i < N; i++)
  {

  	if (fabs((y1[i][1] - y2[i])/y2[i]) > 1e-3)
    {
      printf("y1[%d] = %12.6f\t", i+1, y1[i][1]);
  	  printf("y2[%d] = %12.6f\t", i, y2[i]);
  	  printf("Percentage Error = %g\n", (y2[i]-y1[i][1])/y2[i]);
      result = 0;
      break;
    }
  }
  return result;
}

