#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>

#define PI                3.14159265359

void printInfo();
complex double* MakeWpowers(int N);
void FastDFS(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);
void FastDFT(complex double* x, complex double* y, complex double* w, complex double* Wp, int N, int skip);
int check_result(complex double* x, int N, int skip);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int skip, N = 1;
  printInfo();
  printf("Enter skip:");
  scanf("%d", &skip);
  printf("    N        FastDFS     Expected  \n");
  printf("--------- ------------ ------------ \n");
  while (N<=20)
  {
    int i, count = 0;
    double time_diff = 0;
    clock_t start_time, end_time;

    complex double *Wp = MakeWpowers(N);
    complex double *w  = (complex double*) malloc(2*N    * sizeof(complex double));
    complex double *y  = (complex double*) malloc(N*skip * sizeof(complex double));
    complex double *x  = (complex double*) malloc(N*skip * sizeof(complex double));
    
    printf("%9d ", N);

    for (i = 0; i < N*skip; i++)
      y[i] = 0 + 0*I;
    for (i = 0; i < N; i++)
      y[i*skip] =  i+1. + 0.*I;

    FastDFS(x, y, w, Wp, N, skip);

    /* Time FastSine Method */
    start_time = clock();
    do
    {
      FastDFT(x, y, w, Wp, N, skip);
      end_time = clock();
      time_diff = (double) (end_time - start_time);
      count++;
    } while (time_diff == 0);
    printf("%12.4e ", time_diff/(CLOCKS_PER_SEC*count));

    /* Compare and output result */
    printf("%7s\n", check_result(y, N++, skip) == 1 ? "Yes" : "No");

    /* Allocated Memory Destruction */
    free(x);
    free(y);
    free(w);
    free(Wp);

  }

  return 0;
}

int check_result(complex double* y, int N, int skip)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  int result = 1;
  for (i = 0; i < N*skip; i++)
    if (i%skip == 0)
    {
      if (cabs((y[i]/(double)N-(i/skip+1.))/(i/skip+1.)) > 1e-3)
      {
        result = 0;
        break;        
      }
    }
    else
    {
      if (cabs(y[i]) > 1e-3)
      {
        result = 0;
        break;
      }
    }
  return result;
}
