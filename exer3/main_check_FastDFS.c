#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define PI 3.14159265359

/* Function Declaration */
void printInfo();
complex double* MakeWpowers(int N);
void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);

complex double** create_matrix(int row, int col);
void free_matrix(complex double** matrix);
complex double **matmul(complex double** m1, complex double** m2, int row1, int col1, int col2);

void fdfs(int N, int skip);
void execute_traditional(int N);
void generate_y(complex double* y, int N, int skip);

/* Function Implementation */
int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int N, skip;
  printInfo();	

  printf("Enter N and skip:");
  scanf("%d %d", &N, &skip);

  fdfs(N, skip);
  /*execute_traditional(N); */

  return 0;
}

void fdfs(int N, int skip)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  complex double *Wp = MakeWpowers(N);
  complex double *w  = (complex double*) malloc(2*N    * sizeof(complex double));
  complex double *y  = (complex double*) malloc(N*skip * sizeof(complex double));
  complex double *x  = (complex double*) malloc(N*skip * sizeof(complex double));

  for (i = 0; i < N; i++)
  	y[skip*i] =  i+1. + 0.*I;

  generate_y(y, N, skip);
  FastDFS(x, y, w, Wp, N, skip);

  printf("\nFastDFS (N = %d) :\n", N);
  printf("==================\n");
  for (i = 0; i < N*skip; i++)
  	printf("x[%3d] = %12.6f + %12.6fi\n", i, creal(x[i]), cimag(x[i]));

  free(x);
  free(y);
  free(w);
  free(Wp);
}

void execute_traditional(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  complex double** y  = create_matrix(N, 1);
  complex double** Cn = create_matrix(N, N);
  complex double** x;
  double theta = 2.*PI/N;
  
  int i, j;
  for (i = 1; i <= N; i++)
  	y[i][1] = i + 0*I;

  
  for (i = 1; i <= N; i++)
  	for (j = 1; j <= N; j++)
  	  Cn[i][j] = cos(theta*(i-1)*(j-1)) + I*sin(theta*(i-1)*(j-1));

  x = matmul(Cn, y, N, N, 1);

  printf("\nTraditional way (N = %d) :\n", N);
  printf("==================\n");
  for (i = 1; i <= N; i++)
  	printf("x[%3d] = %12.6f + %12.6fi\n", i, creal(x[i][1]), cimag(x[i][1]));

  free_matrix(x);
  free_matrix(y);
  free_matrix(Cn);
}

void generate_y(complex double* y, int N, int skip)
{
  /* Chan, Joey, JMCSC, ync12 */
  complex double* Wp = MakeWpowers(N);

  int i, j;
  for (i = 0; i < N*skip; i++)
    y[i] = 0 + 0*I;

  for (i = 0; i < N; i++)
  {
    complex double temp = 0;
    for (j = 0; j < N; j++)
        temp += Wp[(N-(i*j%N))%N] * (double)(j+1);
    y[i*skip] = temp/N;
  }        
}
