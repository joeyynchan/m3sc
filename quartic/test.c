#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int test(double* args, double* roots, int* n);
int assertEqualRoot(double actual, double expected);
int assertEqualResult(int actual, int expected);
int rquartic_roots(double*, double*);

int main()
{

  double data[5][4] = {
                        /* Normal Cases returning 4*/
                        {3., -39., -47., 210.},
                        {-10., 35., -50., 24.},
                        {10100., -1199020000., -120200000000., 24000000000000},
                        {8.25, -125.875, -625.5, 2705.63},
                        /* Normal Cases returning 3*/
                        {3., -3., -7., 6.}
                      };

  double sol[5][4] = {
                        {-7., -3., 2., 5.},
                        { 1.,  2., 3., 4.},
                        {-40000., -200., 100., 30000.},
                        {-13., -7.5, 3., 9.25},

                        {-3., -2., 1., 1.}
                     };

  int n[5] = {4, 4, 4, 4, 3};

  int i;

  for (i = 0; i < 5; i++)
  {
    if (test(&data[i][0], &sol[i][0], &n[i]) == 1)
      printf("Test %2d Passed!\n", i);
    else
      printf("Test %2d Failed!!!\n", i);
  }
  return 0;
}

int test(double* args, double* roots, int* n)
{
  double _roots[5];
  int _n;
  _n = rquartic_roots(args, &_roots[0]);
  if (assertEqualRoot(_roots[1], *(roots)) &&
      assertEqualRoot(_roots[2], *(roots+1)) &&
      assertEqualRoot(_roots[3], *(roots+2)) &&
      assertEqualRoot(_roots[4], *(roots+3)) &&
      assertEqualResult(_n, *n))
    return 1;
  else
    return 0;
}

int assertEqualRoot(double actual, double expected)
{
  if (fabs((actual-expected)/expected) > 1e-4)
  {
    printf("expected = %20.10f, actual = %20.10f, ratio diff = %10f\n", expected, actual, fabs((actual-expected)/expected));
    return 0;
  }
  return 1;
}

int assertEqualResult(int actual, int expected)
{
  if (actual != expected)
  {
    printf("expected number of roots = %2d, but actual number of roots = %2d\n", expected, actual);
    return 0;
  }
  return 1;
}
