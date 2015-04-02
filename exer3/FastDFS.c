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
        for (j = 0; j < N; j++)
          x[i] = Wp[skip*i*j%N]*y[j];
  	}
  } 
  else                  /* N even */
  { 
    int i, j;
    complex double* xe = w;
    complex double* xo = w + N/2;
    complex double* ye = y;
    complex double* yo = y + N/2;
    complex double* we = w + N/2;
    complex double* wo = w + N;
    complex double* temp = (complex double*) calloc(N/2, sizeof(complex double));


    /* rearrange y into y_even and y_odd */
    for (i = 0; i < N/2; i++)
    {
      y[i] = y[2*i];
      temp[i] = y[2*i+1];
    }

    for (i = 0; i < N/2; i++)
      y[i+N/2] = temp[i];
    free(temp);

    


    /* Divide the problems into two sub problems */
    FastDFS(xe, ye, we, Wp, N/2, 2*skip);      /* First half: even part */
    FastDFS(xo, yo, wo, Wp, N/2, 2*skip);  /* Second half: odd part */

    /*
    printf("xe[0] = %10.6f + %10.6fi\n", creal(xe[0]), cimag(xe[0]));
    printf("xe[1] = %10.6f + %10.6fi\n", creal(xe[1]), cimag(xe[1]));
    printf("xo[0] = %10.6f + %10.6fi\n", creal(xo[0]), cimag(xo[0]));
    printf("xo[1] = %10.6f + %10.6fi\n", creal(xo[1]), cimag(xo[1]));
    printf("skip = %d\n", skip);
    printf("N = %d\n", N);
    */


    /* Compute the final result from the two sub result */
    for (j = 0; j < N/2; j++)     /* First half */
      x[j] = xe[j] + Wp[skip*j] * xo[j];

    for (j = 0; j < N/2; j++)     /* Second half */
      x[j+N/2] = xe[j] + Wp[skip*(j+N/2)] * xo[j];
/*
    if (N==2)
      for (i = 0; i < N; i++)
      	printf("x[%d] = %10.6f\n", i, creal(x[i]));

    printf("\n\n");
    printf("%d, %d\nWp[4] = %10.6f + %10.6fi\nWp[0] = %10.6f + %10.6fi\n", skip*(j+N/2), skip*(j+N/2)%N, creal(Wp[skip*(j+N/2)]), cimag(Wp[skip*(j+N/2)]), creal(Wp[skip*(j+N/2)%N]), cimag(Wp[skip*(j+N/2)%N]));
*/
  }
}