#include <math.h>

int rcubic_roots(double*, double*);

int rquartic_roots(double* args, double* roots)
{

  int ONE_COMPLEX_PAIR = 2;
  int TWO_COMPLEX_PAIRS = 0;

  double p[3], q[3];
  double a0, a1, a2, a3;
  double r1, r2, r3, r4;
  double r;
  double b[3];

  int conjugate_pair_count;
  int repeat_root_count;
  int result;

  a3 = *(args+0);
  a2 = *(args+1);
  a1 = *(args+2);
  a0 = *(args+3);

  r1 = *(roots+1);
  r2 = *(roots+2);
  r3 = *(roots+3);
  r4 = *(roots+4);

  b[0] = -a2;
  b[1] = a1*a3 - 4.*a0;
  b[2] = 4.*a0*a2 - a1*a1 - a0*a3*a3;

  r = (rcubic_roots(&b, roots) == 3) ? *(roots+3) : *(roots+1);

  p[0] = 1.;
  p[1] = a3/2. + sqrt(a3*a3/4. + r - a2);
  p[2] = r/2. + sqrt((r/2.)*(r/2.) - a0);

  q[0] = 1.;
  q[1] = a3/2. - sqrt(a3*a3/4. + r - a2);
  q[2] = r/2. - sqrt((r/2.)*(r/2.) - a0);

  conjugate_pair_count = 0;
  repeat_root_count = 0;

  result = quad_roots(&p, roots);
  conjugate_pair_count += (result == 0);
  repeat_root_count += (result == 1);

  result = quad_roots(&q, roots+2);
  conjugate_pair_count += (result == 0);
  repeat_root_count += (result == 1);

  if (conjugate_pair_count > 0)
  	return (conjugate_pair_count == 1) ? ONE_COMPLEX_PAIR : TWO_COMPLEX_PAIRS ;
  else
  	return 4 - 2 * (conjugate_pair_count);   
}