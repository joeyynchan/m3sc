#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>

#define PI                3.14159265359

void printInfo();
double **create_matrix(int, int);
void free_matrix(double**);
double **mymatmul(double**, double**, int, int, int);
double **MakeSN(int);
void FastSINE(double* rx, double* ry,int N);
int check_result(double** y1, double* y2, int N);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int N = 2;
  printInfo();
  printf(" log2(N)     MatMul      FastSINE    Same Result \n");
  printf("--------- ------------ ------------ -------------\n");
  while (1)
  {
    int i;

    double time_diff1 = 0;
    double time_diff2 = 0;
    double time_limit = 100.;
    clock_t start_time, end_time;


    double** y1;
    double*  y2 = (double *)malloc((N-1)*sizeof(double));
    double** x1 = create_matrix(N-1, 1);
    double*  x2 = (double *)malloc((N-1)*sizeof(double));
    double** Sn = MakeSN(N);

    /* Dummy Vector and Matrix Constructino */
    for (i = 1; i < N; i++)
    {
      x1[i][1] = i;
      x2[i]  = i;
    }


    printf("%9d ", N);

    /* Time Direct Matrix Multiplication */
    start_time = clock();
    y1 = mymatmul(Sn, x1, N-1, N-1, 1);
    end_time = clock();
    time_diff1 = (double) (end_time - start_time);
    time_diff1 = (time_diff1 == 0) ? 1. : time_diff1;
    printf("%12.6f ", time_diff1/CLOCKS_PER_SEC);

    /* Time FastSine Method */
    start_time = clock();
    FastSINE(x2, y2, N);
    end_time = clock();
    time_diff2 = (double) (end_time - start_time);
    time_diff2 = (time_diff2 == 0) ? 1. : time_diff2;
    printf("%12.6f ", time_diff2/CLOCKS_PER_SEC);

    /* Compare and output result */
    printf("%7s\n", check_result(y1, y2, N) == 1 ? "Yes" : "No");

    /* Allocated Memory Destruction */
    free_matrix(x1);
    free_matrix(y1);
    free_matrix(Sn);
    free(x2);
    free(y2);

    /* Stop Execution if time taken is larger than threshold value, ie 100s */
    if (time_diff1/CLOCKS_PER_SEC > time_limit ||
        time_diff2/CLOCKS_PER_SEC > time_limit)
      break;
    else
      N *= 2;

  }

  return 0;
}

int check_result(double** y1, double* y2, int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  int result = 1;
  for (i = 1; i < N; i++)
  {

    if (fabs((y1[i][1] - y2[i])/y2[i]) > 1e-3)
    {
      printf("y1[%d] = %12.6f\t", i+1, y1[i][1]);
      printf("y2[%d] = %12.6f\t", i, y2[i]);
      printf("Percentage Error = %g\n", (y2[i]-y1[i][1])/y2[i]);
      result = 0;
      break;
    }
  }
  return result;
}
