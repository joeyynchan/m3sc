#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define PI 3.14159265359

/* Function Declaration */
void printInfo();
complex double* MakeWpowers(int N);
void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);
void FastDFT(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);

complex double** create_matrix(int row, int col);
void free_matrix(complex double** matrix);
complex double **matmul(complex double** m1,
	                    complex double** m2,
	                    int row1,
	                    int col1,
	                    int col2);

void fdfs(int N);
void fdft(int N);
void execute_traditional(int N);


/* Function Implementation */
int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int N;
  printInfo();	

  N = 5;
  fdfs(N);
  execute_traditional(N);

  return 0;
}

void fdfs(int N)
{
  int i;
  /* LZ algorithm */
  complex double *Wp = MakeWpowers(N);
  complex double *mem = (complex double*) calloc(2*N , sizeof(complex double));
  complex double *y  = (complex double*) calloc(N , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *x  = &mem[N];
  for (i = 0; i < N; i++)
  	y[i] =  i+1. + 0.*I;

  FastDFS(x, y, w, Wp, N, 1);

  printf("\nFastDFS (N = %d) :\n", N);
  printf("==================\n");
  for (i = 0; i < N; i++)
  	printf("x[%d] = %12.6f + %12.6fi\n", i, creal(x[i]), cimag(x[i]));

  /*
  for (i = 0; i < 3*N; i++)
   	printf("w[%2d] = %10.6f + %10.6fi\n", i, creal(w[i]), cimag(w[i]));
  */

  free(mem);
  free(Wp);
}

void fdft(int N)
{
  int i;
  /* LZ algorithm */
  complex double *Wp = MakeWpowers(N);
  complex double *mem = (complex double*) calloc(2*N , sizeof(complex double));
  complex double *x  = (complex double*) calloc(N , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[N];
  for (i = 0; i < N; i++)
  	x[i] =  i+1. + 0.*I;

  FastDFT(x, y, w, Wp, N, 1);

  printf("\nFastDFT (N = %d) :\n", N);
  printf("==================\n");
  for (i = 0; i < N; i++)
  	printf("y[%d] = %12.6f + %12.6fi\n", i, creal(y[i]), cimag(y[i]));

  free(mem);
  free(Wp);
}

void execute_traditional(int N)
{
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
  	printf("x[%d] = %12.6f + %12.6fi\n", i, creal(x[i][1]), cimag(x[i][1]));

  free_matrix(x);
  free_matrix(y);
  free_matrix(Cn);
}
