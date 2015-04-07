#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define PI 3.14159265359

/* Function Declaration */
void printInfo();
complex double* MakeWpowers(int N);

void FastDFT(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);
void fdft(int N);


/* Function Implementation */
int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int N;
  printInfo();	

  for (N = 1; N <= 10; N++)
    fdft(N);

  return 0;
}

void fdft(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  complex double *Wp = MakeWpowers(N);
  complex double *mem = (complex double*) calloc(2*N , sizeof(complex double));
  complex double *x  = (complex double*) calloc(N , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[N];

  /* Dummy Vector Construction */
  for (i = 0; i < N; i++)
  	x[i] =  i+1. + 0.*I;

  /* Execute FDFT */
  FastDFT(x, y, w, Wp, N, 1);

  /* Output Result */
  printf("\nFastDFT (N = %d) :\n", N);
  printf("==================\n");
  for (i = 0; i < N; i++)
  	printf("y[%d] = %12.6f + %12.6fi\n", i, creal(y[i]), cimag(y[i]));

  /* Allocated Memory Destruction */
  free(mem);
  free(Wp);
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
