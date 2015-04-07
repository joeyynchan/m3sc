#include <stdlib.h>
#include <complex.h>
#include <math.h>

/* Function Declaration */
complex double* MakeWpowers(int N);
void FastSINE(double* rx, double* ry,int N);
void FastDFT(complex double* y, complex double* x, complex double* w, complex double* Wp, int N, int skip);

/* Function Implementation */
void FastSINE(double* rx, double* ry,int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  int M = 2*N;
  complex double *Wp = MakeWpowers(M);
  complex double *mem = (complex double*) calloc(2*M , sizeof(complex double));
  complex double *x  = (complex double*) calloc(M , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[M];
  x[0] = 0 + 0*I;
  x[N] = 0 + 0*I;
  for (i = 1; i < N; i++)
  {
  	x[i]   =  0 + rx[i]*I;
  	x[M-i] =  0 - rx[i]*I;
  }

  FastDFT(x, y, w, Wp, M, 1);

  for (i = 1; i < N; i++)
  	ry[i] = creal(y[i])/2.;

  free(x);
  free(mem);
  free(Wp);
}
