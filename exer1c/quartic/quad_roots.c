#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

int lin_root(double*, double*);
int calculateSqrt(double*, double*);
void swap(double*, double*);

int quad_roots(double* a, double* roots)
{

  /* Chan, Joey, JMCSC, ync12 */
  
  double a2 = *a,
         a1 = *(a+1),
         a0 = *(a+2);

  double *r1 = roots+1,
         *r2 = roots+2;
         
  double sqroot;
  double argv[2];
  int result;



  /* Handle Linear Equation */
  if (a2 == 0)
  {
    argv[0] = a1;
    argv[1] = a0;
    return lin_root(&argv[0], roots) - 2;
  }
  

  result = calculateSqrt(a, &sqroot);
  if (result < 0)
  /* Complex roots*/
  {
    *r1 = -a1/(2*a2);
    *r2 = sqroot/(2*a2);
  }
  else
  {
    if (a2 > 0 && a0 > 0 && 2*sqrt(a2)*sqrt(a0) == fabs(a1))
    {
      *r1 = *r2 = sqrt(a0)/sqrt(a2);
      if (a1 > 0)
        *r1 = *r2 = -(*r2);
    }
    else if (fabs(a1) < DBL_EPSILON)
    {
      *r1 = sqrt(-a0/a2);
      *r2 = -sqrt(-a0/a2);
    }
    else if (a1 > 0)
    {
      *r1 = -(a1 + sqroot)/(2*a2);
      *r2 = (a0/a2)/(*r1);
    }
    else
    {
      *r2 = ((-a1) + sqroot)/(2*a2);
      *r1 = (a0/a2)/(*r2);
    }
  }

  if (result >= 0 && (*r1) > (*r2))
    swap(r1, r2);

  return result + 1;
}

/* This function returns -1 if there is no real root 
 * or else, calculate the sqrt 
 */
int calculateSqrt(double* a, double* sqroot)
{
  /* Chan, Joey, JMCSC, ync12 */

  double a2 = *a,
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
    *sqroot = fabs(sqrt(fabs(result)));
  }

  if (fabs(result) < 1e-6)
    return 0;
  else if (result > 0)
    return 1;
  else
    return -1;
}
