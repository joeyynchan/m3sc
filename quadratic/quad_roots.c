#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int quad_roots(double a2, double a1, double a0, double* r1, double* r2)
{

  double sqroot;
  int d;
  /* Handle Linear Equation */
  if (a2 == 0)
    return lin_root(a1, a0, r1) - 2;
  
  d = calculateSqrt(a2, a1, a0, &sqroot);
  printf("HI");
  /* Complex Root */
  if (d < 0)
  {
    *r1 = -a1/(2*a2);
    *r2 = sqroot/(2*a2);
    return 0;
  }

  /* Using the more accurate way by avoiding substraction of coefficients with different signs */
  if (a1 >= 0)
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
int calculateSqrt(double a2, double a1, double a0, double* sqroot)
{
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
