#include <stdio.h>
#include <math.h>
#include <float.h>

int rcubic_roots(double a2, double a1, double a0, double* r1, double* r2, double* r3)
{
  double a, b, p;
  a = -cbrt(2*a2*a2*a2-9*a1*a2+27*a0)/3.;
  b = -a2/3.;
  p = (a1 - a2*a2/3.)/(a*a);

  double y_n, y_n1;
  y_n  = fabs(p) < 2 ? 1-p/3. : 1/p;
  y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
  while (y_n != y_n1)
  {
    y_n = y_n1;
    y_n1 = y_n - (y_n*y_n*y_n + p*y_n - 1)/(3*y_n*y_n + p);
  }
  *r1 = a*y_n1+b;

  quad_roots(1., a2+(*r1), -a0/(*r1), r2, r3);

  return 0;
}
