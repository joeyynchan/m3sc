#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);


void FastDFS(complex double* x,
             complex double* y,
             complex double* w, /* Intermediate Result of size N */
             complex double* Wp,
             int N,
             int skip)
{
  if (N % 2 != 0)       /* N odd */
  {
    if (N == 1)           /* Case N = 1, x := y */
      x[0] = y[0];
    else                  /* Case N != 1 */
    {
      int i, j;
      for (i = 0; i < N; i++)
      {
        complex double temp = 0. + I*0.;
        for (j = 0; j < N; j++)
          if (i == 0 || j == 0)
            temp += y[j*skip];
          else
            temp += Wp[skip*(j*i%N)]*y[j*skip];
        x[i] = temp;
      }
    }
  } 
  else                  /* N even */
  { 
    int j;
    complex double* xe = w;
    complex double* xo = w + N/2;
    complex double* we = w + N/2;
    complex double* wo = w + N;

    /* Divide the problems into two sub problems */
    FastDFS(xe, y     , we, Wp, N/2, 2*skip);      /* First half: even part */
    FastDFS(xo, y+skip, wo, Wp, N/2, 2*skip);      /* Second half: odd part */
    
    /* Compute the final result from the two sub result */
    for (j = 0; j < N/2; j++)
    { 
      if (j == 0)
      {
        x[0]   = xe[0] + xo[0];
        x[N/2] = xe[0] - xo[0];
      }
      else
      {
        x[j] = xe[j] + Wp[skip*j] * xo[j];
        x[j+N/2] = xe[j] + Wp[skip*(N/2+j)] * xo[j];
      }
    }

  }
}
