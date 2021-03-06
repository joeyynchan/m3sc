#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>

#define PI                3.14159265359

void printInfo();
complex double* MakeWpowers(int N);
void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);
void FastDFS2(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int skip = 1, count = 1, N = 2;
  printInfo();
  printf(" log2(N)        FastDFS     FastDFS2     ratio\n");
  printf("--------- ------------ ------------ ---------\n");
  while (1)
  {
    int i, count1 = 0, count2 = 0;
    double time_diff1 = 0.;
    double time_diff2 = 0.;
    clock_t start_time, end_time;

    complex double *Wp = MakeWpowers(N);
    complex double *w  = (complex double*) malloc(2*N    * sizeof(complex double));
    complex double *y  = (complex double*) malloc(N*skip * sizeof(complex double));
    complex double *x  = (complex double*) malloc(N*skip * sizeof(complex double));
    
    printf("%9d ", count++);

    for (i = 0; i < N*skip; i++)
      y[i] = i;

    /* Time FastSine Method */
    start_time = clock();
    do
    {
      FastDFS(x, y, w, Wp, N, skip);
      end_time = clock();
      time_diff1 = (double) (end_time - start_time);
      count1++;
    } while (time_diff1 == 0);
    printf("%12.6f ", time_diff1/(CLOCKS_PER_SEC*count1));

    for (i = 0; i < N*skip; i++)
      y[i] = i;

    /* Test Improved version */
    start_time = clock();
    do
    {
      FastDFS(x, y, w, Wp, N, skip);
      end_time = clock();
      time_diff2 = (double) (end_time - start_time);
      count2++;
    } while (time_diff2 == 0);
    printf("%12.6f ", time_diff2/(CLOCKS_PER_SEC*count2));

    /* Compare and output result */
    printf("%9.2f\n", time_diff1*count2/(time_diff2*count1));

    /* Allocated Memory Destruction */
    free(x);
    free(y);
    free(w);
    free(Wp);
    N*=2;
  }

  return 0;
}
