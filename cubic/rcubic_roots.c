#include <stdio.h>
#include <math.h>
#include <float.h>

void sort(double*, double*, double*);
void swap(double*, double*);

int rcubic_roots(double a2, double a1, double a0, double* r1, double* r2, double* r3)
{

  int THREE_DISTINCT_ROOTS = 3;
  int TWO_REPEATING_ROOTS = 2;
  int ONE_ROOT = 1;
  int COMPLEX_ROOT = 0;

	double ALLOWED_ERROR = 1e-15;

  int result;
  double a, b, p;
  double y_n, y_n1;

  
  if (a2 == 0 && a1 == 0)
  {
    *r1 = *r2 = *r3 = cbrt(-a0);
    return ONE_ROOT;
  }

  else if (a0 == 0)
  {
    *r1 = 0;
    result = quad_roots(1., a2, a1, r2, r3);
  }

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

  else
  {
    a = -cbrt(2*a2*a2*a2-9*a1*a2+27*a0)/3.;
    if (a == 0)
    /* alpha is 0, p cannot be calculated */
    {
      *r1 = 0;
      result = quad_roots(1., 0., (a1 - a2*a2/3.), r2, r3);
    }
    else
    /* Normal calculation */
    {
      b = -a2/3.;
      p = (a1 - a2*a2/3.)/(a*a);
      //printf("%10.5g, %10.5g, %10.5g\n", a, b, p);

      y_n  = fabs(p) < 2. ? 1-p/3. : 1/p;
      y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
      //printf("%10.5g, %10.5g\n", y_n, y_n1);
      while (fabs(y_n-y_n1) > ALLOWED_ERROR)
      {
        y_n = y_n1;
        y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
        //printf("%10.5g, %10.5g\n", a*y_n+b, a*y_n1+b);
      }
      *r1 = a*y_n1+b;
      result = quad_roots(1., a2+(*r1), -a0/(*r1), r2, r3) + 1;
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
	if (*r1 > *r2)
		swap(r1, r2);
	if (*r2 > *r3)
		swap(r2, r3);
	if (*r1 > *r2)
		swap(r1, r2);
}

void swap(double* r1, double* r2)
{
	double temp = *r1;
	*r1 = *r2;
	*r2 = temp;
}
