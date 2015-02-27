#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define PI 3.14159265359
int main()
{
  int j;
  double complex s, d4;
  double complex d[4];
  double complex roots[5];
  printf(" j    Re(r1)     Re(r1)     Re(r2)     Im(r2)     Re(r3)     Im(r3)     Re(r4)     Im(r4)  \n");
  printf("--- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------\n");
  for (j = 0; j <=100; j++)
  {
	s = cexp(0. + I*PI*((double) j)/50.);
	d4 = 23.*s*s-16.*s+5.; 
	d[0] = (-12.*s*(5.*s+1.))/d4;
	d[1] = (36.*s*(5.*s+1.))/d4; 
	d[2] = (-108.*s*(5.*s+1.))/d4;
	d[3] = -324.*s*(s-1.)/d4;
	rquartic_roots(d, roots);

	printf("%3d %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f\n",
	 j,
	 creal(roots[1]), cimag(roots[1]),
	 creal(roots[2]), cimag(roots[2]),
	 creal(roots[3]), cimag(roots[3]),
	 creal(roots[4]), cimag(roots[4]));
  }

  return 0;
}