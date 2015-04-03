#include <stdlib.h>
#include <complex.h>

void FastDFT(complex double* y, complex double* x, complex double* w, complex double* Wp, int N, int skip);


void FastDFT(complex double* x,  /* Input vector */
             complex double* y,  /* Final result */
             complex double* w,  /* Intermediate result of size N */
             complex double* Wp, /* List of power of W */
             int N,
             int skip)
{
  if (N % 2 != 0)       /* N odd */
  {
  	if (N == 1)           /* Case N = 1, x := y */
  	  y[0] = x[0];
  	else                  /* Case N != 1 */
  	{
      int i, j;
      for (i = 0; i < N; i++)
      {
      	complex double temp = 0. + I*0.;
        for (j = 0; j < N; j++)
          temp += Wp[skip*((N-j*i%N)%N)]*x[j*skip];
        y[i] = temp;
      }
  	}
  } 
  else                  /* N even */
  { 
    int j;
    complex double* ye = w;
    complex double* yo = w + N/2;
    complex double* we = w + N/2;
    complex double* wo = w + N;

    /* Divide the problems into two sub problems */
    FastDFT(x     , ye, we, Wp, N/2, 2*skip);      /* First half: even part */
    FastDFT(x+skip, yo, wo, Wp, N/2, 2*skip);      /* Second half: odd part */
    
    /* Compute the final result from the two sub result */
    for (j = 0; j < N/2; j++)     /* First half */
      y[j] = ye[j] + Wp[skip*((N-j)%N)] * yo[j];

    for (j = 0; j < N/2; j++)     /* Second half */
      y[j+N/2] = ye[j] + Wp[skip*(N/2-j)] * yo[j];

  }
}
