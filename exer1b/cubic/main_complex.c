#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

void printResult(int, double complex, double complex, double complex);

int main()
{

  /* Chan, Joey, JMC */
  double a0, a1, a2, b0, b1, b2; /* Coefficients to the equation */
  double complex r1, r2, r3; /* Roots */
  double complex c0, c1, c2;

  int numberOfRoots;

  /* Extract information about the equation */
  printf("###################\n");
  printf("# JMC | JOEY CHAN #\n");
  printf("###################\n");
  printf("To solve x^3 + (a2 + b2*i) * x^2 + (a1 +b2*i) * x + (a0 + b0*i) = 0\n");
  printf("Please enter the 3 coefficient in the order a2, a1, a0\n");
  printf("separated with spaces: ");
  scanf("%lf %lf %lf %lf %lf %lf", &a2, &b2, &a1, &b1, &a0, &b0);

  c2 = a2 + b2*I;
  c1 = a1 + b1*I;
  c0 = a0 + b0*I;

  numberOfRoots = rcubic_roots(c2, c1, c0, &r1, &r2, &r3);
  printResult(numberOfRoots, r1, r2, r3);

}

void printResult(int numberOfRoots, double complex r1, double complex r2, double complex r3)
{
  /* Chan, Joey, JMC */
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
    default:
      break;
  }
}
