#include <stdio.h>
#include <math.h>
#include "rcubic_roots.h"

int main()
{
	double T;
	double r1, r2, r3;
	printf("\n%5s %10s %10s %10s %10s %10s\n", "T", "Fst", "Re(Snd)", "Im(Snd)", "Re(Trd)", "Im(Trd)");
	for (T = 0.; T <= 75000.; T += 1000.)
	{
		int result = rcubic_roots(14., T/2. - 12456., 5.*T - 24960., &r1, &r2, &r3);
		
		if (result > 0)
			printf("%5g %10.5f %10.5f %10.5f %10.5f %10.5f\n", T, r1, r2, 0., r3, 0.);
      //printf("%10.5f\n", r3);
		else
			printf("%5g %10.5f %10.5f %10.5f %10.5f %10.5f\n", T, r1, r2, -fabs(r3), r2, fabs(r3));
      //printf("%10.5f\n", r2);

	}
}
