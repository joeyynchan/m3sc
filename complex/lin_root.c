#include <stdio.h>
#include <math.h>
#include <complex.h>

int lin_root(double complex* argv, double complex* roots)
{
  /* Chan, Joey, JMCSC, ync12 */

  double complex c1 = *argv;
  double complex c0 = *(argv+1);
  double complex* r = roots+1;

  if (cabs(c1) == 0)
    return cabs(c0) == 0 ? 0 : -1 ;
  *r = cabs(c0) == 0 ? 0 : -c0/c1;
  return 1;
}
