#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define PI 3.14159265359

/* Function Declaration */
complex double* MakeWpowers(int N);

/* Function Implementation */
complex double* MakeWpowers(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  complex double *result = (complex double*) malloc(N*sizeof(complex double));
  for (i = 0; i < N; i++)
  {
  	double theta = 2.*i*PI/N;
    result[i] = cos(theta) + I*sin(theta);
  }
  return result;
}
