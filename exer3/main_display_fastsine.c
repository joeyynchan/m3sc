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
    clock_t start_time, end_time;
    double** y1;
    double*  y2 = (double *)malloc((N-1)*sizeof(double));
    double** x1 = create_matrix(N-1, 1);
    double*  x2 = (double *)malloc((N-1)*sizeof(double));
    double** Sn = MakeSN(N);

    for (i = 1; i < N; i++)
    {
      x1[i][1] = i;
      x2[i-1]  = i;
    }
    printf("%9d ", N);

    start_time = clock();
    y1 = mymatmul(Sn, x1, N-1, N-1, 1);
    end_time = clock();
    time_diff1 = (double) (end_time - start_time);
    time_diff1 = (time_diff1 == 0) ? 1. : time_diff1;
    printf("%12.6f ", time_diff1/CLOCKS_PER_SEC);

    start_time = clock();
    FastSINE(x2, y2, N);
    end_time = clock();
    time_diff2 = (double) (end_time - start_time);
    time_diff2 = (time_diff2 == 0) ? 1. : time_diff2;
    printf("%12.6f ", time_diff2/CLOCKS_PER_SEC);

    printf("%7s\n", check_result(y1, y2, N) == 1 ? "Yes" : "No");
    /*
    for (i = 1; i < N; i++)
      printf("y1[%d] = %12.6f\n", i, 2*y1[i][1]);

    printf("\n\n");
    for (i = 0; i < N-1; i++)
  	  printf("y2[%d] = %12.6f\n", i, y2[i]);
    */

    free_matrix(x1);
    free_matrix(y1);
    free_matrix(Sn);
    free(x2);
    free(y2);

    if (time_diff1/CLOCKS_PER_SEC > 100 || time_diff2/CLOCKS_PER_SEC > 100)
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
  for (i = 0; i < N-1; i++)
  {

  	if (fabs((2*y1[i+1][1] - y2[i])/y2[i]) > 1e-3)
    {
      printf("2*y1[%d] = %12.6f\t", i+1, 2*y1[i+1][1]);
  	  printf("y2[%d] = %12.6f\t", i, y2[i]);
  	  printf("Percentage Error = %g\n", (y2[i]-2*y1[i+1][1])/y2[i]);
      result = 0;
      break;
    }
  }
  return result;
}

double** create_matrix(int row, int col)
{
  /* Chan, Joey, JMCSC, ync12 */
  int n;
  double** m = (double**) calloc(row+1, sizeof(double*));
  m[0] = (double*) calloc(row*col+1, sizeof(double));
  m[1] = m[0];
  for (n = 2; n <= row; n++)
    m[n] = m[n-1]+col;
  return m;
}

void free_matrix(double** matrix)
{
  /* Chan, Joey, JMCSC, ync12 */
  free(matrix[0]);
  free(matrix);
}

double **mymatmul(double** m1, double** m2, int row1, int col1, int col2)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  double** m = create_matrix(row1, col2);

  #pragma omp parallel for
  for (i = 1; i <= row1; i++)
  {
    double* m1_row_i = m1[i];
    double* m_row_i = m[i];
    for (k = 1; k <= col1; k++)
    {
      double* m2_row_k = m2[k];
      double m1_ik = m1_row_i[k];
      for (j = 1; j <= col2; j++)
        m_row_i[j] += m1_ik * m2_row_k[j];
    }
  }
  return m;
}

double **MakeSN(int N)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j;
  double** M = create_matrix(N-1, N-1);
  for (i = 1; i < N; i++)
    for (j = 1; j < N; j++)
      M[i][j] = sin((double)i*(double)j*PI/(double)N);
  return M;
}

void printInfo()
{
  /* Chan, Joey, JMCSC, ync12 */
  printf("\n");
  printf("%15s: %s\n", "Name", "Joey");
  printf("%15s: %s\n", "CID", "00730306");
  printf("%15s: %s\n", "LIBRARY NO", "0246734100");
  printf("%15s: %s\n", "Email Address", "ync12@ic.ac.uk");
  printf("%15s: %s\n", "Course Code", "JMCSC");
  printf("%15s: %s, %s \n", "Compile Time", __TIME__, __DATE__);
  printf("-------------------------------------------------\n");
}

