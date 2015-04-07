#include <stdlib.h>
#include <complex.h>
#include <math.h>

/* Function Declaration */
complex double* MakeWpowers(int N);
void FastDFT(complex double* y, complex double* x, complex double* w, complex double* Wp, int N, int skip);

/* Function Implementation */
void FastSINE1(double** S, double** T, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i,j;
  int M = 2*N;
  complex double *Wp = MakeWpowers(M);
  complex double *mem = (complex double*) calloc(2*M , sizeof(complex double));
  complex double *x  = (complex double*) calloc(M , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[M];

  /* Parallel FastSINE for every 2 columns */
  for (i = 1; i < N-1; i++)
  {
    x[0] = 0 + 0*I;
    x[N] = 0 + 0*I;
    for (j = 1; j < N; j++)
    {
      x[j]   =   S[j][i]*I;
      x[M-j] = - S[j][i]*I;
    }

    FastDFT(x, y, w, Wp, M, 1);

    for (j = 1; j < N; j++)
    {
       T[j][i] = creal(y[j])/2.;
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

  free(x);
  free(mem);
  free(Wp);
}

void FastSINE2(double** S, double** T, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i,j;
  int M = 2*N;
  complex double *Wp = MakeWpowers(M);
  complex double *mem = (complex double*) calloc(2*M , sizeof(complex double));
  complex double *x  = (complex double*) calloc(M , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[M];

  /* Parallel FastSINE for every 2 columns */
  for (i = 1; i < N; i++)
  {
    x[0] = 0 + 0*I;
    x[N] = 0 + 0*I;
    for (j = 1; j < N; j++)
    {
      x[j]   =   S[i][j]*I;
      x[M-j] = - S[i][j]*I;
    }

    FastDFT(x, y, w, Wp, M, 1);

    for (j = 1; j < N; j++)
    {
       T[i][j] = creal(y[j])/2.;
    }
  }

  free(x);
  free(mem);
  free(Wp);
}
