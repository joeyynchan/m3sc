#include <stdlib.h>
#include <complex.h>
#include <math.h>

/* Function Declaration */
void FastSINE(double* rx, double* ry,int N);

/* Function Implementation */
void FastSINE(double* rx, double* ry,int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  complex double *Wp = MakeWpowers(N);
  complex double *mem = (complex double*) calloc(2*N , sizeof(complex double));
  complex double *x  = (complex double*) calloc(N , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[N];
  for (i = 0; i < N/2; i++)
  {
  	x[i]     =  0 + rx[i]*I;
  	x[i+N/2] =  0 - rx[i]*I;
  }

  FastDFT(x, y, w, Wp, N, 1);

  for (i = 0; i < N; i++)
  	ry[i] = creal(y[i]);

  free(mem);
  free(Wp);
}