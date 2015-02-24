#include <stdio.h>
#include <math.h>
#include <float.h>

void sort(double* r1, double* r2, double* r3);
void swap(double* r1, double* r2);

int rcubic_roots(double* args, double* roots)
{

  /* Chan, Joey, JMC */

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

  double  a2 = *args,
          a1 = *(args+1),
          a0 = *(args+2);
    
  double* r1 = roots+1,
        * r2 = roots+2,
        * r3 = roots+3;

  /* Case i: a2 == a1 == 0
   * Roots are unity times -sign(a0)|a0)^(1/3)
   */
  if (a2 == 0 && a1 == 0)
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
  else if (a0 == 0)
  {
    double a[3] = {1., a2, a1};
    *r1 = 0;
    result = quad_roots(&a, r1);
  }

  /* Case iii: a0 = a1*a2
   * x = +-(-a1)^(1/2), -a2
   */
	else if (a0 == a1*a2)
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
  else if (3*a1 == a2*a2 && 27*a0 == a2*a2*a2)
  {
    *r1 = *r2 = *r3 = -a2/3.;
  }

  else
  {
    a = -cbrt(2*a2*a2*a2-9*a1*a2+27*a0)/3.;

    /* alpha is 0, p cannot be calculated */
    if (a == 0)
    {
      double a[3] = {1., 0., a1 - a2*a2/3.};
      *r1 = 0;
      result = quad_roots(args, r1);
    }


    /* Normal calculation */
    else
    {
      b = -a2/3.;
      p = (a1 - a2*a2/3.)/(a*a);

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

        int count = 1;     /* Counter for number of iterations */
        double difference; /* Difference between y_n and y_(n+1) */
        double p2;

        y_n  = fabs(p) < 2. ? 1-p/3. : 1/p;
        y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
        difference = fabs(y_n1-y_n);

        /* Iteration only stops when both of the following conditions are fulfilled
         * 1) y_(n+1) = y_n OR |y_(n+1) - y_n| starts diverging
         * 2) Performed at least 3 iterations
         */
        while ((y_n != y_n1 || difference > fabs(y_n1-y_n)) &&
                count < 3)
        {
          count++;
          difference = fabs(y_n1-y_n); 

          y_n = y_n1;
          y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
        }
        *r1 = a*y_n1+b;
        
        /* Case vi */
        p2 = -3. * (*r1) * (*r1);
        if (p2 == p)
        {
          *r2 = *r1;
          *r3 = 1./((*r1)*(*r1));
        }
        
        double args[3] = {1., a2+(*r1), -a0/(*r1)};
        result = quad_roots(&args, r1);
      }

    }
  }


  /* Compute the status which should be returned to main function */
  if (result != COMPLEX_ROOT)
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
