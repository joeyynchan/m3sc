#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void print_matrix(double**, int, int);
double** create_matrix(int, int);
double** create_random_matrix(int, int);
double** create_matrix_with_entries(int, int, double*);
double** mymatmul(double**, double**, int, int , int);
void free_matrix(double**);

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int N[105] = {8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
               28,29,30,31,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,
               64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,136,144,152,
               160,168,176,184,192,200,208,216,224,232,240,248,256,272,288,304,320,336,352,368,
               384,400,416,432,448,464,480,496,512,544,576,608,640,672,704,736,768,800,832,864,
               896,928,960,992,1024};
  int i;
  double time_diff = 0;
  clock_t start_time, end_time;
  
  printf("  N    log10(N)     Time      GFlops   \n");
  printf("----- ---------- ---------- ---------- \n");
  
  for (i = 0; i < 105; i++)
  {
  	double** M, ** MM;
    M = create_random_matrix(N[i], N[i]);
    start_time = clock();
    MM = mymatmul(M, M, N[i], N[i], N[i]);  
    end_time = clock();
    time_diff = (double) (end_time - start_time);
    time_diff = (time_diff == 0) ? 1. : time_diff;
    printf("%5d %8.2f ", N[i], log10((double)N[i]));
    printf("%10.6f ", time_diff/CLOCKS_PER_SEC);
    printf("%10.6f",  2*N[i]*N[i]*N[i]/(time_diff/CLOCKS_PER_SEC)/10e+9);
    printf("\n");
    free_matrix(MM);
    free_matrix(M);
  }

  return 0;
}
