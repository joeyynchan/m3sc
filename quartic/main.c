#include <stdio.h>
#include <stdlib.h>

void printResult(int, double*);
void printInfo();
int rquartic_roots(double*, double*);

int main()
{
  /* Chan, Joey, JMC */

  double argv[4]; /* Coefficients to the equation */
  double roots[5]; /* Roots */

  int numberOfRoots;

  /* Extract information about the equation */
  printInfo();

  printf("To solve x^4 + a3 * x^3 + a2 * x^2 + a1 * x + a0 = 0\n");
  printf("Please enter the 3 coefficient in the order a3, a2, a1, a0\n");
  printf("separated with spaces: ");
  scanf("%lf %lf %lf %lf", &argv[0], &argv[1], &argv[2], &argv[3]);

  numberOfRoots = rquartic_roots(&argv[0], &roots[0]);
  printResult(numberOfRoots, &roots[0]);
  return 0;
}

void printResult(int numberOfRoots, double* roots)
{
  double  r1 = *(roots+1),
          r2 = *(roots+2),
          r3 = *(roots+3),
          r4 = *(roots+4);

  /* Chan, Joey, JMC */
  switch (numberOfRoots)
  {
    case 4:
      printf("There are 4 distinct real roots\n");
      printf("--------------------------------------------------\n");
      printf("x1 = %.10f\nx2 = %.10f\nx3 = %.10f\nx4 = %.10f\n", r1, r2, r3, r4);
      break;
    case 3:
      printf("There are 3 distinct real roots\n");
      printf("--------------------------------------------------\n");
      printf("x1 = %10.5g\nx2 = %10.5g\nx3 = %10.5g\nx4 = %10.5g\n", r1, r2, r3, r4);
      break;
    case 2:
      printf("There are 2 real roots and 1 pair of complex conjugate roots\n");
      printf("--------------------------------------------------\n");
      printf("x1 = %10.5g\nx2 = %10.5g\nx3 = %10.5g + %10.5gi\nx4 = %10.5g - %10.5gi\n", r1, r2, r3, r4, r3, r4);
      break;
    case 1:
      printf("There is 1 or 2 distinct real root\n");
      printf("--------------------------------------------------\n");
      printf("x1 = %10.5g\nx2 = %10.5g\nx3 = %10.5g\nx4 = %10.5g\n", r1, r2, r3, r4);
      break;
    case 0:
      printf("There are 2 pairs of complex conjugate roots\n");
      printf("--------------------------------------------------\n");
      printf("x1 = %10.5g + %10.5gi\nx2 = %10.5g - %10.5gi\nx3 = %10.5g + %10.5gi\nx4 = %10.5g + %10.5gi\n", r1, r2, r1, r2, r3, r4, r3, r4);
      break;
    default:
      break;
  }
}

void printInfo()
{
  /* Chan, Joey, JMC */
  
  /*printf("\n What is this? : \234 ");*/
  printf("\n");
  printf("Chan, Joey | JMC | Cubic Solver\n");
  printf("Compilation Time : %s, %s \n", __TIME__, __DATE__);
  printf("-------------------------------\n");
}
