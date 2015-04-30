#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

/* Function Declaration */

/* MakeWpowers.c */
complex double* MakeWpowers(int N);
int bmod(int i, int j, int N);
void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);

/* MatMul.c */
complex double** create_matrix(int row, int col);
void free_matrix(complex double** matrix);
complex double **matmul(complex double** m1,
	                    complex double** m2,
	                    int row1,
	                    int col1,
	                    int col2);

/* Local */
void printInfo();
double fdfs(int N);
double execute_traditional(int N);

/* Function Implementation */
int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, N;
  double r1, r2;
  printInfo();	

  printf(" log2(N)     FastFDS        Trad.     Ratio \n");
  printf("--------- ------------ ------------ ---------\n");
  N = 2;
  for (i = 2; i <= 20; i++)
  {
    r1 = fdfs(N);
    r2 = execute_traditional(N);
    printf("%9d %12.4e %12.4e %9.2f\n", i, r1, r2, r2/r1);
    N *= 2;
  }

  return 0;
}

double fdfs(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, count = 0;
  double time_diff = 0;
  clock_t start_time, end_time;
  complex double *Wp = MakeWpowers(N);
  complex double *w  = (complex double*) malloc(2*N * sizeof(complex double));
  complex double *x  = (complex double*) malloc(N   * sizeof(complex double));
  complex double *y  = (complex double*) malloc(N   * sizeof(complex double));

  /* Dummy Vector Construction */
  for (i = 0; i < N; i++)
  	y[i] =  i+1. + 0.*I;

  /* Time FDFS */
  start_time = clock();
  do
  {
    FastDFS(x, y, w, Wp, N, 1);
    end_time = clock();
    time_diff = (double) (end_time - start_time);
    count++;
  } while (time_diff == 0);

  /* Allocated Memory Destruction */
  free(w);
  free(x);
  free(y);
  free(Wp);

  return time_diff/(CLOCKS_PER_SEC*count);
}

double execute_traditional(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, count = 0;
  double time_diff = 0;
  clock_t start_time, end_time;
  complex double* x  = (complex double*) malloc (N*sizeof(complex double));
  complex double* y  = (complex double*) malloc (N*sizeof(complex double));
  complex double* Cn = MakeWpowers(N);
  
  /* Dummy Matrix Construction */
  for (i = 0; i < N; i++)
  	y[i] = i+1. + 0*I;


  /* Time Direct Matrix Multiplication Method */
  start_time = clock();
  do
  {
    for (i = 0; i < N; i++)
    {
      complex double temp = 0. + I*0.;
      for (j = 0; j < N; j++)
      {
        int index = i*j%N > 0 ? i*j%N : i*j%N+N;
        temp += Cn[index]*y[j];
      }
      x[i] = temp;
    }

    end_time = clock();
    time_diff = (double) (end_time - start_time);
    count++;
  } while (time_diff == 0);

  /* Allocated Memory Destruction */
  free(x);
  free(y);
  free(Cn);

  return time_diff/(CLOCKS_PER_SEC*count);
}

int bmod(int i, int j, int N)
{
  if (j == 1)
    return i%N;
  else if (j%2 == 0)
    return bmod(2*bmod (i, j/2, N), 1, N);
  else 
    return bmod(2*i*bmod(i, j/2, N), 1, N);
}

