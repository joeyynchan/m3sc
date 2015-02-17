#include <stdio.h>
#include <math.h>
//#include "rcubic_roots.h"

int main()
{
	double T;
	double r1, r2, r3;

	for (T = 0.; T <= 75000.; T += 1.)
	{
		int result = rcubic_roots(14., T/2. - 12456., 5.*T - 24960., &r1, &r2, &r3);

		if (result > 0 && (r1 == 0 || r2 == 0 || r3 == 0))
			printf("When T = %5g , one of the 3 real roots takes the value 0\n", T);
		if (result == 2)
			printf("When T = %5g , two of the roots are equal\n", T);
		if (result == 0 && r2 == 0)
			printf("When T = %5g , the real part of the complex roots is equal 0\n", T);

	}
}
