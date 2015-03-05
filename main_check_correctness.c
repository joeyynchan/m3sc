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
int compare_matrix(double**, double**, int, int);
void free_matrix(double**);

int main()
{

  double _B[12] = {1.,  2., 3., 4.,  5., 6., 7.,  8., 9., 10.,  11., 12.};
  double _C[12] = {1., -2., 3., 4., -5., 6., 7., -8., 9., 10., -11., 12.};
  double _expected_BC[9] = {70., -80., 90., 158., -184., 210., 246., -288., 330.};
  double _expected_CB[16] = {18., 20., 22., 24., 33., 38., 43., 48., 48., 56., 64., 72., 63., 74., 85., 96.};

  double** BC, **CB;
  double** B = create_matrix_with_entries(3, 4, _B);
  double** C = create_matrix_with_entries(4, 3, _C);
  double** expected_BC = create_matrix_with_entries(3, 3, _expected_BC);
  double** expected_CB = create_matrix_with_entries(4, 4, _expected_CB);

  /* I J K */
  BC = mymatmul(B, C, 3, 4, 3);
  CB = mymatmul(C, B, 4, 3, 4);
  printf("Multiplying matrix using order IJK %s return the expected BC.\n", compare_matrix(expected_BC, BC, 3, 3) ? "does" : "does not");
  printf("Multiplying matrix using order IJK %s return the expected CB.\n\n", compare_matrix(expected_CB, CB, 4, 4) ? "does" : "does not");
  free_matrix(BC);
  free_matrix(CB);

  /* I K J */
  BC = mymatmul_ikj(B, C, 3, 4, 3);
  CB = mymatmul_ikj(C, B, 4, 3, 4);
  printf("Multiplying matrix using order IKJ %s return the expected BC.\n", compare_matrix(expected_BC, BC, 3, 3) ? "does" : "does not");
  printf("Multiplying matrix using order IKJ %s return the expected CB.\n\n", compare_matrix(expected_CB, CB, 4, 4) ? "does" : "does not");
  free_matrix(BC);
  free_matrix(CB);

  /* J I K */
  BC = mymatmul_jik(B, C, 3, 4, 3);
  CB = mymatmul_jik(C, B, 4, 3, 4);
  printf("Multiplying matrix using order JIK %s return the expected BC.\n", compare_matrix(expected_BC, BC, 3, 3) ? "does" : "does not");
  printf("Multiplying matrix using order JIK %s return the expected CB.\n\n", compare_matrix(expected_CB, CB, 4, 4) ? "does" : "does not");
  free_matrix(BC);
  free_matrix(CB);

  /* J K I */
  BC = mymatmul_jki(B, C, 3, 4, 3);
  CB = mymatmul_jki(C, B, 4, 3, 4);
  printf("Multiplying matrix using order JKI %s return the expected BC.\n", compare_matrix(expected_BC, BC, 3, 3) ? "does" : "does not");
  printf("Multiplying matrix using order JKI %s return the expected CB.\n\n", compare_matrix(expected_CB, CB, 4, 4) ? "does" : "does not");
  free_matrix(BC);
  free_matrix(CB);

  /* K I J */
  BC = mymatmul_kij(B, C, 3, 4, 3);
  CB = mymatmul_kij(C, B, 4, 3, 4);
  printf("Multiplying matrix using order KIJ %s return the expected BC.\n", compare_matrix(expected_BC, BC, 3, 3) ? "does" : "does not");
  printf("Multiplying matrix using order KIJ %s return the expected CB.\n\n", compare_matrix(expected_CB, CB, 4, 4) ? "does" : "does not");
  free_matrix(BC);
  free_matrix(CB);

  /* K J I */
  BC = mymatmul_kji(B, C, 3, 4, 3);
  CB = mymatmul_kji(C, B, 4, 3, 4);
  printf("Multiplying matrix using order KJI %s return the expected BC.\n", compare_matrix(expected_BC, BC, 3, 3) ? "does" : "does not");
  printf("Multiplying matrix using order KJI %s return the expected CB.\n\n", compare_matrix(expected_CB, CB, 4, 4) ? "does" : "does not");
  free_matrix(BC);
  free_matrix(CB);

  free_matrix(B);
  free_matrix(C);
  free_matrix(expected_BC);
  free_matrix(expected_CB);

  return 0;
}

int compare_matrix(double** expected, double** actual, int row, int col)
{
  int i, j;
  for (i = 1; i <= row; i++)
    for (j = 1; j <= col; j++)
      if (expected[i][j] != actual[i][j])
        return 0;
  return 1;
}