#include <stdio.h>
#include <math.h>
#include <complex.h>

int quad_roots(double complex c2, double complex c1, double complex c0, double complex* r1, double complex* r2)
{

  /* Chan, Joey, JMC */
  double complex delta;

  if (cabs(c2) == 0)
    return lin_root(c1, c0, r1);

  delta = c1 * c1 - 4. * c2 * c0;
  //printf("delta = (%10.5g, %10.5g)\n", creal(delta), cimag(delta));
  delta = csqrt(delta);
  *r1 = (-c1 - delta)/(2*c2);
  *r2 = (-c1 + delta)/(2*c2);

  //printf("c2 = (%10.5g, %10.5g)\n", creal(c2), cimag(c2));
  //printf("c1 = (%10.5g, %10.5g)\n", creal(c1), cimag(c1));
  //printf("c0 = (%10.5g, %10.5g)\n", creal(c0), cimag(c0));
  //printf("sqrt(delta) = (%10.5g, %10.5g)\n", creal(delta), cimag(delta));
  //printf("*r1 = (%10.5g, %10.5g)\n", creal(*r1), cimag(*r1));
  //printf("*r2 = (%10.5g, %10.5g)\n", creal(*r2), cimag(*r2));
  return delta == 0 ? 1 : 2;
}
