#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define PI 3.14159265359

/* Function Declaration */
void printInfo();
complex double* MakeWpowers(int N);
complex double** create_matrix(int row, int col);
void free_matrix(complex double** matrix);

void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);
complex double **matmul(complex double** m1,
	                    complex double** m2,
	                    int row1,
	                    int col1,
	                    int col2);


/* Function Implementation */
int main()
{
  /* Chan, Joey, JMCSC, ync12 */	
  int i, j, N = 8, skip = 1;
  printInfo();

  complex double *Wp = MakeWpowers(N);
  complex double *w  = (complex double*) calloc(2*N, sizeof(complex double));
  complex double *x  = (complex double*) calloc(  N, sizeof(complex double));
  complex double *y  = (complex double*) calloc(  N, sizeof(complex double));
  for (i = 0; i < N; i++)
  	y[i] =  1.*i+1. + 0.*I;

  //y[0] = 1. + 0*I;
  //y[1] = 2. + 0*I;
  //y[2] = 3. + 0*I;
  //y[3] = 4. + 0*I;

  FastDFS(x, y, w, Wp, N, skip);
  for (i = 0; i < N; i++)
  	printf("x[%d] = %10.8f + %10.8fi\n", i, creal(x[i]), cimag(x[i]));

  free(w);
  free(Wp);
  free(x);
  free(y);
}


void printInfo()
{
  /* Chan, Joey, JMCSC, ync12 */
  printf("\n");
  printf("%15s: %s\n", "Name", "Joey");
  printf("%15s: %s\n", "CID", "00730306");
  printf("%15s: %s\n", "LIBRARY NO", "0246734100");
  printf("%15s: %s\n", "Email Address", "ync12@ic.ac.uk");
  printf("%15s: %s\n", "Course Code", "JMCSC");
  printf("%15s: %s, %s \n", "Compile Time", __TIME__, __DATE__);
  printf("-------------------------------------------------\n");
}