#include <stdio.h>
#include <stdlib.h>

int main()
{
  double a2, a1, a0;
  double r1 = 0, r2 = 0;

  printf("*******************\n");
  printf("* JMC | Joey Chan *\n");
  printf("*******************\n");
  printf("Enter coefficients of Quadratic Equation a2*x^2 + a1*x + a0 = 0 \n");
  printf("in the order a2, a1, a0, separated by spaces: ");
  scanf("%lf %lf %lf", &a2, &a1, &a0);
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
