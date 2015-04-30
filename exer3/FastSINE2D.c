#include <stdlib.h>
#include <complex.h>
#include <math.h>

/* Function Declaration */
complex double* MakeWpowers(int N);
void FastDFT(complex double* y, complex double* x, complex double* w, complex double* Wp, int N, int skip);

/* Function Implementation */
void FastSINE1(double** S, double** T, complex double* Wp, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i,j;
  int M = 2*N;
  complex double *w = (complex double*) malloc(2*M * sizeof(complex double));
  complex double *x = (complex double*) malloc(  M * sizeof(complex double));
  complex double *y = (complex double*) malloc(  M * sizeof(complex double));

  /* Parallel FastSINE for every 2 columns */
  for (i = 1; i < N-1; i+=2)
  {
    x[0] = 0 + 0*I;
    x[N] = 0 + 0*I;
    for (j = 1; j < N; j++)
    {
      x[j]   = -S[j][i] + S[j][i+1]*I;
      x[M-j] =  S[j][i] - S[j][i+1]*I;
    }

    FastDFT(x, y, w, Wp, M, 1);

    for (j = 1; j < N; j++)
    {
       T[j][i]   = cimag(y[j])/2.;
       T[j][i+1] = creal(y[j])/2.;
    }
  }

  for (j = 1; j < N; j++)
  {
    x[j]   =   S[j][N-1]*I;
    x[M-j] = - S[j][N-1]*I;
  }

  FastDFT(x, y, w, Wp, M, 1);

  for (j = 1; j < N; j++)
  {
     T[j][N-1] = creal(y[j])/2.;
  }

  free(w);
  free(x);
  free(y);
}

void FastSINE2(double** S, double** T, complex double* Wp, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i,j;
  int M = 2*N;
  complex double *w = (complex double*) malloc(2*M * sizeof(complex double));
  complex double *x = (complex double*) malloc(  M * sizeof(complex double));
  complex double *y = (complex double*) malloc(  M * sizeof(complex double));

  /* Parallel FastSINE for every 2 rows */
  for (i = 1; i < N-1; i+=2)
  {
    x[0] = 0 + 0*I;
    x[N] = 0 + 0*I;
    for (j = 1; j < N; j++)
    {
      x[j]   = -S[i][j] + S[i+1][j]*I;
      x[M-j] =  S[i][j] - S[i+1][j]*I;
    }

    FastDFT(x, y, w, Wp, M, 1);

    for (j = 1; j < N; j++)
    {
       T[i][j]   = cimag(y[j])/2.;
       T[i+1][j] = creal(y[j])/2.;
    }
  }

  for (j = 1; j < N; j++)
  {
    x[j]   =   S[N-1][j]*I;
    x[M-j] = - S[N-1][j]*I;
  }

  FastDFT(x, y, w, Wp, M, 1);

  for (j = 1; j < N; j++)
  {
     T[N-1][j] = creal(y[j])/2.;
  }

  free(w);
  free(x);
  free(y);
}
