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
  int N[105] = {8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
               28,29,30,31,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,
               64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,136,144,152,
               160,168,176,184,192,200,208,216,224,232,240,248,256,272,288,304,320,336,352,368,
               384,400,416,432,448,464,480,496,512,544,576,608,640,672,704,736,768,800,832,864,
               896,928,960,992,1024};
  int i;
  clock_t start_time, end_time;
  double time_diff = 0;
  for (i = 0; i < 105; i++)
  {
  	double** M, ** MM;
    M = create_random_matrix(N[i], N[i]);
    start_time = clock();
    MM = mymatmul(M, M, N[i], N[i], N[i]);  
    end_time = clock();
    time_diff = (double) (end_time - start_time);
    time_diff = (time_diff == 0) ? 1 : time_diff;
    printf("%10.6f \n", time_diff / (double)CLOCKS_PER_SEC);
    free_matrix(MM);
    free_matrix(M);

  }

  return 0;
}
