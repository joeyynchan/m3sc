#include <stdio.h>
#include <math.h>

int lin_root(float, float, float*);
int quad_roots(float, float, float, float*, float*);

int main (void)
{

  float a2, a1, a0;
  float r1 = 0, r2 = 0;

  printf("Enter coefficients of Quadratic Equation a2*x^2 + a1*x + a0 = 0 \n");
  printf("in the order a2, a1, a0, separated by spaces: ");
  scanf("%f %f %f", &a2, &a1, &a0);
  int num_root = quad_roots(a2, a1, a0, &r1, &r2);
  switch (num_root)
  {
    case 2:
      printf("There are 2 distinct real roots with x = %.6g or x = %.6g\n", r1, r2);
      break;
    case 1:
    case -1:
      printf("There is 1 distinct real root with x = %g\n", r1);
      break;
    case 0:
      printf("There is not real roots for the equation\n");
      break;
    case -2:
      printf("Any number is a root\n");
    default:
      break;
  }
  return 0;
}

int lin_root(float a1, float a0, float* r)
{
  if (a1 == 0)
    return a0 == 0 ? 0 : -1 ;
  *r = a0 == 0 ? 0 : -a0/a1;
  return 1;
}

int quad_roots(float a2, float a1, float a0, float* r1, float* r2)
{
  /* Handle Linear Equation */
  if (a2 == 0)
    return lin_root(a1, a0, r1) - 2;
  
  float delta = a1 * a1 - 4 * a2 * a0;
  /* No real roots */
  if (delta < 0)
    return 0;

  *r1 = (-a1 - sqrt(delta))/(2*a2);
  *r2 = (-a1 + sqrt(delta))/(2*a2);
  return (delta > 0) ? 2 : 1;
}