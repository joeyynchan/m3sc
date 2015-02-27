#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <float.h>

int quad_roots(double complex* argv, double complex* roots)
{

  /* Chan, Joey, JMC */
  double complex c2 = *(argv+0),
                 c1 = *(argv+1),
                 c0 = *(argv+2);

  if (cabs(c2)< DBL_EPSILON)
    c2 = 0. +  0*I;  
  if (cabs(c1)< DBL_EPSILON)
    c1 = 0. +  0*I;  
  if (cabs(c0)< DBL_EPSILON)
    c0 = 0. +  0*I;

  //printf("c2 = %10.5g + %10.5gi\n", creal(c2), cimag(c2));
  //printf("c1 = %10.5g + %10.5gi\n", creal(c1), cimag(c1));
  //printf("c0 = %10.5g + %10.5gi\n", creal(c0), cimag(c0));

  double complex* r1 = roots+1,
                * r2 = roots+2;
  double complex delta;

  if (cabs(c2) == 0)
    return lin_root(&c1, roots);

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
  return 0;
}
