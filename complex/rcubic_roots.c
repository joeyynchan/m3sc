#include <stdio.h>
#include <math.h>
#include <float.h>
#include <complex.h>

int ascending(const void* a, const void* b);

int rcubic_roots(double complex* argv, double complex* roots)
{

  double complex a2 = *(argv+0),
                 a1 = *(argv+1),
                 a0 = *(argv+2);

  //printf("rcubic a2 = %10.5g + %10.5gi\n", creal(a2), cimag(a2));
  //printf("rcubic a1 = %10.5g + %10.5gi\n", creal(a1), cimag(a1));
  //printf("rcubic a0 = %10.5g + %10.5gi\n", creal(a0), cimag(a0));

  double complex *r1 = roots+1,
                 *r2 = roots+2,
                 *r3 = roots+3;

  /* Chan, Joey, JMC */
  double ALLOWED_ERROR = DBL_EPSILON;

  double complex UNITY_1  = 1. + 0.*I;           /* Unity Real root */
  double complex UNITY_2 = -1./2. - sqrt(3.)/2.*I;       /* Real part of the complex unity root */
  double complex UNITY_3 = -1./2. + sqrt(3.)/2.*I;  /* Imaginary part of the complex unity root */

  int result;
  double complex a, b, p;
  double complex y_n, y_n1;

  a = (1./3.)* cpow(9.*a1*a2- 2.*a2*a2*a2 - 27.*a0, (1./3.));
  b = -a2/3.;

  /* alpha is 0, p cannot be calculated */
  if (a == 0)
  {
    *r1 = b;
    double complex z[3] = {(1.+0*I), (0. + 0*I), (a1 - a2*a2/3.)};
    quad_roots(z, r1);
    *r2 += b;
    *r3 += b;
  }

  /* Normal calculation */
  else
  {
    p = (a1 - a2*a2/3.)/(a*a);

    int count = 1;              /* Counter for number of iterations */
    double complex difference;  /* Difference between y_n and y_(n+1) */

    y_n  = cabs(p) < 2. ? 1.-p/3. : 1./p;
    y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
    difference = cabs(y_n1-y_n);

    while ( (cabs(y_n-y_n1) > ALLOWED_ERROR && cabs(difference) < cabs(y_n1-y_n)) || 
            count < 3)
    {
      count++;
      difference = cabs(y_n1-y_n); 

      y_n = y_n1;
      y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
    }
    *r1 = a*y_n1+b;
    double complex z[3] = {1. + 0*I, a2+(*r1), -a0/(*r1)};
    quad_roots(z, r1);

  }

  qsort(roots+1, 3, sizeof(double complex), ascending);

  return 0;
}

int ascending(const void* a, const void* b)
{
  /* Chan, Joey, JMC */

  return (cabs(*(double complex*)a) - cabs(*(double complex*)b));
}

