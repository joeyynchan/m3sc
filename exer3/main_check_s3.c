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
complex double **matmul(complex double** m1,
	                    complex double** m2,
	                    int row1,
	                    int col1,
	                    int col2);

void fdfs(int N);
void generate_y(complex double* y, int N);

/* Function Implementation */
int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int N;
  printInfo();	

  N = 64;
  fdfs(N);

  return 0;
}

void fdfs(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  complex double *Wp = MakeWpowers(N);
  complex double *x  = (complex double*) calloc(N , sizeof(complex double));
  complex double *y  = (complex double*) calloc(N , sizeof(complex double));
  complex double *w = (complex double*) calloc(2*N , sizeof(complex double));

  generate_y(y, N);
  FastDFS(x, y, w, Wp, N, 1);

  printf("\nFastDFS (N = %d) :\n", N);
  printf("==================\n");
  for (i = 0; i < N; i++)
  	printf("x[%d] = %12.6f + %12.6fi\n", i, creal(x[i]), cimag(x[i]));

  free(x);
  free(y);
  free(w);
  free(Wp);
}

void generate_y(complex double* y, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  complex double* Wp = MakeWpowers(N);

  int i, j;
  for (i = 0; i < N; i++)
  {
    complex double temp = 0;
    for (j = 0; j < N; j++)
        temp += Wp[(N-(i*j%N))%N] * (double)(j+1);
    y[i] = temp/N;
  }        
}
