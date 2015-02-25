#include <stdio.h>
#include <stdlib.h>

void printResult(int, double*);
int rcubic_roots(double*, double*);

int main()
{
  /* Chan, Joey, JMC */

  double a[3]; /* Coefficients to the equation */
  double roots[4]; /* Roots */

  int numberOfRoots;

  /* Extract information about the equation */
  printf("Chan, Joey | JMC | Cubic Solver\n");
  printf("-------------------------------\n");

  printf("To solve x^3 + a2 * x^2 + a1 * x + a0 = 0\n");
  printf("Please enter the 3 coefficient in the order a2, a1, a0\n");
  printf("separated with spaces: ");
  scanf("%lf %lf %lf", &a[0], &a[1], &a[2]);

  numberOfRoots = rcubic_roots(&a[0], &roots[0]);
  printResult(numberOfRoots, &roots[0]);

  return 0;
}

void printResult(int numberOfRoots, double* roots)
{
  /* Chan, Joey, JMC */

  double  r1 = *(roots+1),
          r2 = *(roots+2),
          r3 = *(roots+3);

  switch (numberOfRoots)
  {
    case 3:
      printf("There are 3 distinct real roots\n");
      printf("--------------------------------------------------\n");
      printf("x1 = %10.5g\nx2 = %10.5g\nx3 = %10.5g\n", r1, r2, r3);
      break;
    case 2:
      printf("There are 2 distinct real roots\n");
      printf("--------------------------------------------------\n");
      printf("x1 = %10.5g\nx2 = %10.5g\nx3 = %10.5g\n", r1, r2, r3);
      break;
    case 1:
      printf("There is 1 distinct real root\n");
      printf("--------------------------------------------------\n");
      printf("x = %10.5g\n", r1);
      break;
    case 0:
      printf("There are 1 real root and a complex conjugate pair\n");
      printf("--------------------------------------------------\n");
      printf("x1 = %10.5g\nx2 = %10.5g+%10.5gi\nx3 = %10.5g-%10.5gi\n", r1, r2, r3, r2, r3);
      break;
    default:
      break;
  }
}
