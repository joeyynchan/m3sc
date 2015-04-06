#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int rquartic_test(double* args, double* roots, int* n);
int quad_test(double*, double*, int*);
int assertEqualRoot(double actual, double expected);
int assertEqualResult(int actual, int expected);
int rquartic_roots(double*, double*);
int quad_roots(double*, double*);

int main()
{

  double data4[13][4] = {
                        /* Normal Cases returning 4*/
                        {3., -39., -47., 210.},
                        {-10., 35., -50., 24.},
                        {10100., -1199020000., -120200000000., 24000000000000},
                        {8.25, -125.875, -625.5, 2705.63},
                        /* Normal Cases returning 3*/
                        {3., -3., -7., 6.},
                        {-10., 32., -38., 15.},
                        {-12., 50., -84., 45.},
                        {-14., 68., -130., 75.},
                        /* Normal Cases with 3 equal roots */
                        {-8., +18., -16., 5.},
                        /* Normal Case with 4 equal roots */
                        {-4., 6., -4., 1.},

                        {-2., 2., -2., 1.},

                        {0, 5., 0, 4.},
                        {-8., 42., -80., 125.}
                      };

  double data2[7][3] = {
                        {2., -4., 10.},
                        {2.,  7.,  0.},
                        {1., 3.45846e-323, 5.30499e-315},
                        {2., 0., 8.},
                        {2., 5., 7.},
                        {-2., 5., 7.},
                        {2., 0., 7.}
                       };

  double sol4[13][4] = {
                        {-7., -3., 2., 5.},
                        { 1.,  2., 3., 4.},
                        {-40000., -200., 100., 30000.},
                        {-13., -7.5, 3., 9.25},

                        {-3., -2., 1., 1.},
                        {1., 1., 3., 5.},
                        {1., 3., 3., 5.},
                        {1., 3., 5., 5.},
                        
                        {1., 1., 1., 5.},
                        {1., 1., 1., 1.},
                        
                        {1., 1., 0., 1.},

                        {0., 1., 0., 2.},
                        {1., 2., 3., 4.}
                     };

  double sol2[7][2] = {
                        {1., 2.},
                        {-3.5, 0},
                        {0, 0},
                        {0, 2.},
                        {-1.2500, 1.3919},
                        {-1., 3.5},
                        {0., 1.8708}
                      };

  int n4[13] = {4, 4, 4, 4, 3, 3, 3, 3, 1, 1, 2, 0, 0};
  int n2[7] = {0, 2, 1, 0, 0, 2, 0};

  int i;

  printf("\n_________Quartic Test___________\n");

  for (i = 0; i < 13; i++)
  {
    if (rquartic_test(&data4[i][0], &sol4[i][0], &n4[i]) == 1)
      printf("Test %2d Passed!\n", i+1);
    else
      printf("Test %2d Failed!!!\n", i+1);
  }

  printf("\n________Quadratic Test__________\n");

  for (i = 0; i < 7; i++)
  {
    if (quad_test(&data2[i][0], &sol2[i][0], &n2[i]) == 1)
      printf("Test %2d Passed!\n", i+1);
    else
      printf("Test %2d Failed!!!\n", i+1);
  }

  return 0;
}

int rquartic_test(double* args, double* roots, int* n)
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

int quad_test(double* args, double* roots, int* n)
{
  double _roots[3];
  int _n;
  _n = quad_roots(args, &_roots[0]);
  if (assertEqualRoot(_roots[1], *(roots)) &&
      assertEqualRoot(_roots[2], *(roots+1)) &&
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
