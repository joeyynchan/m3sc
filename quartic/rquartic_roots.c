#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int rcubic_roots(double*, double*);
int quad_roots(double*, double*);
void swap(double*, double*);
double max_ratio(double*, int);
int ascending(const void*, const void*);
int equal(double* a, double* b);

int rquartic_roots(double* args, double* roots)
{
  /* Chan, Joey, JMC */

  int ONE_COMPLEX_PAIR = 2;
  int TWO_COMPLEX_PAIRS = 0;

  double p[3], q[3];
  double b[3];
  double a0, a1, a2, a3;
  double r;
  double e;

  int conjugate_pair_count;
  int result;

  a3 = *(args+0);
  a2 = *(args+1);
  a1 = *(args+2);
  a0 = *(args+3);
  e  = max_ratio(args, 4);

/*
  printf("%10s %10s %10s %10s %10s\n", "a3", "a2", "a1", "a0", "e");
  printf("-------------------------------------------------------\n");
  printf("%10.5g %10.5g %10.5g %10.5g %10f\n\n", a3, a2, a1, a0, e);
*/

  conjugate_pair_count = 0;

  if (a0 == 0)
  {
    *roots = 0;
    conjugate_pair_count += (rcubic_roots(args, roots+1) == 0);
  }
  else if (a3 == 0 && a1 == 0)
  {
    double qroots[3];
    double a[3];
    a[0] = 1.;
    a[1] = a2;
    a[2] = a0;
    quad_roots(&a[0], &qroots[0]);
    /*printf("qroots = %.20f, %.20f\n", qroots[1], qroots[2]);*/
    if (qroots[1] < 0)
    {
      *(roots+1) = 0;
      *(roots+2) = sqrt(-qroots[1]);
      conjugate_pair_count = 2;
    }
    else
    {
      *(roots+1) = -sqrt(qroots[1]);
      *(roots+2) =  sqrt(qroots[1]);
    }

    if (qroots[2] < 0)
    {
      *(roots+3) = 0;
      *(roots+4) = sqrt(-qroots[2]);
      conjugate_pair_count++;
    }
    else
    {
      *(roots+3) = -sqrt(qroots[2]);
      *(roots+4) =  sqrt(qroots[2]);
    }
  }
  else if (a3 == 0 && a2 == 0 && a1 == 0)
  {
    if (a0 < 0)
    {
      *(roots+1) = -sqrt(sqrt(-a0));
      *(roots+2) =  sqrt(sqrt(-a0));
      *(roots+3) = 0;
      *(roots+4) =  sqrt(sqrt(-a0));
      conjugate_pair_count = 1;
    }
    else
    {
      double a;
      a = sqrt(a0)/sqrt(2.);
      *(roots+1) = -a;
      *(roots+2) =  a;
      *(roots+3) =  a;
      *(roots+4) =  a;
      conjugate_pair_count = 3;
    }
  }
  else
  {
    b[0] = -a2;
    b[1] = a1*a3 - 4.*a0;
    b[2] = 4.*a0*a2 - a1*a1 - a0*a3*a3;
    /*printf("b[0] = %.20f\nb[1] = %.20f\nb[2] = %.20f\n", b[0], b[1], b[2]); */

    r = (rcubic_roots(&b[0], &roots[0]) == 0) ? *(roots+1) : *(roots+3);
    /*printf("r1 = %.20f r2 = %.20f r3 = %.20f\n", *(roots+1), *roo */
    /*printf("r = %.20f\n", r);*/

    p[0] = 1.;
    p[1] = a3/2. + sqrt(a3*a3/4. + r - a2);
    p[2] = r/2. + sqrt((r/2.)*(r/2.) - a0);

    q[0] = 1.;
    q[1] = a3/2. - sqrt(a3*a3/4. + r - a2);
    q[2] = r/2. - sqrt((r/2.)*(r/2.) - a0);

/*
    printf("%10s %10s %10s %10s %10s %10s\n", "r", "p1", "p0", "q1", "q0", "p1q2+q1p2");
    printf("-----------------------------------------------------------------\n");
    printf("%10f %10f %10f %10f %10f %10f\n\n", r, p[1], p[2], q[1], q[2], p[1]*q[2] + q[1]*p[2]);

    printf("%10s %10s %10s %10s %10s %10s\n", "a", "b", "a-b", "a-b/b", "e", "e*1e-7");
    printf("-----------------------------------------------------------------\n");
    printf("%10f %10f %10f %10f %10f %10f\n\n", p[1]*q[2] + q[1]*p[2], a1, p[1]*q[2] + q[1]*p[2] - a1 , (p[1]*q[2] + q[1]*p[2] - a1)/ a1, e, e*1e-7);
*/

    if (fabs((p[1]*q[2] + q[1]*p[2] - a1)/a1) > e*1e-7)
      swap(&p[2], &q[2]);

/*
    printf("%10s %10s %10s %10s %10s %10s\n", "r", "p1", "p0", "q1", "q0", "p1q2+q1p2");
    printf("-----------------------------------------------------------------\n");
    printf("%.10f %.10f %.10f %.10f %.10f %.10f\n\n", r, p[1], p[2], q[1], q[2], p[1]*q[2] + q[1]*p[2]);
*/

    conjugate_pair_count += (quad_roots(&p[0], roots  ) == 0)*2;
    /*printf ("conjugate_pair_count = %d\n", conjugate_pair_count);*/
    conjugate_pair_count += (quad_roots(&q[0], roots+2) == 0);
    /*printf ("conjugate_pair_count = %d\n", conjugate_pair_count);*/
  }

/*
  printf("%15s %15s %15s %15s\n", "r1", "r2", "r3", "r4");
  printf("---------------------------------------------\n");
  printf("%15f %15f %15f %15f\n\n", *(roots+1), *(roots+2), *(roots+3), *(roots+4));
*/

  if (conjugate_pair_count > 0)
  {
    result = (conjugate_pair_count < 3) ? ONE_COMPLEX_PAIR : TWO_COMPLEX_PAIRS ;
    if (conjugate_pair_count == 2) {
      swap(roots+1, roots+3);
      swap(roots+2, roots+4);
    }
    else if (conjugate_pair_count == 3)
    {
      if (equal(roots+1, roots+3) && *(roots+2) > *(roots+4))
        swap(roots+2, roots+4);
      else if (*(roots+1) > *(roots+3))
      {
        swap(roots+1, roots+3);
        swap(roots+2, roots+4);
      }
    }
  }
  else
  {
    result = 3;
    qsort(roots+1, 4, sizeof(double), ascending);
    if ((equal(roots+1, roots+2) && equal(roots+1, roots+3)) ||
        (equal(roots+1, roots+3) && equal(roots+2, roots+4)) ||
        (equal(roots+2, roots+3) && equal(roots+3, roots+4)) ||
        (equal(roots+1, roots+2) && equal(roots+2, roots+3) && equal(roots+3, roots+4)))
      result = 1;
    if (!equal(roots+1, roots+2) && !equal(roots+1, roots+3) && !equal(roots+1, roots+4) &&
        !equal(roots+2, roots+3) && !equal(roots+2, roots+4) &&
        !equal(roots+3, roots+4))
      result = 4;
  }
  return result;
}

double max_ratio(double* argv, int n)
{
  /* Chan, Joey, JMC */

  int i;
  double min = DBL_MAX;
  double max = DBL_MIN;
  for (i = 0; i < n; i++) {
    min = *(argv+i) < min ? *(argv+i) : min;
    max = *(argv+i) > max ? *(argv+i) : max;
  }
  return fabs(max/min);
}

int ascending(const void* a, const void* b)
{
  /* Chan, Joey, JMC */

  return (*(double*)a - *(double*)b);
}

int equal(double* a, double* b)
{
  /* Chan, Joey, JMC */
  
  return (fabs(*a - *b) < 1e-5);
}
