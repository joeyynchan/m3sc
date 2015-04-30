#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

#define SIN120  0.86602540378
#define COS120  -0.5
#define SIN72   0.95105651629
#define COS72   0.30901699437
#define SIN144  0.58778525229
#define COS144  0.80901699437

void FastTransform(complex double* x, /* Output result */
                   complex double* y, /* Input data */
                   complex double* w, /* Intermediate Result of size N */
                   complex double* Wp,
                   int N,
                   int skipY,
                   int skipX,
                   int reverse)
{
  if (N % 2 != 0)         /* N odd */
  {
  	if (N == 1)           /* Case N = 1, x := y */
  	  x[0] = y[0];
    else if (N == 3)
    {
      complex double Re, Im;
      Re = COS120*((creal(y[  skipY])+creal(y[2*skipY])) + I*(cimag(y[skipY])+cimag(y[2*skipY])));
      Im = SIN120*((cimag(y[2*skipY])-cimag(y[  skipY])) + I*(creal(y[skipY])-creal(y[2*skipY])));
      x[0] = y[0] + y[skipY] + y[2*skipY]; 
      x[reverse? 2 : 1] = y[0] + Re + Im;
      x[reverse? 1 : 2] = y[0] + Re - Im;
    }
  	else                  /* Case N != 1 */
  	{
      int i, j;
      for (i = 0; i < N; i++)
      {
      	complex double temp = y[0];
        for (j = 1; j < N; j++)
          temp += reverse ? Wp[skipX*((N-j*i%N)%N)]*y[j*skipY] : Wp[skipX*(j*i%N)]*y[j*skipY];
        x[i] = temp;
      }
  	}
  } 
  else                  /* N even */
  { 
    int j;
    complex double temp;
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
      if (j == 0)
        temp = xo[j];
      else if (j == N/4 && N%4 == 0)
        temp = reverse ? cimag(xo[j]) - I*creal(xo[j]) : -cimag(xo[j]) + I*creal(xo[j]);
      else
        temp = reverse ? Wp[skipX*((N-j)%N)] * xo[j] : Wp[skipX*j] * xo[j];
      x[j] = xe[j] + temp;
      x[j+N/2] = xe[j] - temp;
    }
  }
}

