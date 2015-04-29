#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

/* Function Declaration */

/* MakeWpowers.c */
complex double* MakeWpowers(int N);
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

  printf(" log2(N)   FastFDS      Trad.    Ratio \n");
  printf("--------- ---------- ---------- -------\n");
  N = 2;
  for (i = 2; i <= 25; i++)
  {
    r1 = fdfs(N);
    //r2 = execute_traditional(N);
    printf("%9d %10.6f %10.6f %7.2f\n", i, r1, r2, r2/r1);
    N *= 2;
  }

  return 0;
}

double fdfs(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  double time_diff = 0;
  clock_t start_time, end_time;
  complex double *Wp = MakeWpowers(N);
  complex double *mem = (complex double*) calloc(2*N , sizeof(complex double));
  complex double *y  = (complex double*) calloc(N , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *x  = &mem[N];

  /* Dummy Vector Construction */
  for (i = 0; i < N; i++)
  	y[i] =  i+1. + 0.*I;

  /* Time FDFS */
  start_time = clock();
  FastDFS(x, y, w, Wp, N, 1);
  end_time = clock();
  time_diff = (double) (end_time - start_time);
  time_diff = (time_diff == 0) ? 1. : time_diff;

  /* Allocated Memory Destruction */
  free(mem);
  free(Wp);

  return time_diff/CLOCKS_PER_SEC;
}

double execute_traditional(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  double time_diff = 0;
  clock_t start_time, end_time;
  complex double** y  = create_matrix(N, 1);
  complex double** Cn = create_matrix(N, N);
  complex double** x;
  double theta = 2.*PI/N;
  
  /* Dummy Matrix Construction */
  int i, j;
  for (i = 1; i <= N; i++)
  	y[i][1] = i + 0*I;

  for (i = 1; i <= N; i++)
  	for (j = 1; j <= N; j++)
  	  Cn[i][j] = cos(theta*(i-1)*(j-1)) + I*sin(theta*(i-1)*(j-1));

  /* Time Direct Matrix Multiplication Method */
  start_time = clock();
  x = matmul(Cn, y, N, N, 1);
  end_time = clock();
  time_diff = (double) (end_time - start_time);
  time_diff = (time_diff == 0) ? 1. : time_diff;

  /* Allocated Memory Destruction */
  free_matrix(x);
  free_matrix(y);
  free_matrix(Cn);

  return time_diff/CLOCKS_PER_SEC;
}
