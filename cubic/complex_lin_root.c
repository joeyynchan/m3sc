#include <stdio.h>
#include <math.h>
#include <complex.h>

int lin_root(double complex c1, double complex c0, double complex* r)
{
  /* Chan, Joey, JMC */
  if (cabs(c1) == 0)
    return cabs(c0) == 0 ? 0 : -1 ;
  *r = cabs(c0) == 0 ? 0 : -c0/c1;
  return 1;
}
