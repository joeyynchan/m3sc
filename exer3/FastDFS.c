#include <stdlib.h>
#include <complex.h>

void FastTransform(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skipY, int skipX, int reverse);

void FastDFS(complex double* x, /* Output result */
             complex double* y, /* Input data */
             complex double* w, /* Intermediate Result of size N */
             complex double* Wp,
             int N,
             int skip)
{
  int i;
  FastTransform(w+N, y, w, Wp, N, skip, 1, 0);
  for (i = 0; i < N; i++)
    x[i*skip] = w[N+i];
}
