#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

#define SIN120 = +0.86602540378
#define COS120 = -0.5
#define SIN72  = +0.95105651629
#define COS72  = +0.30901699437
#define SIN144 = +0.58778525229
#define COS144 = -0.80901699437

void FastTransform(complex double* x, /* Output result */
                   complex double* y, /* Input data */
                   complex double* w, /* Intermediate Result of size N */
                   complex double* Wp,
                   int N,
                   int skipY,
                   int skipX,
                   int reverse)
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
          if (reverse)
            temp += Wp[skipX*((N-j*i%N)%N)]*y[j*skipY];
          else
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
    FastTransform(xe, y      , we, Wp, N/2, 2*skipY, 2*skipX, reverse);      /* First half: even part */
    FastTransform(xo, y+skipY, wo, Wp, N/2, 2*skipY, 2*skipX, reverse);      /* Second half: odd part */
    
    /* Compute the final result from the two sub result */
    for (j = 0; j < N/2; j++)
    { 
      if (reverse)
      {
        x[j] = xe[j] + Wp[skipX*((N-j)%N)] * xo[j];
        x[j+N/2] = xe[j] + Wp[skipX*(N/2-j)] * xo[j];
      }
      else
      {
        x[j] = xe[j] + Wp[skipX*j] * xo[j];
        x[j+N/2] = xe[j] + Wp[skipX*(N/2+j)] * xo[j];
      }
    }

  }
}
