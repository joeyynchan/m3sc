#include <stdio.h>
#include <math.h>
#include <float.h>
#include <complex.h>

int rcubic_roots(double complex a2, double complex a1, double complex a0, double complex* r1, double complex* r2, double complex* r3)
{

  /* Chan, Joey, JMC */

  /* ALLOWED_ERROR is use to determine if two doubles are the "same"
   * If two double, a and b, are the "same", then cabs(a-b) < ALLOWED_ERROR
   * I choose to use a customizable standard so later if I want to improve the acurracy,
   * I only have to change the ALLOWED_ERROR parameter
   */
  double ALLOWED_ERROR = DBL_EPSILON;

  /* For result clarity */
  int THREE_DISTINCT_ROOTS = 3;
  int TWO_REPEATING_ROOTS = 2;
  int ONE_ROOT = 1;
  int COMPLEX_ROOT = 0;

  double complex UNITY_1  = 1.;           /* Unity Real root */
  double complex UNITY_RE = -1./2.;       /* Real part of the complex unity root */
  double complex UNITY_IM = sqrt(3.)/2.;  /* Imaginary part of the complex unity root */

  int result;
  double complex a, b, p;
  double complex y_n, y_n1;


  a = -cpow(2*a2*a2*a2-9*a1*a2+27*a0, 1./3.)/3.;

  /* alpha is 0, p cannot be calculated */
  if (a == 0)
  {
    *r1 = 0;
    result = quad_roots(1., 0., (a1 - a2*a2/3.), r2, r3);
  }


  /* Normal calculation */
  else
  {
    b = -a2/3.;
    p = (a1 - a2*a2/3.)/(a*a);
    //printf("%10.5g, %10.5g, %10.5g\n", a, b, p);

    /* Case v: p = 0
     * y is the three cubic roots
     */
    if (p == 0)
    {
      *r1 = UNITY_1  * a + b;
      *r2 = UNITY_RE * a + b;
      *r3 = UNITY_IM * a + b;
      result = COMPLEX_ROOT;
    }

    else
    {

      int count = 1;  /* Counter for number of iterations */
      double complex difference; /* Difference between y_n and y_(n+1) */

      y_n  = cabs(p) < 2. ? 1-p/3. : 1/p;
      y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
      difference = cabs(y_n1-y_n);
      //printf("%10.5g, %10.5g\n", y_n, y_n1);

      /* Iteration only stops when both of the following conditions are fulfilled
       * 1) y_(n+1) = y_n OR |y_(n+1) - y_n| starts diverging
       * 2) Performed at least 3 iterations
       */
      while ( (cabs(y_n-y_n1) > ALLOWED_ERROR || cabs(difference) > cabs(y_n1-y_n)) && 
              count < 3)
      {
        /* Update difference and counter before next iteration */
        count++;
        difference = cabs(y_n1-y_n); 

        y_n = y_n1;
        y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
      }
      *r1 = a*y_n1+b;
      printf("%10.5g %10.5g %10.5g %10.5g %10.5g %10.5g\n", creal(*r1), cimag(*r1), creal(a2), cimag(a2), creal(a0), cimag(a0));
      printf("%10.5g %10.5g %10.5g %10.5g %10.5g %10.5g\n", creal(*r1), cimag(*r1), creal(a2+(*r1)), cimag(a2+(*r1)), creal(-a0/(*r1)), cimag(-a0/(*r1)));
      result = quad_roots(1. + 0*I, a2+(*r1), -a0/(*r1), r2, r3) + 1;
    }

  }


  /* Compute the status which should be returned to main function */
  if (result != COMPLEX_ROOT)
  /* Solutions do not contains complex roots */
  {
    result = (*r1 == *r2 || *r2 == *r3 || *r1 == *r3) ? TWO_REPEATING_ROOTS : THREE_DISTINCT_ROOTS;
    result = (*r1 == *r2 && *r2 == *r3) ? ONE_ROOT : result;
  }
  return result;
}

