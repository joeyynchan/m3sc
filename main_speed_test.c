#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(double**, int, int);
double** mymatmul(double**, double**, int, int, int);
double** mymatmul_ikj(double**, double**, int, int, int);
double** mymatmul_jik(double**, double**, int, int, int);
double** mymatmul_jki(double**, double**, int, int, int);
double** mymatmul_kij(double**, double**, int, int, int);
double** mymatmul_kji(double**, double**, int, int, int);
double** create_matrix(int, int);
double** create_random_matrix(int, int);
double** create_matrix_with_entries(int, int, double*);
void free_matrix(double**);

int main()
{
  printf("HI\n");
  int N[19] = {8, 9, 10, 32, 34, 64, 68, 72, 128, 136, 144, 160, 256, 264, 272, 512, 528, 542, 1024};
  int i, j;
  clock_t start_time, end_time;
  printf("  N      I J K      I K J      J I K       J K I      K I J     K J I  \n");
  printf("----- ---------- ---------- ---------- ---------- ---------- ----------\n");
  for (i = 0; i < 19; i++)
  {
  	double** M, ** MM;
    printf("%5d ", N[i]);

    M = create_random_matrix(N[i], N[i]);
    start_time = clock();
    MM = mymatmul(M, M, N[i], N[i], N[i]);  
    end_time = clock();
    printf("%10.6f ", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
    free_matrix(MM);
    free_matrix(M);

    M = create_random_matrix(N[i], N[i]);
    start_time = clock();
    MM = mymatmul_ikj(M, M, N[i], N[i], N[i]);  
    end_time = clock();
    printf("%10.6f ", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
    free_matrix(MM);
    free_matrix(M);

    M = create_random_matrix(N[i], N[i]);
    start_time = clock();
    MM = mymatmul_jik(M, M, N[i], N[i], N[i]);  
    end_time = clock();
    printf("%10.6f ", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
    free_matrix(MM);
    free_matrix(M);

    M = create_random_matrix(N[i], N[i]);
    start_time = clock();
    MM = mymatmul_jki(M, M, N[i], N[i], N[i]);  
    end_time = clock();
    printf("%10.6f ", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
    free_matrix(MM);
    free_matrix(M);

    M = create_random_matrix(N[i], N[i]);
    start_time = clock();
    MM = mymatmul_kij(M, M, N[i], N[i], N[i]);  
    end_time = clock();
    printf("%10.6f ", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
    free_matrix(MM);
    free_matrix(M);

    M = create_random_matrix(N[i], N[i]);
    start_time = clock();
    MM = mymatmul_kji(M, M, N[i], N[i], N[i]);  
    end_time = clock();
    printf("%10.6f \n", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
    free_matrix(MM);
    free_matrix(M);

  }

  return 0;
}
