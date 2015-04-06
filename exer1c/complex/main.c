#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

void printInfo();
void printResult(int, double, double, double);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  double argv[8]; /* Coefficients to the equation */
  double complex a[4];
  double complex roots[5]; /* Roots */

  printInfo();
  printf("To solve x^3 + a2 * x^2 + a1 * x + a0 = 0\n");
  printf("Please enter the 3 coefficient in the order a2, a1, a0\n");
  printf("separated with spaces: ");
  scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &argv[0], &argv[1], &argv[2], &argv[3], &argv[4], &argv[5], &argv[6], &argv[7]);

  a[0] = argv[0] + argv[1]*I;
  a[1] = argv[2] + argv[3]*I;
  a[2] = argv[4] + argv[5]*I;
  a[3] = argv[6] + argv[7]*I;

  rquartic_roots(&a[0], &roots[0]);
  printf("x1 = %10.6f + %10.6fi\n", creal(roots[1]), cimag(roots[1]));
  printf("x2 = %10.6f + %10.6fi\n", creal(roots[2]), cimag(roots[2]));
  printf("x3 = %10.6f + %10.6fi\n", creal(roots[3]), cimag(roots[3]));
  printf("x4 = %10.6f + %10.6fi\n", creal(roots[4]), cimag(roots[4]));

}

void printInfo()
{
  /* Chan, Joey, JMCSC, ync12 */
  
  /*printf("\n What is this? : \234 ");*/
  printf("\n");
  printf("%15s: %s\n", "Name", "Joey");
  printf("%15s: %s\n", "CID", "00730306");
  printf("%15s: %s\n", "LIBRARY NO", "0246734100");
  printf("%15s: %s\n", "Email Address", "ync12@ic.ac.uk");
  printf("%15s: %s\n", "Course Code", "JMCSC");
  printf("%15s: %s, %s \n", "Compile Time", __TIME__, __DATE__);
  printf("-------------------------------------------------\n");
}
