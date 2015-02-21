#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "test.h"
#include "rcubic_roots.h"

int main()
{
  double data[13][6] = {{    4.,    -8.,     7.,   -5.6389,   0.81944,  0.75492},
                        {    3.,     1.,     4.,   -3.0946,   0.04728,  1.13594},
                        {    3.,     0.,     8.,   -3.6129,    0.3064,   1.4562},
                        {    3.,     9.,   -13.,        1.,       -2.,       3.},
                        {   -2.,    -5.,     6.,       -2.,        1.,       3.},
                        {    1.,    -1.,    -1.,       -1.,       -1.,       1.},
                        {    0.,     0.,    27.,       -3.,       1.5,  -2.5981},
                        {    0.,     0.,     8.,       -2.,        1.,  -1.7321},
                        {    0.,     0.,    -8.,        2.,       -1.,   1.7321},
                        {    4.,     4.,     0.,       -2.,       -2.,       0.},
                        {    2.,     4.,     8.,       -2.,        0.,       2.},
                        {   -2.,    -4.,     8.,       -2.,        2.,       2.},
                        {    2.,    -4.,    -8.,       -2.,       -2.,       2.}};

  double n[13] = {0, 0, 0, 0, 3, 2, 0, 0, 0, 2, 0, 2, 2};


  /*
  test(    1,    4.,    -8.,     7.,   -5.6389,   0.81944,  0.75492,   0);
  test(    2,    3.,     1.,     4.,   -3.0946,   0.04728,  1.13594,   0);
  test(    3,    3.,     0.,     8.,   -3.6129,    0.3064,   1.4562,   0);
  test(    4,    3.,     9.,   -13.,        1.,       -2.,       3.,   0);
  test(    5,   -2.,    -5.,     6.,       -2.,        1.,       3.,   3);
  test(    6,    1.,    -1.,    -1.,       -1.,       -1.,       1.,   2);


  test(    7,    0.,     0.,    27.,       -3.,       1.5,  -2.5981,   0);
  test(    8,    0.,     0.,     8.,       -2.,        1.,  -1.7321,   0);
  test(    9,    0.,     0.,    -8.,        2.,       -1.,   1.7321,   0);

  test(   10,    4.,     4.,     0.,       -2.,       -2.,       0.,   2);
	test(   11,    2.,     4.,     8.,       -2.,        0.,       2.,   0);
	test(   12,   -2.,    -4.,     8.,       -2.,        2.,       2.,   2);
  test(   13,    2.,    -4.,    -8.,       -2.,       -2.,       2.,   2);
  */

  int i;
  for (i = 0; i < 13; i++)
  {
    if (test((&data)+i*8*sizeof(double), (&data)+i*11*sizeof(double), &n+i) == 1)
      printf("Test %2d Passed!", i);
    else
      printf("Test %2d Failed!!!", i);
  }

}

int test(double* args, double* roots, int n)
{
  double _roots[3];
  int _n = rcubic_roots(args, &_roots);
  if (assertEqualRoot(_roots[0], *(roots)) &&
      assertEqualRoot(_roots[1], *(roots+1)) &&
      assertEqualRoot(_roots[2], *(roots+2)) &&
      assertEqualResult(_n, n))
    return 1;
  else
    return 0;
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
