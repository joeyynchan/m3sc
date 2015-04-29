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
  int i;
  complex double* Wp2 = (complex double*) malloc(N*sizeof(complex double));
  for (i = 0; i < N; i++)
    Wp2[i] = Wp[(N-i)%N];
  FastDFS(y, x, w, Wp2, N, skip);
  free(Wp2);
  for (i = 0; i < N; i++)
    y[i] /= N;
}
