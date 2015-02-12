#include <stdio.h>
#include <math.h>
#include <float.h>

int rcubic_roots(double a2, double a1, double a0, double* r1, double* r2, double* r3)
{

  int result;
  double a, b, p;
  double y_n, y_n1;

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
    while (fabs(y_n-y_n1)>1e-15)
    {
      y_n = y_n1;
      y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
      //printf("%10.5g, %10.5g\n", a*y_n+b, a*y_n1+b);
    }
    *r1 = a*y_n1+b;
    result = quad_roots(1., a2+(*r1), -a0/(*r1), r2, r3) + 1;
  }

  /* Compute the status which should be returned to main function */
  if (result != 0)
  /* Solutions do not contains complex roots */
  {
    result = (*r1 == *r2 || *r2 == *r3 || *r1 == *r3) ? 2 : 3;
    result = (*r1 == *r2 && *r2 == *r3) ? 1 : result;
  }
  return result;
}
