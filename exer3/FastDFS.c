#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);
void FastTransform(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skipY, int skipX);

void FastDFS(complex double* x, /* Output result */
             complex double* y, /* Input data */
             complex double* w, /* Intermediate Result of size N */
             complex double* Wp,
             int N,
             int skip)
{
  int i;
  FastTransform(w+N, y, w, Wp, N, skip, 1);
  for (i = 0; i < N; i++)
    x[i*skip] = w[N+i];
}

void FastTransform(complex double* x, /* Output result */
                   complex double* y, /* Input data */
                   complex double* w, /* Intermediate Result of size N */
                   complex double* Wp,
                   int N,
                   int skipY,
                   int skipX)
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
          temp += Wp[skipX*(j*i%N)]*y[j*skipY];
        x[i] = temp;
      }
  	}
  } 
  else                  /* N even */
  { 
    int j;
    complex double* xe  = w;
    complex double* xo  = w + N/2;
    complex double* we  = w + N/2;
    complex double* wo  = w + N;

    /* Divide the problems into two sub problems */
    FastTransform(xe, y     , we, Wp, N/2, 2*skipY, 2*skipX);      /* First half: even part */
    FastTransform(xo, y+skipY, wo, Wp, N/2, 2*skipY, 2*skipX);      /* Second half: odd part */
    
    /* Compute the final result from the two sub result */
    for (j = 0; j < N/2; j++)
    { 
      x[j] = xe[j] + Wp[skipX*j] * xo[j];
      x[j+N/2] = xe[j] + Wp[skipX*(N/2+j)] * xo[j];
    }

  }
}
