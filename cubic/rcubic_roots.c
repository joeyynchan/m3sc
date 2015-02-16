#include <stdio.h>
#include <math.h>
#include <float.h>
#include "rcubic_roots.h"
#include "quad_roots.h"

int rcubic_roots(double a2, double a1, double a0, double* r1, double* r2, double* r3)
{

  /* Chan, Joey, JMC */

  /* ALLOWED_ERROR is use to determine if two doubles are the "same"
   * If two double, a and b, are the "same", then fabs(a-b) < ALLOWED_ERROR
   * I choose to use a customizable standard so later if I want to improve the acurracy,
   * I only have to change the ALLOWED_ERROR parameter
   */
  double ALLOWED_ERROR = DBL_EPSILON;

  /* For result clarity */
  int THREE_DISTINCT_ROOTS = 3;
  int TWO_REPEATING_ROOTS = 2;
  int ONE_ROOT = 1;
  int COMPLEX_ROOT = 0;

  double UNITY_1  = 1.;           /* Unity Real root */
  double UNITY_RE = -1./2.;       /* Real part of the complex unity root */
  double UNITY_IM = sqrt(3.)/2.;  /* Imaginary part of the complex unity root */

  int result;
  double a, b, p;
  double y_n, y_n1;
  
  /* Case i: a2 == a1 == 0
   * Roots are unity times -sign(a0)|a0)^(1/3)
   */
  if (fabs(a2) < ALLOWED_ERROR &&
      fabs(a1) < ALLOWED_ERROR)
  {
    *r1 = *r2 = *r3 = (a0 < 0) ? cbrt(-a0) : -cbrt(a0);
    *r2 *= UNITY_RE;
    *r3 *= UNITY_IM;
    return COMPLEX_ROOT;
  }

  /* Case ii: a0 == 0
   * One root = 0
   * Call quad_roots() to find the other two roots
   */
  else if (fabs(a0) < ALLOWED_ERROR)
  {
    *r1 = 0;
    result = quad_roots(1., a2, a1, r2, r3);
  }

  /* Case iii: a0 = a1*a2
   * x = +-(-a1)^(1/2), -a2
   */
	else if (fabs(a0 - a1*a2) < ALLOWED_ERROR)
	{
		*r1 = -a2;
		if (a1 > 0)
		{
			*r3 = sqrt(a1);
			*r2 = 0;
		}
		else
		{
			*r2 = sqrt(-a1);
			*r3 = -sqrt(-a1);
		}
		result = (a1 > 0) ? COMPLEX_ROOT : THREE_DISTINCT_ROOTS ;
	}

  /* Case iv: 3*a1 == (a2)^2 && 27*a0 = (a2)^3
   * # identical roots: -(a2)/3
   */
  else if ( fabs(3*a1 - a2*a2) < ALLOWED_ERROR && 
            fabs(27*a0 - a2*a2*a2) < ALLOWED_ERROR)
  {
    *r1 = *r2 = *r3 = -a2/3.;
  }


  else
  {
    a = -cbrt(2*a2*a2*a2-9*a1*a2+27*a0)/3.;

    /* alpha is 0, p cannot be calculated */
    if (fabs(a) < ALLOWED_ERROR)
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
      if (fabs(p) < ALLOWED_ERROR)
      {
        *r1 = UNITY_1  * a + b;
        *r2 = UNITY_RE * a + b;
        *r3 = UNITY_IM * a + b;
        result = COMPLEX_ROOT;
      }

      else
      {

        int count = 1;  /* Counter for number of iterations */
        double difference; /* Difference between y_n and y_(n+1) */

        y_n  = fabs(p) < 2. ? 1-p/3. : 1/p;
        y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
        difference = fabs(y_n1-y_n);
        //printf("%10.5g, %10.5g\n", y_n, y_n1);

        /* Iteration only stops when both of the following conditions are fulfilled
         * 1) y_(n+1) = y_n OR |y_(n+1) - y_n| starts diverging
         * 2) Performed at least 3 iterations
         */
        while ( (fabs(y_n-y_n1) > ALLOWED_ERROR || difference > fabs(y_n1-y_n)) && 
                count < 3)
        {
          /* Update difference and counter before next iteration */
          count++;
          difference = fabs(y_n1-y_n); 

          y_n = y_n1;
          y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
          //printf("%10.5g, %10.5g\n", a*y_n+b, a*y_n1+b);
        }
        *r1 = a*y_n1+b;
        result = quad_roots(1., a2+(*r1), -a0/(*r1), r2, r3) + 1;
      }

    }
  }


  /* Compute the status which should be returned to main function */
  if (result != COMPLEX_ROOT)
  /* Solutions do not contains complex roots */
  {
    result = (*r1 == *r2 || *r2 == *r3 || *r1 == *r3) ? TWO_REPEATING_ROOTS : THREE_DISTINCT_ROOTS;
    result = (*r1 == *r2 && *r2 == *r3) ? ONE_ROOT : result;
  }
	if (result == THREE_DISTINCT_ROOTS ||
			result == TWO_REPEATING_ROOTS)
		sort(r1, r2, r3);
  return result;
}

void sort(double* r1, double* r2, double* r3)
{
  /* Chan, Joey, JMC */
	if (*r1 > *r2)
		swap(r1, r2);
	if (*r2 > *r3)
		swap(r2, r3);
	if (*r1 > *r2)
		swap(r1, r2);
}

void swap(double* r1, double* r2)
{
  /* Chan, Joey, JMC */
	double temp = *r1;
	*r1 = *r2;
	*r2 = temp;
}
