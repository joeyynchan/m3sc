#include <stdio.h>

int rquartic_roots(double*, double*);

int main()
{
  /* Chan, Joey, JMC */

  double X = 1./5.;
  double Y = 1./3.;
  double b;
  double argv[4];
  double roots[5];
  int result;

  printf("  b       Re(t)       Im(t)         theta    \n");
  printf("----- ------------ ------------ -------------\n");
  for (b = 0.05; b <= 0.95; b+=0.05)
  {
  	argv[0] = (2*X + 2 - 2*b*b)/(b*Y);
  	argv[1] = 0;
  	argv[2] = (2*X - 2 + 2*b*b)/(b*Y);
  	argv[3] = 1.;

  	result = rquartic_roots(argv, roots);
  	switch (result)
  	{
  	  case 2:
  	  {
  	  	printf("%5.2f %12.6f %12.6f %12.6f\n", b, roots[1], 0., 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[2], 0., 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[3], -roots[4], 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[3],  roots[4], 0.);
  	  	break;
  	  }
  	  case 0:
  	  {
  	  	printf("%5.2f %12.6f %12.6f %12.6f\n", b, roots[1], -roots[2], 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[1],  roots[2], 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[3], -roots[4], 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[3],  roots[4], 0.);
  	  	break;
  	  }
  	  default:
  	  {
  	  	printf("%5.2f %12.6f %12.6f %12.6f\n", b, roots[1], 0., 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[2], 0., 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[3], 0., 0.);
  	  	printf("      %12.6f %12.6f %12.6f\n", roots[4], 0., 0.);
  	  	break;
  	  }
  	}
  }
}
