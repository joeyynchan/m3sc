#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int check_symmetric_matrix_correctness(double**, int);
double** mymatmul(double**, double**, int, int, int);
double** MakeSN(int);
void free_matrix(double**);

int main()
{

  int m = 0;
  int should_stop = 0;
  clock_t start, end;
  printf("   m         N      Result as expected   Time taken\n");
  printf("------- ---------- -------------------- ------------\n");
  while(!should_stop)
  {
    int i, result;
    for (i = 4; i <= 6; i++)
    { 
      double time_taken;
      int N = i*(int)pow(2, 3+m);
      double** M = MakeSN(N);
      start = clock();
      double** MM = mymatmul(M, M, N-1, N-1, N-1);
      end = clock();
      time_taken = (double) (end - start) / CLOCKS_PER_SEC;
      result = check_symmetric_matrix_correctness(MM, N);
      printf("%7d %10d %20s %12.4f\n", m, N, result == 1 ? "True" : "False", time_taken);
      free_matrix(M);
      free_matrix(MM);
      if (time_taken > 5)
      {
        should_stop = 1;
        break;
      }
    }
    m++;
  }

}

int check_symmetric_matrix_correctness(double** MM, int N)
{
  int i, j;
  int result = 1;
  for (i = 1; i < N; i++)
    for (j = 1; j < N; j++)
      if ((i == j && fabs(MM[i][j] - N/2) > 1e-6) || (i != j && fabs(MM[i][j]) > 1e-6))
      {
        result = 0;
        printf("MM[%d][%d] expected = %20.12f but actual = %20.12f \n", i, j, i==j ? (double)N/2 : 0., MM[i][j]);
      }
  return result;
}