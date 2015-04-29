#include <stdlib.h>
#include <complex.h>

void FastDFT(complex double* y, complex double* x, complex double* w, complex double* Wp, int N, int skip);
void FastTransform(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skipY, int skipX);

void FastDFT(complex double* x,  /* Input vector */
             complex double* y,  /* Final result */
             complex double* w,  /* Intermediate result of size N */
             complex double* Wp, /* List of power of W */
             int N,
             int skip)
{
  int i;
  FastTransform(w+N, x, w, Wp, N, skip, -1);
  for (i = 0; i < N; i++)
    y[i*skip] = w[N+i];
}
