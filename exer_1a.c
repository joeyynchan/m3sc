#include <stdio.h>
#include <math.h>

int lin_root(double, double, double*);
int quad_roots(double, double, double, double*, double*);

int main (void)
{

double a2, a1, a0;
double r1, r2;

printf("Enter coefficients of Quadratic Equation a2*x^2 + a1*x + a0 = 0 \n");
printf("in the order a2, a1, a0, separated by spaces: ");
scanf("%lf %lf %lf", &a2, &a1, &a0);
int num_root = quad_roots(a2, a1, a0, &r1, &r2);
switch (num_root)
{
  case 0:
    printf("There is not real roots for the equation\n");
    break;
  case 1:
    printf("There is 1 distinct real root with x = %g\n", r1);
    break;
  case 2:
    printf("There are 2 distinct real roots with x = %.4g or x = %.4g\n", r1, r2);
    break;
  default:
    break;
}


return 0;
}

int lin_root(double a1, double a0, double* r)
{
  if (a1 != 0)
  {
    *r = (float) -a0/a1;
    return 1;
  }
  return 0;
}

int quad_roots(double a2, double a1, double a0, double* r1, double* r2)
{
  if (a2 != 0)
  {
    double delta = a1 * a1 - 4 * a2 * a0;
    if (delta < 0)
      return 0;
    *r1 = (a1 - sqrt(delta))/(2*a2);
    *r2 = (a1 + sqrt(delta))/(2*a2);
    return (delta > 0) ? 2 : 1;
  }
  return lin_root(a1, a0, r1);
}
