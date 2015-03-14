#include <stdio.h>
#include <stdlib.h>

double **create_sigma_matrix(int);
void print_matrix(double**, int, int);
void free_matrix(double**);

int main()
{
  double** M = create_sigma_matrix(32);
  print_matrix(M, 32, 32);
  free_matrix(M);
  return 0;
}

