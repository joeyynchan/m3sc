#include <math.h>
#include <complex.h>
#include <stdio.h>

void swap(double complex*, double complex*);

int rquartic_roots(double complex* argv, double complex* roots)
{
	double complex  a3 = *(argv+0),
  					      a2 = *(argv+1),
  					      a1 = *(argv+2),
  					      a0 = *(argv+3);

	double complex p[3], q[3];
	double complex b[3];
	double complex r;

  //printf("a3 = %10.5g + %10.5gi\n", creal(a3), cimag(a3));
  //printf("a2 = %10.5g + %10.5gi\n", creal(a2), cimag(a2));
  //printf("a1 = %10.5g + %10.5gi\n", creal(a1), cimag(a1));
  //printf("a0 = %10.5g + %10.5gi\n", creal(a0), cimag(a0));

	b[0] = -a2;
  b[1] = a1*a3 - (4. + 0*I) *a0;
  b[2] = (4. + 0*I) *a0*a2 - a1*a1 - a0*a3*a3;

	//printf ("b[0] = %20.10f + %20.10fi\n", creal(b[0]), cimag(b[0]));
	//printf ("b[1] = %20.10f + %20.10fi\n", creal(b[1]), cimag(b[1]));
	//printf ("b[2] = %20.10f + %20.10fi\n", creal(b[2]), cimag(b[2]));

	rcubic_roots(&b[0], roots);
 	//printf("r1 = %10.5g + %10.5gi\n", creal(roots[1]), cimag(roots[1]));
 	//printf("r2 = %10.5g + %10.5gi\n", creal(roots[2]), cimag(roots[2]));
  //printf("r3 = %10.5g + %10.5gi\n", creal(roots[3]), cimag(roots[3]));
  r = *(roots+3);
	//printf ("r    = %20.10f + %20.10fi\n", creal(r), cimag(r));

  p[0] = 1. + 0*I;
  p[1] = a3/2. + csqrt(a3*a3/4. + r - a2);
  p[2] = r/2. + csqrt((r/2.)*(r/2.) - a0);

  q[0] = 1. + 0*I;
  q[1] = a3/2. - csqrt(a3*a3/4. + r - a2);
  q[2] = r/2. - csqrt((r/2.)*(r/2.) - a0);

  if (cabs((p[1]*q[2] + q[1]*p[2] - a1)/a1) > cabs((p[1]*p[2] + q[1]*q[2] - a1)/a1))
    swap(&p[2], &q[2]);

    //printf ("p[0] = %20.10f + %20.10fi\n", creal(p[0]), cimag(p[0]));
  	//printf ("p[1] = %20.10f + %20.10fi\n", creal(p[1]), cimag(p[1]));
  	//printf ("p[2] = %20.10f + %20.10fi\n", creal(p[2]), cimag(p[2]));
  	//printf ("q[0] = %20.10f + %20.10fi\n", creal(q[0]), cimag(q[0]));
  	//printf ("q[1] = %20.10f + %20.10fi\n", creal(q[1]), cimag(q[1]));
  	//printf ("q[2] = %20.10f + %20.10fi\n", creal(q[2]), cimag(q[2]));

  quad_roots(&p[0], roots);
  quad_roots(&q[0], roots+2);

  return 0;
}

void swap(double complex* r1, double complex* r2)
{
  /* Chan, Joey, JMC */
	double complex temp = *r1;
	*r1 = *r2;
	*r2 = temp;
}