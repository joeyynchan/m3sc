#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

#define SIN120  0.86602540378
#define COS120  -0.5
#define SIN72   0.95105651629
#define COS72   0.30901699437
#define SIN144  0.58778525229
#define COS144  -0.80901699437

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
      Re = COS120 * ((creal(y[  skipY])+creal(y[2*skipY])) + I*(cimag(y[skipY])+cimag(y[2*skipY])));
      Im = SIN120 * ((cimag(y[2*skipY])-cimag(y[  skipY])) + I*(creal(y[skipY])-creal(y[2*skipY])));
      x[0] = y[0] + y[skipY] + y[2*skipY]; 
      x[reverse? 2 : 1] = y[0] + Re + Im;
      x[reverse? 1 : 2] = y[0] + Re - Im;
    }
    else if (N==5)
    {
      complex double u, v, p, q;
      complex double uCOS72, uCOS144,
                     vSIN72, vSIN144,
                     pCOS72, pCOS144,
                     qSIN72, qSIN144;
      u = ((creal(y[  skipY])+creal(y[4*skipY])) + I*(cimag(y[  skipY])+cimag(y[4*skipY])));
      v = ((cimag(y[4*skipY])-cimag(y[  skipY])) + I*(creal(y[  skipY])-creal(y[4*skipY])));
      p = ((creal(y[2*skipY])+creal(y[3*skipY])) + I*(cimag(y[2*skipY])+cimag(y[3*skipY])));
      q = ((cimag(y[3*skipY])-cimag(y[2*skipY])) + I*(creal(y[2*skipY])-creal(y[3*skipY])));

      uCOS72  = u * COS72;
      uCOS144 = u * COS144;
      vSIN72  = v * SIN72;
      vSIN144 = v * SIN144;
      pCOS72  = p * COS72;
      pCOS144 = p * COS144;
      qSIN72  = q * SIN72;
      qSIN144 = q * SIN144;

      x[0] = y[0] + y[skipY] + y[2*skipY] + y[3*skipY] + y[4*skipY];
      x[reverse? 4 : 1] = y[0] + uCOS72  + vSIN72  + pCOS144 + qSIN144;
      x[reverse? 3 : 2] = y[0] + uCOS144 + vSIN144 + pCOS72  - qSIN72;
      x[reverse? 2 : 3] = y[0] + uCOS144 - vSIN144 + pCOS72  + qSIN72;
      x[reverse? 1 : 4] = y[0] + uCOS72  - vSIN72  + pCOS144 - qSIN144;
    }
  	else                  /* Case N != 1 */
  	{
      int i, j;
      for (i = 0; i < N; i++)
      {
      	complex double temp = y[0];
        for (j = 1; j < N; j++)
          /*temp += reverse? creal(Wp[skipX*(j*i%N)])*y[j*skipY] + cimag(Wp[skipX*(j*i%N)])*(cimag(y[j*skipY])-I*creal((y[j*skipY]))) :
                         creal(Wp[skipX*(j*i%N)])*y[j*skipY] - cimag(Wp[skipX*(j*i%N)])*(cimag(y[j*skipY])-I*creal((y[j*skipY]))) ;*/
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
      {
        x[j] = xe[j] + xo[j];
        x[j+N/2] = xe[j] - xo[j];
      }
      else
      {
        if (j == N/4 && N%4 == 0)
          temp = reverse ? cimag(xo[j]) - I*creal(xo[j]) : -cimag(xo[j]) + I*creal(xo[j]);
        else
          /*temp = reverse? creal(Wp[skipX*j])*xo[j] + cimag(Wp[skipX*j])*(cimag(xo[j])-I*creal((xo[j]))) :
                          creal(Wp[skipX*j])*xo[j] - cimag(Wp[skipX*j])*(cimag(xo[j])-I*creal((xo[j]))) ;*/
          temp = reverse ? Wp[skipX*((N-j)%N)] * xo[j] : Wp[skipX*j] * xo[j];
        x[j] = xe[j] + temp;
        x[j+N/2] = xe[j] - temp;
      }
      /*{
        if (reverse)
        {
          if (j == N/4 && N%4 == 0)
            temp = cimag(xo[j]) - I*creal(xo[j]);
          else
            temp = Wp[skipX*((N-j)%N)] * xo[j];
          x[j] = xe[j] + temp;
          x[j+N/2] = xe[j] - temp;
        }
        else
        {
          if (j == N/4 && N%4 == 0)
            temp = -cimag(xo[j]) + I*creal(xo[j]);
          else
            temp = Wp[skipX*j] * xo[j];
          x[j] = xe[j] + temp;
          x[j+N/2] = xe[j] - temp;
        }
      }*/
    }
  }
}

