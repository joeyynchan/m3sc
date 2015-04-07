#include <stdlib.h>
#include <complex.h>
#include <math.h>

/* Function Declaration */
complex double* MakeWpowers(int N);
void FastDFT(complex double* y, complex double* x, complex double* w, complex double* Wp, int N, int skip);

/* Function Implementation */
void FastSINE1(double*** S, double*** T, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  int M = 2*N;
  complex double *Wp = MakeWpowers(M);
  complex double *mem = (complex double*) calloc(2*M , sizeof(complex double));
  complex double *x  = (complex double*) calloc(M , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[M];

  /* Parallel FastSINE in x axis */
  for (k = 1; k < N; k++)
  {
     for (i = 1; i < N-1; i+=2)
    {
      x[0] = 0 + 0*I;
      x[N] = 0 + 0*I;
      for (j = 1; j < N; j++)
      {
        x[j]   = -S[j][i][k] + S[j][i+1][k]*I;
        x[M-j] =  S[j][i][k] - S[j][i+1][k]*I;
      }

      FastDFT(x, y, w, Wp, M, 1);

      for (j = 1; j < N; j++)
      {
         T[j][i][k]   = cimag(y[j])/2.;
         T[j][i+1][k] = creal(y[j])/2.;
      }
    }
  }

  free(x);
  free(mem);
  free(Wp);
}

void FastSINE2(double*** S, double*** T, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  int M = 2*N;
  complex double *Wp = MakeWpowers(M);
  complex double *mem = (complex double*) calloc(2*M , sizeof(complex double));
  complex double *x  = (complex double*) calloc(M , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[M];

  /* Parallel FastSINE in y axis */
  for (k = 1; k < N; k++)
  {
  	 for (i = 1; i < N-1; i+=2)
     {
      x[0] = 0 + 0*I;
      x[N] = 0 + 0*I;
      for (j = 1; j < N; j++)
      {
        x[j]   = -S[i][j][k] + S[i+1][j][k]*I;
        x[M-j] =  S[i][j][k] - S[i+1][j][k]*I;
      }

      FastDFT(x, y, w, Wp, M, 1);

      for (j = 1; j < N; j++)
      {
         T[i][j][k]   = cimag(y[j])/2.;
         T[i+1][j][k] = creal(y[j])/2.;
      }
    }

    for (j = 1; j < N; j++)
    {
      x[j]   =   S[N-1][j][k]*I;
      x[M-j] = - S[N-1][j][k]*I;
    }

    FastDFT(x, y, w, Wp, M, 1);

    for (j = 1; j < N; j++)
    {
       T[N-1][j][k] = creal(y[j])/2.;
    }
  }

  free(x);
  free(mem);
  free(Wp);
}


void FastSINE3(double*** S, double*** T, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  int M = 2*N;
  complex double *Wp = MakeWpowers(M);
  complex double *mem = (complex double*) calloc(2*M , sizeof(complex double));
  complex double *x  = (complex double*) calloc(M , sizeof(complex double));
  complex double *w  = &mem[0];
  complex double *y  = &mem[M];

  /* Parallel FastSINE in z axis */
  for (k = 1; k < N; k++)
  {
  	 for (i = 1; i < N-1; i+=2)
     {
      x[0] = 0 + 0*I;
      x[N] = 0 + 0*I;
      for (j = 1; j < N; j++)
      {
        x[j]   = -S[k][i][j] + S[k][i+1][j]*I;
        x[M-j] =  S[k][i][j] - S[k][i+1][j]*I;
      }

      FastDFT(x, y, w, Wp, M, 1);

      for (j = 1; j < N; j++)
      {
         T[k][i][j]   = cimag(y[j])/2.;
         T[k][i+1][j] = creal(y[j])/2.;
      }
    }

    for (j = 1; j < N; j++)
    {
      x[j]   =   S[k][N-1][j]*I;
      x[M-j] = - S[k][N-1][j]*I;
    }

    FastDFT(x, y, w, Wp, M, 1);

    for (j = 1; j < N; j++)
    {
       T[k][N-1][j] = creal(y[j])/2.;
    }
  }

  free(x);
  free(mem);
  free(Wp);
}


