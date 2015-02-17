#include <stdio.h>
#include <complex.h>

int main()
{
	/* Chan, Joey, JMC */
	double PI = 3.1415;
	double complex c0, c1, c2, s, r1, r2, r3;
	int j;

	printf("%5s %10s %10s %10s %10s %10s %10s\n", "j", "Re(r1)", "Im(r1)", "Re(r2)", "Im(r2)", "Re(r3)", "Im(r3)");
	for (j = 0; j <= 120; j++)
	{
		s = cexp(I*j*PI/60.);
		c0 = (9.*s*s - 9.*s)/(4.*s+2.);
		c1 = (6.*s+3.)/(4.*s+2.);
		c2 = -3./(4.*s+2.);
		rcubic_roots(c2, c1, c0, &r1, &r2, &r3);
		printf("%5d %10.5f %10.5f %10.5f %10.5f %10.5f %10.5f\n", j, creal(r1), cimag(r1), creal(r2), cimag(r2), creal(r3), cimag(r3));
	}

}