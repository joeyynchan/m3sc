#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);


void FastDFS(complex double* x,
             complex double* y,
             complex double* w,
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
          temp += Wp[skip*(j*i%N)]*y[j*skip];
        x[i] = temp;
      }
  	}
  } 
  else                  /* N even */
  { 
    int i, j;
    complex double* xe = w;
    complex double* xo = w + N/2;
    complex double* we = w + N/2;
    complex double* wo = w + N;

    /* Divide the problems into two sub problems */
    FastDFS(xe, y     , we, Wp, N/2, 2*skip);      /* First half: even part */
    FastDFS(xo, y+skip, wo, Wp, N/2, 2*skip);      /* Second half: odd part */

    for (i = 0; i < N/2; i++)
      printf("xe[%d] = %10.6f + %10.6fi\n", i, creal(xe[i]), cimag(xe[i]));

    for (i = 0; i < N/2; i++)
      printf("xo[%d] = %10.6f + %10.6fi\n", i, creal(xo[i]), cimag(xo[i]));
    printf("\n\n\n");
    
    /* Compute the final result from the two sub result */
    for (j = 0; j < N/2; j++)     /* First half */
      x[j] = xe[j] + Wp[skip*j] * xo[j];

    for (j = 0; j < N/2; j++)     /* Second half */
      x[j+N/2] = xe[j] + Wp[skip*(N/2+j)] * xo[j];

  }
}