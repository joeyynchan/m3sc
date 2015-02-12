#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int assertEqual(double, double);
void test(int, double, double, double, double, double, double);

int main()
{
  test(1,  4.,  -8.,   7., -5.6389, 0.81944, 0.75492);
  test(2,  3.,   1.,   4., -3.0946, 0.04728, 1.13594);
}

void test(int index, double a2, double a1, double a0, double r1, double r2, double r3)
{
  double _r1, _r2, _r3;
  int _n = rcubic_roots(a2, a1, a0, &_r1, &_r2, &_r3);
  if (assertEqual(_r1, r1) &&
      assertEqual(_r2, r2) &&
      assertEqual(_r3, r3))
    printf("Test %3d passed\n", index);
  else
    printf("Test %3d failed!!!\n", index);
}

int assertEqual(double actual, double expected)
{
  if (fabs(actual-expected) > 0.0001)
  {
    printf("expected = %10.5g, actual = %10.5g\n", expected, actual);
    return 0;
  }
  return 1;
}
