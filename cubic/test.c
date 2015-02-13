#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int assertEqualRoot(double, double);
int assertEqualResult(int, int);
void test(int, double, double, double, double, double, double, int);

int main()
{
  
  test(    1,    4.,    -8.,     7.,   -5.6389,   0.81944,  0.75492,   0);
  test(    2,    3.,     1.,     4.,   -3.0946,   0.04728,  1.13594,   0);
  test(    3,    3.,     0.,     8.,   -3.6129,    0.3064,   1.4562,   0);
  test(    4,    3.,     9.,   -13.,        1.,       -2.,       3.,   0);
  test(    5,   -2.,    -5.,     6.,       -2.,        1.,       3.,   3);
  test(    6,    1.,    -1.,    -1.,       -1.,       -1.,       1.,   2);

  /* Case i */
  test(    7,    0.,     0.,    27.,       -3.,       1.5,  -2.5981,   0);
  test(    8,    0.,     0.,     8.,       -2.,        1.,  -1.7321,   0);
  test(    9,    0.,     0.,    -8.,        2.,       -1.,   1.7321,   0);

  test(   10,    4.,     4.,     0.,       -2.,       -2.,       0.,   2);
	test(   11,    2.,     4.,     8.,       -2.,        0.,       2.,   0);
	test(   12,   -2.,    -4.,     8.,       -2.,        2.,       2.,   2);
  test(   13,    2.,    -4.,    -8.,       -2.,       -2.,       2.,   2);

}

void test(int index, double a2, double a1, double a0, double r1, double r2, double r3, int n)
{
  double _r1, _r2, _r3;
  int _n = rcubic_roots(a2, a1, a0, &_r1, &_r2, &_r3);
  if (assertEqualRoot(_r1, r1) &&
      assertEqualRoot(_r2, r2) &&
      assertEqualRoot(_r3, r3) &&
      assertEqualResult(_n, n))
    printf("Test %3d passed\n", index);
  else
    printf("Test %3d failed!!!\n", index);
}

int assertEqualRoot(double actual, double expected)
{
  if (fabs(actual-expected) > 0.0001)
  {
    printf("expected = %10.5g, actual = %10.5g\n", expected, actual);
    return 0;
  }
  return 1;
}

int assertEqualResult(int actual, int expected)
{
  if (actual != expected)
  {
    printf("expected = %10d, actual = %10d\n", expected, actual);
    return 0;
  }
  return 1;
}
