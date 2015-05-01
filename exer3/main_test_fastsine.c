#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>

#define PI                3.14159265359

void printInfo();
int test(int N);
double **create_matrix(int, int);
void free_matrix(double**);
double **mymatmul(double**, double**, int, int, int);
double **MakeSN(int);
void FastSINE(double* rx, double* ry,int N);
int check_result(double** y1, double* y2, int N);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int N, m = 0;
  int go = 1;
  printInfo();
  printf("    N        MatMul      FastSINE    Same Result     Ratio\n");
  printf("--------- ------------ ------------ ------------- -----------\n");

  for (N = 32; N <= 96; N+= 32)
  {
    test(N);
	printf("HI\n");
  }
  /*
  while (go)
  {
    int i;
    for (i = 4; i <= 6; i++)
    {
      N = i*(int)pow(2, 5+m);
      go = test(N);
      if (!go)
        break;
    }
    m++;
  }*/

  return 0;
}

int test(int N)
{
  int i, count1 = 0, count2 = 0;

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
  do
  {
    y1 = mymatmul(Sn, x1, N-1, N-1, 1);
    end_time = clock();
    time_diff1 = (double) (end_time - start_time);
    count1++;
  } while (time_diff1 == 0);
  printf("%12.4e ", time_diff1/(CLOCKS_PER_SEC*count1));


  /* Time FastSine Method */
  start_time = clock();
  do
  {
    FastSINE(x2, y2, N);
    end_time = clock();
    time_diff2 = (double) (end_time - start_time);
    count2++;
  } while (time_diff2 == 0);
  printf("%12.4e ", time_diff2/(CLOCKS_PER_SEC*count2));

  /* Compare and output result */
  printf("%13s ", check_result(y1, y2, N) == 1 ? "Yes" : "No");
  printf("%11.6f\n", (time_diff1*count2)/(time_diff2*count1));

  /* Allocated Memory Destruction */
  /*free_matrix(x1);*/
  free_matrix(y1);
  free_matrix(Sn);
  free(x2);
  free(y2);

  /* Stop Execution if time taken is larger than threshold value, ie 100s */
  if (time_diff1/CLOCKS_PER_SEC > time_limit ||
      time_diff2/CLOCKS_PER_SEC > time_limit)
    return 0;
  else
    return 1;
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
