#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARC4RANDOM_MAX    0x100000000
#define PI                3.14159265359

/* Matrix Construction and Destruction*/
double** create_matrix(int, int);
double**create_random_matrix(int, int);
double** create_matrix_with_entries(int, int, double*);
void free_matrix(double**);
void print_matrix(double**, int, int);

/* Matrix Multiplication with different loop order*/
double **mymatmul(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_ijk(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_ikj(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_jik(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_jki(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_kij(double** m1, double** m2, int row1, int col1, int col2);
double **mymatmul_kji(double** m1, double** m2, int row1, int col1, int col2);

/* Construct Symmetric Matrix */
double **MakeSN(int);






/*
 *  Function Implementation
 **************************************************
 **************************************************/


/*
 *  Matrix Constructor
 ****************************
 ****************************/
double** create_matrix(int row, int col)
{
  int n;
  double** m = (double**) calloc(row+1, sizeof(double*));
  m[0] = (double*) calloc(row*col+1, sizeof(double));
  m[1] = m[0];
  for (n = 2; n <= row; n++)
    m[n] = m[n-1]+col;
  return m;
}

double** create_random_matrix(int row, int col)
{
  int i, j;
  double** m = create_matrix(row, col);
  for (i = 1; i <= row; i++)
    for (j = 1; j <= col; j++)
      /*m[i][j] = (double)arc4random()/(double)ARC4RANDOM_MAX;*/
      m[i][j] = (double)rand() / RAND_MAX;
  return m;
}

double** create_matrix_with_entries(int row, int col, double* e)
{
  int n, i, j, k = 0;
  double** m = (double**) calloc(row+1, sizeof(double*));
  m[0] = (double*) calloc(row*col+1, sizeof(double));
  m[1] = m[0];
  for (n = 2; n <= row; n++)
    m[n] = m[n-1]+col;
  for (i = 1; i <= row; i++)
    for (j = 1; j <= col; j++)
      m[i][j] = *(e+(k++));
  return m;
}

void free_matrix(double** matrix)
{
  free(matrix[0]);
  free(matrix);
}


void print_matrix(double** m, int row, int col)
{
  int i, j;
  for (i = 1; i <= row; i++)
  {
    printf("(");
    for (j = 1; j < col; j++)
    {
      printf("%6.1f, ", m[i][j]);
    }
    printf("%6.1f)\n", m[i][col]);
  }
}

void print_matrix2(double** m, int row, int col)
{
  int i, j;
  for (i = 1; i <= row; i++)
    for (j = 1; j <= col; j++)
      printf("M[%4d][%4d] = %15.6f\n", i, j, m[i][j]);
}


/*
 * Matrix Multiplication
 *************************
 *************************/

double **mymatmul(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
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

double **mymatmul_ijk(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (i = 1; i <= row1; i++)
    for (j = 1; j <= col2; j++)
      for (k = 1; k <= col1; k++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_ikj(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (i = 1; i <= row1; i++)
    for (k = 1; k <= col1; k++)
      for (j = 1; j <= col2; j++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_jik(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (j = 1; j <= col2; j++)
    for (i = 1; i <= row1; i++)
      for (k = 1; k <= col1; k++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_jki(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (j = 1; j <= col2; j++)
    for (k = 1; k <= col1; k++)
      for (i = 1; i <= row1; i++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_kij(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (k = 1; k <= col1; k++)
    for (i = 1; i <= row1; i++)
      for (j = 1; j <= col2; j++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}

double **mymatmul_kji(double** m1, double** m2, int row1, int col1, int col2)
{
  double** m = create_matrix(row1, col2);
  int i, j, k;
  for (k = 1; k <= col1; k++)
    for (j = 1; j <= col2; j++)
      for (i = 1; i <= row1; i++)
        m[i][j] += m1[i][k] * m2[k][j];
  return m;
}


/*
 * Question 5: Create Symmetric Matrix
 ***************************************
 ***************************************/

double **MakeSN(int N)
{
  int i, j;
  double** M = create_matrix(N-1, N-1);
  for (i = 1; i < N; i++)
    for (j = 1; j < N; j++)
      M[i][j] = sin((double)i*(double)j*PI/(double)N);
  return M;
}

/*
 * Question 6: Create Sigma Matrix
 ************************************
 ************************************/

double **create_sigma_matrix(int N)
{
  int i, j;
  double** M = create_matrix(N, N);

  if (N % 32 != 0)
  {
    printf("%d is not a valid value for N\n", N);
    return 0;
  }

  for (i = N*3/8; i <= N/2; i++)
    for (j = N*7/16; j <= N*9/16; j++)
      M[i][j] = 1000.;
  for (i = N/2; i <= N*9/16; i++)
    for (j = N*15/32; j <= N*17/32; j++)
      M[i][j] = (M[i][j] == 1000.) ? 750. : 500. ;
  return M;
}

double **create_smooth_sigma_matrix(int N)
{
  int i, j;
  int lower_i1 = N*3/8,
      upper_i1 = N/2,
      lower_j1 = N*7/16,
      upper_j1 = N*9/16,
      lower_i2 = N/2,
      upper_i2 = N*9/16,
      lower_j2 = N*15/32,
      upper_j2 = N*17/32;
  double** M = create_matrix(N, N);

  if (N % 32 != 0)
  {
    printf("%d is not a valid value for N\n", N);
    return 0;
  }

  for (i = lower_i1; i <= upper_i1; i++)
    for (j = lower_j1; j <= upper_j1; j++)
      if ((i == lower_i1 && (j == lower_j1 || j == upper_j1)) ||
          (i == upper_i1 && (j == lower_j1 || j == upper_j1)))
        M[i][j] = 250.;
      else if (i == lower_i1 || i == upper_i1 ||
               j == lower_j1 || j == upper_j1)
        M[i][j] = 500.;
      else
        M[i][j] = 1000.;

  for (i = lower_i2; i <= upper_i2; i++)
    for (j = lower_j2; j <= upper_j2; j++)
      if ((i == lower_i2 && (j == lower_j2 || j == upper_j2)) ||
          (i == upper_i2 && (j == lower_j2 || j == upper_j2)))
        M[i][j] = (M[i][j] != 0) ?  (M[i][j] + 125.)/2. : 125.;
      else if (i == lower_i2 || i == upper_i2 ||
               j == lower_j2 || j == upper_j2)
        M[i][j] = (M[i][j] != 0) ?  (M[i][j] + 250.)/2. : 250.;
      else
        M[i][j] = (M[i][j] != 0) ?  (M[i][j] + 500.)/2. : 500.;
  return M;
}


/*
 *  Cube Constructor
 ************************
 ************************/

double*** create_cube(int N)
{
  int i;
  double*** m = (double***) calloc(N+1, sizeof(double**));
  for (i = 1; i <=N; i++)
    m[i] = create_matrix(N, N);

  return m;
}

void free_cube(double*** m, int N)
{
  int i;
  for (i = 1; i <=N; i++)
    free_matrix(m[i]);
  free(m);
}

void print_cube(double*** m, int N)
{
   int i;
   for (i = 1; i <= N; i++)
   {
    printf("\nLayer %5d\n", i);
    print_matrix(m[i], N, N);
   }
}


/*
 * Mastery: Create Sigma Cube
 ************************************
 ************************************/

double*** create_sigma_cube(int N)
{
  double*** cube = create_cube(N);
  int i, j, k;

  for (i = N*3/8; i <= N/2; i++)
    for (j = N*7/16; j <= N*9/16; j++)
      for (k = N*3/8; k <= N/2; k++)
        cube[i][j][k] = 10000;

  for (i = N*7/16; i <= N*9/16; i++)
    for (j = N*15/32; j <= N*17/32; j++)
      for (k = N/2; k <= 9/16; k++)
        cube[i][j][k] = 10000;

  return cube;
}

double*** to_sigma_imn(double*** cube, int N)
{
  double*** new_cube = create_cube(N);
  double** Sn = MakeSN(N);
  int i;
  for (i = 1; i <=N; i++)
    new_cube[i] = mymatmul(Sn, cube[i], N-1, N-1, N-1);
  free_matrix(Sn);
  return new_cube;
}

double*** to_sigma_ijn(double*** cube, int N)
{
  double*** new_cube = create_cube(N);
  double** Sn = MakeSN(N);
  int i;
  for (i = 1; i <=N; i++)
    new_cube[i] = mymatmul(cube[i], Sn, N-1, N-1, N-1);
  free_matrix(Sn);
  return new_cube;
}


double*** to_sigma_ijk(double*** cube, int N)
{
  double*** new_cube = create_cube(N);
  int i, j, k, n;
  for (i = 1; i <=N-1; i++)
    for (k = 1; k <= N-1; k++)
      for (n = 1; n <= N-1; n++)
        for (j = 1; j <= N-1; j++)
          new_cube[i][j][k] += cube[i][j][n] * sin(k*n*PI/N);
  return new_cube;
}


