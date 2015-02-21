#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "quad_roots.h"
#include "lin_root.h"

int quad_roots(double* a, double* roots)
{
  /* Chan, Joey, JMC */
  double  a2 = *a,
          a1 = *(a+1),
          a0 = *(a+2);

  double* r1 = roots;
  double* r2 = roots+1;

  /* Handle Linear Equation */
  if (a2 == 0)
  {
    double a[2] = {a1, a0};
    return lin_root(&a, r1) - 2;

  }
  
  double sqroot;
  int d = calculateSqrt(a, &sqroot);

  if (d < 0)
  /* Complex roots*/
  {
    *r1 = -a1/(2*a2);
    *r2 = sqroot/(2*a2);
  }
  else if (a1 >= 0)
  /* Real roots */
  /* Using the more accurate way by avoiding substraction of coefficients with different signs */
  {
    *r1 = -(a1 + sqroot)/(2*a2);
    *r2 = (a0/a2)/(*r1);
  }
  else
  {
    *r2 = ((-a1) + sqroot)/(2*a2);
    *r1 = (a0/a2)/(*r2);
  }
  return d;
}




/* This function returns -1 if there is no real root 
 * or else, calculate the sqrt 
 */
int calculateSqrt(double* a, double* sqroot)
{
  /* Chan, Joey, JMC */
  double  a2 = *a,
          a1 = *(a+1),
          a0 = *(a+2);

  double result;
  
  if (a1 > 1e153)
  {
    result = 1. - 4. * (a2/a1) * (a0/a1);
    *sqroot = abs(a1) * sqrt(fabs(result));
  }
  
  else if (a2 > 1e153)
  {
    result = (a1/a2)*(a1/a2) - 4. * (a0/a2);
    *sqroot = abs(a2) * sqrt(fabs(result));
  }
  
  else if (a0 > 1e153)
  {
    result = (a1/a0)*(a1/a0) - 4. * (a2/a0);
    *sqroot = abs(a0) * sqrt(fabs(result));
  }
  
  else 
  {
    result = (a1 * a1 - 4. * a2 * a0);
    *sqroot = sqrt(fabs(result));
  }

  if (result >= 0)
    return (result == 0) ? 1 : 2;
  else
    return -1;
}
